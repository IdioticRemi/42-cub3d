#include "cub3d.h"

t_vect	set_vector(float x, float y)
{
	t_vect	ret;

	ret.x = x;
	ret.y = y;
	return (ret);
}

t_vect	vector_add(t_vect vec, t_vect to_add)
{
	vec.x += to_add.x;
	vec.y += to_add.y;
	return (vec);
}

t_vect	vector_subs(t_vect vec, t_vect to_sub)
{
	vec.x -= to_sub.x;
	vec.y -= to_sub.y;
	return (vec);
}

t_vect	vector_multi(t_vect vec, float num)
{
	vec.x *= num;
	vec.y *= num;
	return (vec);
}