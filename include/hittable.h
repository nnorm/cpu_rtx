#ifndef _HITTABLE_H_
#define _HITTABLE_H_
#pragma once
#include <ray.h>
#include <glm.hpp>

struct HitRecord
{
	float t = 0.0f;
	glm::vec3 position;
	glm::vec3 normal;
};

struct Hittable
{
	virtual bool hit(Ray const& ray, float tmin, float tmax, HitRecord& record) const = 0;
};

#endif //_HITTABLE_H_
