#ifndef _SPHERE_H_
#define _SPHERE_H_
#pragma once
#include <hittable.h>
#include <glm.hpp>
struct Sphere
	: public Hittable
{
	Sphere(glm::vec3 const& c = glm::vec3(0.0f), float r = 0.5f, Material const& mat = Material())
		: center(c), radius(r), material(mat)
	{}
	//Object Attributes:
	glm::vec3 center;
	float radius;
	Material material;

	//Hit function
	bool hit(Ray const& ray, float tmin, float tmax, HitRecord& record) const override;
};

#endif //_SPHERE_H_
