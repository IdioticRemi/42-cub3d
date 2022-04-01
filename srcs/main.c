#include "cub3d.h"

int	game_loop(t_cub *cub)
{
	if (cub->status == GAME_START)
		// display start message;
	if (cub->status == GAME_PLAY)
	{
		//put window;
	}
	return 0;
}

int main(int argc, char **argv)
{
	char		*map_path;
	t_cub		cub;

	if (argc != 2)
		//display error
	map_path = argv[1];
	cub.status = GAME_START;
	//map check
	//initiate game

	return (0);
}