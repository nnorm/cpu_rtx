#include <parse_args.h>
#include <stdio.h>
#include <stddef.h>
#include <assert.h>
#include <fstream>
#include <algorithm>

#include <glm.hpp>

/* DATA */
struct Ray
{
	Ray(glm::vec3 const& ro = glm::vec3(), glm::vec3 const& rd = glm::vec3()) : origin(ro), direction(rd) {};
	glm::vec3 origin;
	glm::vec3 direction;
	glm::vec3 compute_position(float t) const { return origin + (direction * t); }
};

struct HitRecord
{
	float t = 0.0f;
	glm::vec3 position;
	glm::vec3 normal;
};

struct Sphere
{
	glm::vec3 center;
	float radius;
};

/* RAYTRACE */
bool hit_sphere(Sphere const& sphere, Ray const& ray, float tmin, float tmax, HitRecord& record)
{
	glm::vec3 origin_center_vector = ray.origin - sphere.center;
	//quadratic equation (ax² + bx + c) factors:
	float a = glm::dot(ray.direction, ray.direction);
	float b = glm::dot(origin_center_vector, ray.direction);
	float c = glm::dot(origin_center_vector, origin_center_vector) - (sphere.radius * sphere.radius);

	//quadratic discriminant:
	float discriminant = b*b - a*c;
	if (discriminant >= 0)
	{
		float temp = (-b - sqrtf(b*b - a*c)) / a;
		if (temp < tmax && temp > tmin)
		{
			record.t = (-b - sqrtf(discriminant)) / (2.0f * a);
			record.position = ray.compute_position(record.t);
			record.normal = glm::normalize(record.position - sphere.center);
			return true;
		}
		temp = (-b + sqrtf(b*b - a * c)) / a;
		if (temp < tmax && temp > tmin)
		{
			record.t = (-b - sqrtf(discriminant)) / (2.0f * a);
			record.position = ray.compute_position(record.t);
			record.normal = glm::normalize(record.position - sphere.center);
			return true;
		}
	}
	return false;
}

/* COLOR */
glm::vec3 background(Ray const& r)
{
	glm::vec3 normalize_direction = glm::normalize(r.direction/2.0f);
	float t = 0.5f * normalize_direction.y + 0.5f;
	return (1.0f - t) * glm::vec3(1.0, 1.0, 1.0) + t * glm::vec3(0.5, 0.7f, 1.0f);
}

bool trace_against_world(Ray const& r, Sphere const* sphereTable, int sphereCount, float tmin, float tmax, HitRecord& record)
{
	glm::vec3 sphere_center = glm::vec3(0.0f, 0.0f, -1.0f);
	Sphere sph0 = Sphere({ glm::vec3(0.0f, 0.0f, -1.0f), 0.5f });
	
	HitRecord tmp_record;
	bool hit = false;
	float closest_yet = tmax;
	for (int i = 0; i < sphereCount; i++)
	{
		if (hit_sphere(sphereTable[i], r, tmin, closest_yet, tmp_record))
		{
			hit = true;
			closest_yet = record.t;
			record = tmp_record;
		}
	}
	return hit;
}

glm::vec3 compute_color(Ray const& r, Sphere const* sphereTable, int sphereCount)
{
	HitRecord record;
	if (trace_against_world(r, sphereTable, sphereCount, 0.0f, 64.0f, record))
	{
		return (0.5f*record.normal + 0.5f);
	}
	return background(r);
}

int main(int argc, char const *argv[])
{
    printf("CPU RTX\n");
    argsResult argsRes = parseCmdlineArgs(argc, argv);
	int height = int(argsRes.height);
	int width = int(argsRes.width);

	std::ofstream outputFile(argsRes.outputPath);
	assert("Could not open output file" && outputFile.is_open());
	
	//write file content
	outputFile << "P3\n" << width << " " << height << "\n" << "255\n";
	const float aspectRatio = float(width) / float(height);
	glm::vec3 horizontal_axis(1.0f, 0.0f, 0.0f);
	glm::vec3 vertical_axis(0.0, 1.0, 0.0);
	glm::vec3 eye_positon(0.0f, 0.0f, 1.0f);

	//scene
	Sphere world[2] = { {glm::vec3(0.0f, 0.0f, -1.0f), 0.5f}, {glm::vec3(0.0f, -100.5f, -1.0f), 100.0f} };

	for (int py = height - 1; py >= 0; py--)
	{
		for (int px = 0; px < width; px++)
		{
			//ray trace
			glm::vec2 uv(float(px) / float(width), float(py) / float(height));
			uv -= glm::vec2(0.5f);
			glm::vec3 rayDir = glm::vec3(0.0, 0.0, -1.0f) + uv.x * horizontal_axis * aspectRatio + uv.y * vertical_axis;
			Ray r(eye_positon, rayDir);
			glm::vec3 c = compute_color(r, world, 2);

			//write file
			c *= 255.99f;
			glm::ivec3 ic = glm::ivec3(std::max(0, int(c.x)), std::max(0, int(c.y)), std::max(0, int(c.z)));
			outputFile << ic.r << " ";
			outputFile << ic.g << " ";
			outputFile << ic.b << " \n";
		}
	}
	outputFile << std::endl;

	//close file
	outputFile.close();

    return 0;
}