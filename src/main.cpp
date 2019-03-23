#include <parse_args.h>
#include <output_file.h>
#include <ray.h>
#include <hittable.h>
#include <sphere.h>
#include <camera.h>

#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include <assert.h>
#include <vector>
#include <glm.hpp>
#include <random>

static constexpr int gp_SuperSamplingCount = 16;
static constexpr int gp_DiffuseRayMaxDepth = 8;

static constexpr float g_PI = 3.14159265359f;
static constexpr float g_Gamma = 2.22f;
static constexpr float g_invGamma = 1.0f / g_Gamma;

static std::random_device global_random_device;
static std::mt19937 global_mt19937_generator(global_random_device());


//src: https://stackoverflow.com/questions/14539867/how-to-display-a-progress-indicator-in-pure-c-c-cout-printf/36315819#36315819
#define PBSTR "############################################################"
#define PBWIDTH 32

void printProgressBar(double percentage)
{
	int val = (int)(percentage * 100);
	int lpad = (int)(percentage * PBWIDTH);
	int rpad = PBWIDTH - lpad;
	printf("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
	fflush(stdout);
}

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

glm::vec3 compute_color(Ray const& r, std::vector<Hittable*> const& world, int max_depth)
{
	if (max_depth <= 0)
		return background(r);
	HitRecord record;
	if (trace_ray(r, world, 0.001f, 512.0f, record))
	{
		std::uniform_real_distribution<float> dirRng(-1.0f, 1.0f);
		float sx = dirRng(global_mt19937_generator);
		float sy = dirRng(global_mt19937_generator);
		float sz = dirRng(global_mt19937_generator);
		glm::vec3 sampleDirection = glm::normalize(record.position + record.normal + glm::vec3(sx, sy, sz) - record.position);
		return record.material->albedo * compute_color(Ray(record.position, sampleDirection), world, max_depth - 1) * std::max(0.0f, glm::dot(sampleDirection, record.normal));
	}
	return background(r);
}

int main(int argc, char const *argv[])
{
    printf("CPU RTX\n");
    argsResult argsRes = parseCmdlineArgs(argc, argv);
	int height = int(argsRes.height);
	int width = int(argsRes.width);
	
	//camera setup
	const float aspectRatio = float(width) / float(height);
	Camera cam;
	cam.eye_position = glm::vec3(0.0, 0.0, 2.0f);

	//scene
	Material floorMat = Material({ glm::vec3(1.0f, 0.4f, 0.0f) });//	https://www.beautycolorcode.com/ff6600
	Material sphereMat = Material({ glm::vec3(0.4f, 0.0f, 1.0f) });//	https://www.beautycolorcode.com/6600ff
	std::vector<Hittable*> world = { new Sphere({glm::vec3(0.0f, 0.0f, -1.0f), 0.5f, sphereMat}),
									 new Sphere({glm::vec3(0.0f, -100.5f, -1.0f), 100.0f, floorMat}) };

	//image data
	std::vector<std::vector<glm::vec3>> image(width, std::vector<glm::vec3>(height, glm::vec3(0.0f)));
	std::uniform_real_distribution<float> superSamplingRNG(0.0f, 1.0f);

	//ray tracing loop
	const double pixelCount = double(width) * double(height) - 1;
	double progress = 0.0;
	for (int py = height - 1; py >= 0; py--)
	{
		for (int px = 0; px < width; px++)
		{
			printProgressBar(progress);

			//trace rays
			glm::vec3 color = glm::vec3(0.0f);
			for (int i = 0; i < gp_SuperSamplingCount; i++)
			{
				float jx = superSamplingRNG(global_mt19937_generator);
				float jy = superSamplingRNG(global_mt19937_generator);
				glm::vec2 uv(float(px + jx) / float(width), 
							 float(py + jy) / float(height));

				Ray r = cam.getRD(uv, aspectRatio);
				color += compute_color(r, world, gp_DiffuseRayMaxDepth);
			}
			color /= float(gp_SuperSamplingCount);
			color.r = powf(color.r, g_invGamma);
			color.g = powf(color.g, g_invGamma);
			color.b = powf(color.b, g_invGamma);
			image[px][py] = color;
			progress = 1.0 - double(py * height + px) / pixelCount;
		}
	}

	//output file
	write_ppm(argsRes.outputPath, image, width, height);

    return 0;
}