#include <plane.h>
#include <glm.hpp>
#include <gtx/intersect.hpp>
bool Plane::hit(Ray const & ray, float tmin, float tmax, HitRecord & record) const
{
	float t = 0.0f;

	if (glm::intersectRayPlane(ray.origin, ray.direction, origin, normal, t))
	{
		if (t < tmax && t >= tmin)
		{
			record.t = t;
			record.position = ray.compute_position(record.t);
			record.normal = normal;
			record.material = material;
			record.textureCoords = glm::vec2(normal.x, normal.y);
			return true;
		}
	}

	return false;
}
