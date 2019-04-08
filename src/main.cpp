#include <parse_args.h>
#include <output_file.h>
#include <ray.h>
#include <hittable.h>
#include <sphere.h>
#include <plane.h>
#include <camera.h>
#include <utils.h>

#include <stdio.h>
#include <stddef.h>
#include <assert.h>
#include <vector>
#include <glm.hpp>
#include <random>

static constexpr int gp_SuperSamplingCount = 64;
static constexpr int gp_MaxRaysDepth = 4+1;

static constexpr float g_PI = 3.14159265359f;
static constexpr float g_Gamma = 2.22f;
static constexpr float g_invGamma = 1.0f / g_Gamma;

/* RAYTRACE */
bool trace_ray(Ray const& r, std::vector<Hittable*> const& world, float tmin, float tmax, HitRecord& record)
{
	HitRecord tmp_record;
	bool hit = false;
	float closest_yet = tmax;
	for (Hittable const* obj : world)
	{
		if (obj->hit(r, tmin, closest_yet, tmp_record))
		{
			hit = true;
			closest_yet = tmp_record.t;
			record = tmp_record;
		}
	}
	return hit;
}

/* COLOR */
glm::vec3 sky(Ray const& r)
{
	glm::vec3 normalized_direction = r.direction/2.0f;
	float t = 0.5f * normalized_direction.y + 0.5f;
	glm::vec3 outputColor = (1.0f - t) * glm::vec3(1.0, 1.0, 1.0) + t * glm::vec3(0.5, 0.7f, 1.0f);
	return outputColor;
}

glm::vec3 compute_color(Ray const& r, std::vector<Hittable*> const& world, int max_depth)
{
	if (max_depth <= 0)
		return glm::vec3(0.0f); //we hit the bottom of the recursion, no more ray trace
	else
	{
		HitRecord record;
		if (trace_ray(r, world, 0.001f, 32.0f, record))
		{
			glm::vec3 diffuseColor = glm::vec3(0.0f);
			glm::vec3 specularColor = glm::vec3(0.0f);
			const glm::vec3 V = normalize(r.origin - record.position);

			//Compute diffuse lighting
			{
				Ray diffuseRay = record.material->computeDiffuseRay(r, &record);
				float NoH = std::max(0.0f, glm::dot(record.normal, glm::normalize(diffuseRay.direction + V)));
				float maxSpec = 1.0f - std::max(record.material->specularR.r, std::max(record.material->specularR.g, record.material->specularR.b));

				diffuseColor += compute_color(diffuseRay, world, max_depth - 1) * std::max(0.0f, glm::dot(diffuseRay.direction, record.normal)) *
					(1.0f - fresnel_schlick(NoH, record.material->specularR)) * ((maxSpec * record.material->albedo) / g_PI);
			}

			//Compute specular lighting
			{
				if (record.material->roughness <= 0.99995f)
				{
					Ray specularRay = record.material->computeSpecularRay(r, &record);
					if (glm::dot(specularRay.direction, record.normal) > 0)
					{
						float NoH = std::max(0.0f, glm::dot(record.normal, glm::normalize(specularRay.direction + V)));
						specularColor += compute_color(specularRay, world, max_depth - 1) * std::max(0.0f, glm::dot(specularRay.direction, record.normal))
							* fresnel_schlick(NoH, record.material->specularR) * record.material->specularR;
					}
				}
			}
			if(max_depth == gp_MaxRaysDepth)
				return diffuseColor + specularColor;
			else
				return (diffuseColor * (1.0f / 2.0f*g_PI)) + specularColor;
		}

		//ray miss, return sky color
		return sky(r);
	}
}

int main(int argc, char const *argv[])
{
    printf("CPU RTX\n");
    //initialize and fetch some variables from cmd line args
	argsResult argsRes = parseCmdlineArgs(argc, argv);
	int height = int(argsRes.height);
	int width = int(argsRes.width);
	
	//reset random seed
	resetRNGSeed();

	//camera setup
	const glm::vec2 imageResolution = glm::vec2(float(width), float(height));
	const float aspectRatio = imageResolution.x / imageResolution.y;
	constexpr float fov = 90.0f;
	const glm::vec3 cameraPosition = glm::vec3(2.0f, 1.0f, 1.0f);
	const glm::vec3 cameraLookAt = glm::vec3(0.0f, 0.0f, -1.5f);
	const glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	const float cameraFocusDist = 2.8f;
	constexpr float cameraAperture = 1.0f;
	Camera cam(fov, aspectRatio, cameraAperture, cameraFocusDist, cameraPosition, cameraLookAt, cameraUp);

	//scene setup
	Material floorMat = Material({ glm::vec3(0.01f) });//	https://www.beautycolorcode.com/ff6600
	floorMat.roughness = 0.16f;
	floorMat.specularR = glm::vec3(0.4f);
	Material sphereMat = Material({ glm::vec3(0.4f, 0.0f, 1.0f) });//	https://www.beautycolorcode.com/6600ff
	Material sphereMat2 = Material({ glm::vec3(0.75164f, 0.60648f, 0.22648f) });// gold
	sphereMat2.roughness = 0.005f;
	sphereMat2.specularR = glm::vec3(0.628281f, 0.555802f, 0.366065f);
	Material sphereMat3 = Material({ glm::vec3(0.714f, 0.4284f, 0.18144f) });// bronze
	sphereMat3.roughness = 0.05f;
	sphereMat3.specularR = glm::vec3(0.393548f, 0.271906f, 0.166721f);

	std::vector<Hittable*> world = { new Sphere({glm::vec3(1.0f, 0.0f, -1.0f), 0.5f, &sphereMat}),
									 new Sphere({glm::vec3(-1.0f, 0.0f, -1.0f), 0.5f, &sphereMat2}),
									 new Sphere({glm::vec3(0.0f, 0.0f, -1.0f), 0.5f, &sphereMat3}),
									 new Plane({glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0, -0.5, 0.0f), &floorMat}) };

	//image buffer allocation
	std::vector<std::vector<glm::vec3>> image(width, std::vector<glm::vec3>(height, glm::vec3(0.0f)));

	//ray tracing loop
	const double pixelCount = double(width) * double(height) - 1;
	double currentPixelID = 0.0;
	double progress = 0.0;
	for (int py = height - 1; py >= 0; py--)
	{
		for (int px = 0; px < width; px++)
		{
			//trace rays
			glm::vec3 color = glm::vec3(0.0f);
			glm::vec2 pixelCoordJitter = glm::vec2(0.0f);
			const glm::vec2 pixelCoordinates = glm::vec2(float(px), float(py));
			for (int i = 0; i < gp_SuperSamplingCount; i++)
			{
				pixelCoordJitter = glm::vec2(randomNumberGen(), randomNumberGen());
				glm::vec2 uv = (pixelCoordinates + pixelCoordJitter) / imageResolution;

				Ray r = cam.getRD(uv);
				color += compute_color(r, world, gp_MaxRaysDepth);
			}
			color /= float(gp_SuperSamplingCount);
			
			//linear to gamma colorspace
			color = glm::pow(color, glm::vec3(g_invGamma));
			
			//write to image buffer
			image[px][py] = color;
			
			//update progress bar
			progress = (currentPixelID / pixelCount);
			currentPixelID += 1.0;
			printProgressBar(progress);
		}
	}

	//output file
	write_ppm_binary(argsRes.outputPath, image, width, height);

    return 0;
}