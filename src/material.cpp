#include <material.h>
#include <hittable.h>
#include <utils.h>

Ray Material::computeDiffuseRay(Ray const & incidentRay, HitRecord const * record) const
{
	glm::vec3 sampleDirection = (record->position + record->normal + glm::vec3(randomNumberGen(), randomNumberGen(), randomNumberGen()) - record->position);
	sampleDirection = glm::normalize(sampleDirection);
	return Ray(record->position, sampleDirection);
}

Ray Material::computeSpecularRay(Ray const & incidentRay, HitRecord const * record) const
{
	glm::vec3 R = glm::reflect(incidentRay.direction, record->normal) + glm::vec3(randomNumberGen(), randomNumberGen(), randomNumberGen()) * roughness;
	R = glm::normalize(R);
	return Ray(record->position, R);
}
