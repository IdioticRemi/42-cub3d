#include "./mlx/mlx.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define KEY_W	13
#define KEY_A	0
#define KEY_S	1
#define KEY_D	2

#define KEY_ESC	53

#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480

#define X_EVENT_KEY_PRESS 2
#define X_EVENT_KEY_EXIT 17

typedef struct s_info
{
	double	playerPositionX;
	double	playerPositionY;
	double	directionVectorX;
	double	directionVectorY;
	double	planeX;
	double	planeY;
	void	*mlx;
	void	*win;
	double	moveSpeed;
	double	rotSpeed;
} t_info;


int worldMap[mapWidth][mapHeight] =
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

// int worldMap[mapWidth][mapHeight] =
// {
// 	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,1,0,1,0,2,0,1,0,1,0,0,0,1},
// 	{1,0,0,0,0,0,2,0,0,1,1,1,1,1,1},
// 	{1,1,1,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,1,1,1,1,0,0,0,0,0,1},
// 	{1,0,0,0,0,1,0,1,0,0,0,0,0,0,1},
// 	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
// };

void	verLine(t_info *info, int x, int y1, int y2, int color)
{
	int temp;

	temp = y1;
	while (temp <= y2)
	{
		mlx_pixel_put(info->mlx, info->win, x, temp, color);
		temp++;
	}
}

int main_loop(t_info *info)
{
	int x;

	x = 0;
	while (x < screenHeight)
	{
		double cameraX = (2 * x / (double)(screenWidth)) - 1;
		// 光の方向
	// printf("camera: %f\n", cameraX);

		double rayDirectionX = info->directionVectorX + info->planeX * cameraX;
		double rayDirectionY = info->directionVectorY + info->planeY * cameraX;
	// printf("RaydirX: %f | RaydirY: %f | FovDirX: %f | FovDirY: %f | planeX: %f | planeY: %f\n", rayDirectionX, rayDirectionY, info->directionVectorX, info->directionVectorY, info->planeX, info->planeY);
		int mapX = (int)(info->playerPositionX);
		int mapY = (int)(info->playerPositionY);

		double sideDistX;
		double sideDistY;

		double deltaDistX = sqrt(1 + (rayDirectionY * rayDirectionY) / (rayDirectionX * rayDirectionX));//fabs(1 / rayDirectionX);
		double deltaDistY = sqrt(1 + (rayDirectionX * rayDirectionX) / (rayDirectionY * rayDirectionY));//fabs(1 / rayDirectionY);

// printf("dirX: %f | dirY: %f | mapX: %d | mapY: %d\n", rayDirectionX, rayDirectionY, mapX, mapY);

// printf("rayMapX: %d | rayMapY: %d | deltaX: %f | deltaY: %f\n", mapX, mapY, deltaDistX, deltaDistY);
		double perpWallDist;

		int stepX;
		int stepY;
	
		int hit = 0;
		int side;

		if (rayDirectionX < 0)
		{
			stepX = -1;
			sideDistX = (info->playerPositionX - mapX) * deltaDistX;
		// printf("posX: %f | mapX: %d\n", info->playerPositionX, mapX);
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - info->playerPositionX) * deltaDistX;
		}
		if (rayDirectionY < 0)
		{
			stepY = -1;
			sideDistY = (info->playerPositionY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - info->playerPositionY) * deltaDistY;
		}
// printf("sideDistX: %f | sideDistY: %f\n", sideDistX, sideDistY);
		while (hit == 0)
		{
			printf("sideX 1: %f | sideY: %f | mapX 1: %d | mapY 2: %d\n", sideDistX, sideDistY, mapX, mapY);
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
// printf("deltaX: %f | deltaY: %f | sidedistX: %f | sidedistY: %f\n", deltaDistX, deltaDistY, sideDistX, sideDistY);
			if (worldMap[mapX][mapY] > 0)
				hit = 1;
			printf("sideX 2: %f | sideY 2: %f | mapX 2: %d | mapY 2: %d | hit: %d\n --------------\n", sideDistX, sideDistY, mapX, mapY, hit);
		}
		//魚眼対処

       	// printf("raydirety:%f | ", rayDirectionY);
       	// printf("mapX: %d | ", mapX);		   
       	// printf("mapY: %d \n", mapY);
		if (side == 0)
			perpWallDist = (mapX - info->playerPositionX + (1 - stepX) / 2) / rayDirectionX;
		else
			perpWallDist = (mapY - info->playerPositionY + (1 - stepY) / 2) / rayDirectionY;
// printf("posX: %f | posY: %f | raydirX: %f | raydirY: %f\n", info->playerPositionX, info->playerPositionY, rayDirectionX, rayDirectionY);
		//スクリーンに映すラインの高さを計算
		int lineHeight = (int)(screenHeight / perpWallDist);
	// printf("lineheight: %d | perpWall: %f | mapX: %d | mapY: %d\n", lineHeight, perpWallDist, mapX, mapY);
		int	drawStart = (-lineHeight / 2) + (screenHeight / 2);
	// printf("drawStart:%d\n", drawStart);
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = (lineHeight/2) + (screenHeight / 2);
		if (drawEnd >= screenHeight)
			drawEnd = screenHeight - 1;

		int color;
		if (worldMap[mapX][mapY] == 1)
			color = 0xFF0000;
		else if (worldMap[mapX][mapY] == 2)
			color = 0x00FF00;
		else if (worldMap[mapX][mapY] == 3)
			color = 0x0000FF;
		else if (worldMap[mapX][mapY] == 4)
			color = 0xFFFFFF;
		else
			color = 0x123145;

		//明るさ調整
		if (side == 1)
			color = color / 2;
		
		verLine(info, x, drawStart, drawEnd, color);
		x++;
	}
	return 0;
}

