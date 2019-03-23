#ifndef _MATERIAL_H_
#define _MATERIAL_H_
#pragma once
#include <glm.hpp>
#include <ray.h>
#include <hittable.h>
struct Material
{
	glm::vec3 albedo = glm::vec3(0.0f);
	glm::vec3 specularR = glm::vec3(0.0f);
	float roughness = 1.0f;
};
#endif //_MATERIAL_H_
