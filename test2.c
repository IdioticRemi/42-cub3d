#include <stdio.h>
#include <math.h>

typedef struct s_vec
{
	double		x;
	double		y;
} t_vec;

t_vec	new_vector(double x, double y)
{
	t_vec	ret;

	ret.x = x;
	ret.y = y;
	return (ret);
}

double cal_vector_len(t_vec *v)
{
	return sqrtf((v->x * v->x) + (v->y * v->y));
}

int		main(void)
{
	t_vec	zero_vec;
	t_vec	unit_vec;

	zero_vec = new_vector(0.0f, 0.0f);
	unit_vec = new_vector(1.0f, 0.0f);

	printf("zero vector : %.2f %.2f\n  vector size : %.2f\n\n", zero_vec.x, zero_vec.y, cal_vector_len(&zero_vec));
	printf("unit vector : %.2f %.2f\n  vector size : %.2f\n\n", unit_vec.x, unit_vec.y, cal_vector_len(&unit_vec));

/*
zero vectorはすべての要素が０のベクトルを意味する。初期化の際によく使われる。
Unit vector（単位ベクトル）はx軸の方向に方向をもつベクトルである。
*/


	return 0;
}

