#include "mlx/mlx.h"

typedef struct s_data
{
	void	*ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int main ()
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_data	img;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "test");
	img.ptr = mlx_new_image(mlx_ptr, 500, 500);
	img.addr = mlx_get_data_addr(img.ptr, &img.bits_per_pixel, &img.line_length, &img.endian);
	for (int i = 50; i < 150; i++)
	{
		my_mlx_pixel_put(&img, i, 50, 0xfff5ee);
		my_mlx_pixel_put(&img, 50, i, 0xfff5ee);
		my_mlx_pixel_put(&img, i, 150, 0xfff5ee);
		my_mlx_pixel_put(&img, 150, i, 0xfff5ee);
	}
	mlx_put_image_to_window(mlx_ptr, win_ptr, img.ptr, 0, 0);
	mlx_loop(mlx_ptr);
}

