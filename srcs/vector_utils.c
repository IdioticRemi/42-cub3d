#include "cub3d.h"

t_vector	set_vector(float x, float y)
{
	t_vector	ret;

	ret.x = x;
	ret.y = y;
	return (ret);
}

t_vector	vector_add(t_vector vec, t_vector to_add)
{
	vec.x += to_add.x;
	vec.y += to_add.y;
	return (vec);
}

t_vector	vector_subs(t_vector vec, t_vector to_sub)
{
	vec.x -= to_sub.x;
	vec.y -= to_sub.y;
	return (vec);
}

t_vector	vector_multi(t_vector vec, float num)
{
	vec.x *= num;
	vec.y *= num;
	return (vec);
}