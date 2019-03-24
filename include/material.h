#ifndef _MATERIAL_H_
#define _MATERIAL_H_
#pragma once
#include <glm.hpp>
#include <ray.h>
struct HitRecord;

struct Material
{
	glm::vec3 albedo = glm::vec3(0.0f);
	glm::vec3 specularR = glm::vec3(0.0f);
	float roughness = 1.0f;

	Ray computeDiffuseRay(Ray const& incidentRay, HitRecord const* record) const;
	Ray computeSpecularRay(Ray const& incidentRay, HitRecord const* record) const;

};
#endif //_MATERIAL_H_
