#include <parse_args.h>
#include <ray.h>
#include <hittable.h>
#include <sphere.h>

#include <stdio.h>
#include <stddef.h>
#include <assert.h>
#include <fstream>
#include <algorithm>
#include <vector>
#include <glm.hpp>

/* RAYTRACE */
bool trace_ray(Ray const& r, std::vector<Hittable*> const& world, float tmin, float tmax, HitRecord& record)
{
	glm::vec3 sphere_center = glm::vec3(0.0f, 0.0f, -1.0f);
	HitRecord tmp_record;
	bool hit = false;
	float closest_yet = tmax;
	for (Hittable const* obj : world)
	{
		if (obj->hit(r, tmin, closest_yet, tmp_record))
		{
			hit = true;
			closest_yet = record.t;
			record = tmp_record;
		}
	}
	return hit;
}

/* COLOR */
glm::vec3 background(Ray const& r)
{
	glm::vec3 normalize_direction = glm::normalize(r.direction/2.0f);
	float t = 0.5f * normalize_direction.y + 0.5f;
	return (1.0f - t) * glm::vec3(1.0, 1.0, 1.0) + t * glm::vec3(0.5, 0.7f, 1.0f);
}

glm::vec3 compute_color(Ray const& r, std::vector<Hittable*> const& world)
{
	HitRecord record;
	if (trace_ray(r, world, 0.0f, 64.0f, record))
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
	std::vector<Hittable*> world = { new Sphere({glm::vec3(0.0f, 0.0f, -1.0f), 0.5f}),
									 new Sphere({glm::vec3(0.0f, -100.5f, -1.0f), 100.0f}) };
	
	for (int py = height - 1; py >= 0; py--)
	{
		for (int px = 0; px < width; px++)
		{
			//trace ray
			glm::vec2 uv(float(px) / float(width), float(py) / float(height));
			uv -= glm::vec2(0.5f);
			glm::vec3 rayDir = glm::vec3(0.0, 0.0, -1.0f) + uv.x * horizontal_axis * aspectRatio + uv.y * vertical_axis;
			Ray r(eye_positon, rayDir);
			glm::vec3 c = compute_color(r, world);

			//write to file
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