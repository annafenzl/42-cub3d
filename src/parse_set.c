# include "../inc/cub3d.h"

void	set_to_default(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		cub->tex_dir[i] = NULL;
		i++;
	}
	cub->ceiling_color = -1;
	cub->floor_color = -1;
	cub->mp_height = 0;
	cub->mp_width = 0;
	cub->input = NULL;
	cub->map = NULL;
	cub->window.player_x = 0;
	cub->window.player_y = 0;
}

void	set_textures(t_cub *cub, char	**line, int direction)
{
	int	fd;

	if (ft_splitlen(line) != 2)
		print_error_msg("Not the right amount of arguments for the texture file", cub);
	fd = open(line[1], O_RDONLY);
	if (fd < 0)
		print_error_msg("Texture file cant be opened", cub);
	close(fd);
	cub->tex_dir[direction] = mlx_load_png(line[1]);
	if (cub->tex_dir[direction] == NULL)
		print_error_msg("Texture file not a valid file format or empty", cub);
}

int	convert_to_number(char	*str)
{
	int	i;

	i = 0;
	while (str && str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0)
			return (-1);
		i++;
	}
	return (ft_atoi(str));
}

int	set_colores(char **rgb, t_cub *cub)
{
	int		r;
	int		g;
	int		b;

	if (ft_splitlen(rgb) != 3)
	{
		free(rgb);
		print_error_msg("please enter RGB in following manner: '255,255,255'.", cub);
	}
	r = convert_to_number(rgb[0]);
	g = convert_to_number(rgb[1]);
	b = convert_to_number(rgb[2]);
	printf("RED: %i, GREEN: %i, BLUE %i\n", r, g, b);
	if (r < 0 || g < 0 || b < 0
		|| r > 255 || g > 255 || b > 255)
		print_error_msg("number input invalid.", cub);
	ft_free2(rgb);
	return (r << 24 | g << 16 | b << 8 | 255);
}


void	set_directions(char dir, t_window *window)
{
	if (dir == 'N')
	{
		window->dir_x = -1;
		window->dir_y = 0;
		window->plane_x = 0;
		window->plane_y = 0.66;
	}
	else if (dir == 'S')
	{
		window->dir_x = 1;
		window->dir_y = 0;
		window->plane_x = 0;
		window->plane_y = -0.66;
	}
	else if (dir == 'W')
	{
		window->dir_x = 0;
		window->dir_y = 1;
		window->plane_x = -0.66;
		window->plane_y = 0;
	}
	else if (dir == 'E')
	{
		window->dir_x = 0;
		window->dir_y = -1;
		window->plane_x = 0.66;
		window->plane_y = 0;
	}
}