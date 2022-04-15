
/* 
error if negative || bigger than 255

From RGB color,  
R = (color >> 16) & 0xFF
G = (color >> 8 ) & 0xFF
B = color & 0xFF

How to get color when R, G, B are given:
color = R * 256² + G * 256 + B
color = (R << 16)  | ( G << 8) | B
 
*/
#include "../include/cub3d.h"

/* NSWE path */
void	get_texture_path(t_cub *cub)
{

}

int	convert_color_number(int r, int g, int b)
{
	int	color;
	int	red;
	int green;
	int blue;

	color = r * (256 * 256) + g * 256 + b;
	red = (color >> 16) & 0xFF;
	green = (color >> 8) & 0xFF;
	blue = color & 0xFF;

	return (color);
}

int	get_color_number(t_cub *cub, char *color_info)
{
	char	**color;
	int	r;
	int	g;
	int	b;

	color = ft_split(color_info, ','); //do i need to handle ' '?
	r = ft_atoi(color[0]);
	g = ft_atoi(color[1]);
	b = ft_atoi(color[2]);

	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		error_message_exit("invalid color number");
	return (convert_color_number(r, g, b));
}

