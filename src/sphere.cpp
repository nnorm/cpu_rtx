#include <sphere.h>

bool Sphere::hit(Ray const & ray, float tmin, float tmax, HitRecord & record) const
{
	const float PI = 3.14159265359f;
	glm::vec3 origin_center_vector = ray.origin - center;
	//quadratic equation (ax² + bx + c) factors:
	float a = glm::dot(ray.direction, ray.direction);
	float b = glm::dot(origin_center_vector, ray.direction);
	float c = glm::dot(origin_center_vector, origin_center_vector) - (radius * radius);

	//quadratic discriminant:
	float discriminant = b * b - a * c;
	if (discriminant >= 0)
	{
		float temp = (-b - sqrtf(b*b - a * c)) / a;
		if (temp < tmax && temp > tmin)
		{
			record.t = temp;
			record.position = ray.compute_position(record.t);
			record.normal = glm::normalize(record.position - center);
			record.material = material;
			record.textureCoords = glm::vec2(asinf(record.normal.x) / PI, asinf(record.normal.y) / PI ) + 0.5f;
			return true;
		}
		temp = (-b + sqrtf(b*b - a * c)) / a;
		if (temp < tmax && temp > tmin)
		{
			record.t = temp;
			record.position = ray.compute_position(record.t);
			record.normal = glm::normalize(record.position - center);
			record.material = material;
			record.textureCoords = glm::vec2(asinf(record.normal.x) / PI, asinf(record.normal.y) / PI) + 0.5f;
			return true;
		}
	}
	return false;
}