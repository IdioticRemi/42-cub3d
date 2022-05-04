#include "cub3d.h"

t_vect	collision_handler(t_cub *cub)
{
	t_vect	direction;
	t_vect	finalPos;

	direction = set_vector(cub->cam.yaw + FOV / 2, cub->cam.yaw + FOV / 2);
	if (cub->keys.key_w)
		direction = vector_add(direction, set_vector(0, 0));
	else if (cub->keys.key_s)
		direction = vector_add(direction, set_vector(PI, PI));
	else if (cub->keys.key_a)
		direction = vector_subs(direction, set_vector(PI / 2, PI / 2));
	else if (cub->keys.key_d)
		direction = vector_add(direction, set_vector(PI / 2, PI / 2));
	direction = set_vector(cos(direction.x), sin(direction.y));
	direction = vector_multi(direction, MOVE_SPEED);
	finalPos = vector_add(cub->player.pos, direction);
	if (cub->map.array[(int)(finalPos.x / TILE_SIZE)][(int)(finalPos.y / TILE_SIZE)] == '1')
		direction = set_vector(0, 0);
	return (direction);
}
