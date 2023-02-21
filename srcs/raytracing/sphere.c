#include "../../incs/raytracing.h"
#include <math.h>

double			get_distance_to_sphere(void *object, t_ray ray);
t_ray			get_normal_of_sphere(void *object, t_vec3 contact);
static double	get_distance_by_discriminant(double a, double half_b, double c);

double	get_distance_to_sphere(void *object, t_ray ray)
{
	t_sphere *const	sphere = (t_sphere *) object;
	const t_vec3	oc = vec3_sub(ray.origin, sphere->center);
	const double	a = vec3_dot(ray.direction, ray.direction);
	const double	half_b = vec3_dot(oc, ray.direction);
	const double	c = vec3_dot(oc, oc) - sphere->radius * sphere->radius;

	return (get_distance_by_discriminant(a, half_b, c));
}

t_ray	get_normal_of_sphere(void *object, t_vec3 contact)
{
	t_sphere *const	sphere = (t_sphere *) object;

	return (
		(t_ray){
			contact,
			vec3_unit(vec3_sub(contact, sphere->center))
		}
	);
}

static double	get_distance_by_discriminant(double a, double half_b, double c)
{
	double	discriminant;
	double	t1;
	double	t2;

	discriminant = pow(half_b, 2) - a * c;
	if (discriminant < 0)
		return (INF);
	discriminant = sqrt(discriminant);
	t1 = (-half_b - discriminant) / a;
	t2 = (-half_b + discriminant) / a;
	if (t1 < 0 && t2 < 0)
		return (INF);
	if (t1 < 0)
		return (t2);
	if (t2 < 0)
		return (t1);
	return (fmin(t1, t2));
}
