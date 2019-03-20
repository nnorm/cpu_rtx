#ifndef _RAY_H_
#define _RAY_H_
#pragma once
#include <glm.hpp>
struct Ray
{
	Ray(glm::vec3 const& ro = glm::vec3(), glm::vec3 const& rd = glm::vec3()) : origin(ro), direction(rd) {};
	glm::vec3 origin;
	glm::vec3 direction;
	inline glm::vec3 compute_position(float t) const { return origin + (direction * t); }
};
#endif //_RAY_H_