int	key_press(int key, t_info *info)
{
	if (key == KEY_W)
	{//０であれば動く
		if (!worldMap[(int)(info->playerPositionX + info->directionVectorX * info->moveSpeed)][(int)(info->playerPositionY)])
			info->playerPositionX += info->directionVectorX * info->moveSpeed;
		if (!worldMap[(int)(info->playerPositionX)][(int)(info->playerPositionY + info->directionVectorY * info->moveSpeed)])
			info->playerPositionX += info->directionVectorY * info->moveSpeed;

	}

	if (key == KEY_S)
	{
		if (!worldMap[(int)(info->playerPositionX - info->directionVectorX * info->moveSpeed)][(int)(info->playerPositionY)])
			info->playerPositionX -= info->directionVectorX * info->moveSpeed;
		if (!worldMap[(int)(info->playerPositionX)][(int)(info->playerPositionY - info->directionVectorY * info->moveSpeed)])
			info->playerPositionX -= info->directionVectorY * info->moveSpeed;
	}

	if (key == KEY_A)
	{
		double oldDirectionX = info->directionVectorX;
		info->directionVectorX = info->directionVectorX * cos(info->rotSpeed) - info->directionVectorY * sin(info->rotSpeed);
		info->directionVectorY = oldDirectionX * sin(info->rotSpeed) + info->directionVectorY * cos(info->rotSpeed);
	
		double oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(info->rotSpeed) - info->planeY * sin(info->rotSpeed);
		info->planeY = oldPlaneX * sin(info->rotSpeed) + info->planeY * cos(info->rotSpeed);
	
	}

	if (key == KEY_D)
	{
		double oldDirectionX = info->directionVectorX;
		info->directionVectorX = info->directionVectorX * cos(-info->rotSpeed) - info->directionVectorY * sin(-info->rotSpeed);
		info->directionVectorY = oldDirectionX * sin(-info->rotSpeed) + info->directionVectorY * cos(-info->rotSpeed);

		double oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(-info->rotSpeed) - info->planeY * sin(-info->rotSpeed);
		info->planeY = oldPlaneX * sin(-info->rotSpeed) + info->planeY * cos(-info->rotSpeed);
	}

	if (key == KEY_ESC)
		exit(0);
	return(0);
}

int main()
{
	t_info info;
	info.mlx = mlx_init();

	info.playerPositionX = 7;
	info.playerPositionY = 4;
	info.directionVectorX = -1;
	info.directionVectorY = 0;
	info.planeX = 0;
	info.planeY = 0.66;
	info.moveSpeed = 0.05;
	info.rotSpeed = 0.05;

	info.win = mlx_new_window(info.mlx, screenWidth, screenHeight, "mlx");

	mlx_loop_hook(info.mlx, &main_loop, &info);
	mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, &key_press, &info);
	mlx_loop(info.mlx);

}






