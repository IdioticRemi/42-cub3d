#include "cub3d.h"




int	convert_color_number(int r, int g, int b)
{
	int	color;

	color = r * (256 * 256) + g * 256 + b;
	return (color);
}

int	get_color_number(char *color_info)
{
	char	**color;
	int	r;
	int	g;
	int	b;

	color = ft_split(color_info, ','); //handle ' '?
	r = ft_atoi(color[0]);
	g = ft_atoi(color[1]);
	b = ft_atoi(color[2]);

	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		error_message_exit("Invalid color number");
	return (convert_color_number(r, g, b));
}

int	map_check_extension(char *filename, char *ext)
{
	int	i;
	int	j;

	if(ext[0] != '.')
		error_message_exit("Invalid extension");
	i = ft_strlen(filename) - ft_strlen(ext);
	j = 0;
	while (filename[i + j] && ext[j])
	{
		if (filename[i + j] != ext[j])
			error_message_exit("Invalid file extension");
		j++;
	}
	return (1);
}

int	check_valid_character(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'W' && line[i] != 'E')
			return (ERROR);
		i++;
	}
	return (EXIT_SUCCESS);
}

/* IDとPath切る　
スペースでSplitした文字列を２D配列に代入して
［0］のIDが正しいか判断
［1］のPathが正しいか判断
IDに沿ってPath情報をStructの変数に代入
最後に配列をフリー
*/

char	**get_id_and_path(char *str)
{
	char **ret;
	ret = ft_split(str, ' ');
	if (!ret)
		error_message_exit("Info failed");
	return (ret);
}

/* 切ったIDが正しいか判断　*/
char	check_identifier(char *str)
{
/* check first letters of the str and identify the identifier*/
	char	id;
	int		i;

	i = 0;
	id = '\0';
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if ((str[i] == 'N' && str[i + 1] == ' ') || (str[i] == 'N' && str[i + 1] == 'O'))
		id = 'N';
	else if ((str[i] == 'S' && str[i + 1] == ' ') || (str[i] == 'S' && str[i + 1] == 'O'))
		id = 'S';
	else if ((str[i] == 'W' && str[i + 1] == ' ') || (str[i] == 'W' && str[i + 1] == 'E'))
		id = 'W';
	else if ((str[i] == 'E' && str[i + 1] == ' ') || (str[i] == 'E' && str[i + 1] == 'A'))
		id = 'E';
	else if (str[i] == 'F')
		id = 'F';
	else if (str[i] == 'C')
		id = 'C';
	else
		error_message_exit("Invalid identifier");
	return (id);
}

void		save_info(t_cub *cub, char **info_str)
{
// store each info to texture structure by identifier
	int		i;
	char	id;
	i = 0;
	id = check_identifier(info_str[0]);
	if (id == 'N')
		cub->info.n_path = ft_strdup(info_str[1]);
	else if (id == 'S')
		cub->info.s_path = ft_strdup(info_str[1]);
	else if (id == 'W')
		cub->info.w_path = ft_strdup(info_str[1]);
	else if (id == 'E')
		cub->info.e_path = ft_strdup(info_str[1]);
	else if (id == 'F')
		cub->info.floor = get_color_number(info_str[1]);
	else if (id == 'C')
		cub->info.ceiling = get_color_number(info_str[1]);
}

int		check_valid_texture_path(char *path)
{
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		error_message_exit("Invalid path");
	return (0);
}


int		map_read_file(char *file_path);


/*
上部の情報　・　下部のMAP どうわける？ -- どこからMAPが始まるか判断する
MAPの始まる箇所から終わりまで新しい２D配列にコピーする。
コピーしたMAP配列をつかってMAPのチェック
*/

/*
Error cases

- invalid identifier
- identifier must be followed by ' ' tab;
- invalid path (path doesn't open) or color info
- invalid char inside map
- map is not walled
- more than one player

*/


