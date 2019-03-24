#ifndef _PLANE_H_
#define _PLANE_H_
#pragma once
#include <hittable.h>
#include <glm.hpp>
struct Plane
	: Hittable
{
	Plane(glm::vec3 const& n = glm::vec3(0.0f), glm::vec3 const& o = glm::vec3(0.0f), Material* mat = new Material())
		: normal(glm::normalize(n)), origin(o), material(mat)
	{}

	//Data
	glm::vec3 normal;
	glm::vec3 origin;
	Material* material;

	//Hit function
	bool hit(Ray const& ray, float tmin, float tmax, HitRecord& record) const override;
};

#endif // _PLANE_H_