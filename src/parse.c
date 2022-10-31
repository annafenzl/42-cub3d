/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:14:14 by afenzl            #+#    #+#             */
/*   Updated: 2022/10/31 14:49:39 by afenzl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	check_path(char const *path)
{
	int		fd;
	int		i;

	fd = open(path, O_RDONLY);
	if (fd <= 0)
	{
		close(fd);
		print_error_msg("The file doesn't exist or does not have the right rights.", NULL);
	}
	close(fd);
	i = ft_strlen(path);
	if (path[i - 4] != '.' || path[i - 3] != 'c'
		|| path[i - 2] != 'u' || path[i - 1] != 'b')
		print_error_msg("The file doesnt have the right format, it should end with '.cub'.", NULL);
}

char	**read_file(char *infile)
{
	int		line_number;
	int		fd;
	char	*tmp;
	char	*lines;
	char	**ret;

	tmp = ft_strdup("");
	lines = ft_strdup("");
	fd = open(infile, O_RDONLY);
	line_number = 0;
	while (tmp != NULL)
	{
		free(tmp);
		tmp = get_next_line(fd);
		if (tmp != NULL)
		{
			if ((line_number == 4 && ft_strncmp(tmp, "\n", 2) != 0)
				|| (line_number == 7 && ft_strncmp(tmp, "\n", 2) != 0)
				|| (line_number > 7 && ft_strncmp(tmp, "\n", 2) == 0))
				print_error_msg("File invalid! (empty line)\n", NULL);
			lines = ft_strjoin_free(lines, tmp);
		}
		line_number++;
	}
	close(fd);
	ret = ft_split(lines, '\n');
	free(lines);
	return (ret);
}

void	check_textures(t_cub *cub, char	**line, int direction)
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

void	get_textures(t_cub *cub)
{
	int		i;
	char	**line;

	i = 0;
	line = NULL;
	while (cub->input && cub->input[i] && i < 4)
	{
		line = ft_split(cub->input[i], ' ');
		if (line != NULL)
		{
			if (ft_strncmp(line[0], "NO", 3) == 0 && !cub->tex_dir[north])
				check_textures(cub, line, north);
			else if (ft_strncmp(line[0], "SO", 3) == 0 && !cub->tex_dir[south])
				check_textures(cub, line, south);
			else if (ft_strncmp(line[0], "WE", 3) == 0 && !cub->tex_dir[west])
				check_textures(cub, line, west);
			else if (ft_strncmp(line[0], "EA", 3) == 0 && !cub->tex_dir[east])
				check_textures(cub, line, east);
			free(line);
		}
		i++;
	}
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

int	fill_colores(char **rgb, t_cub *cub)
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

void	get_colores(t_cub	*cub)
{
	int		i;
	char	**line;

	line = NULL;
	i = 4;
	while (i <= 5 && cub->input && cub->input[i])
	{
		line = ft_split(cub->input[i], ' ');
		if (line != NULL)
		{
			if (ft_splitlen(line) != 2)
				print_error_msg("please enter RGB in following manner: '255,255,255'.", cub);
			if (ft_strncmp(line[0], "F", 2) == 0)
				cub->floor_color = fill_colores(ft_split(line[1], ','), cub);
			else if (ft_strncmp(line[0], "C", 2) == 0)
				cub->ceiling_color = fill_colores(ft_split(line[1], ','), cub);
			ft_free2(line);
		}
		i++;
	}
}

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

int	check_player(t_cub *cub, int y, int x)
{
	char	dir;

	dir = cub->map[y][x];
	if (dir == 'N' || dir == 'S'
		|| dir == 'W' || dir == 'E')
	{
		cub->window.player_x = x + 0.5;
		cub->window.player_y = y + 0.5;
		cub->map[y][x] = '0';
		set_directions(dir, &cub->window);
		return (1);
	}
	return (0);
}

void	check_walls(t_cub *cub, int y, int x)
{
	if (cub->map[y][x] != '1' && cub->map[y][x] != '0'
		&& ft_skip_whitespace(&cub->map[y][x]) == 0)
		print_error_msg("Invalid character in map.", cub);
	if (cub->map[y][x] == '0')
	{
		if (y == 0 || x == 0
			|| ft_skip_whitespace(&cub->map[y - 1][x]) != 0
			|| ft_skip_whitespace(&cub->map[y][x - 1]) != 0
			|| ft_skip_whitespace(&cub->map[y][x + 1]) != 0
			|| cub->map[y][x + 1] == '\0'
			|| y == ft_splitlen(cub->map) - 1
			|| x >= (int)ft_strlen(cub->map[y - 1])
			|| (cub->map[y + 1] && x >= (int)ft_strlen(cub->map[y + 1])))
			print_error_msg("Error: Map is leaking.", cub);
	}
}

void	check_map(t_cub *cub)
{
	int	x;
	int	player_found;

	player_found = 0;
	cub->map = ft_splitdup(&cub->input[6]);
	while (cub->map && cub->map[cub->mp_height])
	{
		x = 0;
		while (cub->map[cub->mp_height][x] != '\0')
		{
			if (x > cub->mp_width)
				cub->mp_width = x + 1;
			player_found += check_player(cub, cub->mp_height, x);
			check_walls(cub, cub->mp_height, x);
			x++;
		}
		cub->mp_height++;
	}
	if (player_found != 1)
		print_error_msg("please enter ONE player, either 'N', 'S', 'W' or 'E'", cub);
}

void	check_if_complete(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (cub->tex_dir[i] == NULL)
			print_error_msg("missing texture.", cub);
		i++;
	}
	if (cub->floor_color == -1 || cub->ceiling_color == -1)
		print_error_msg("missing colour.", cub);
}

int	parse(char *infile, t_cub *cub)
{
	set_to_default(cub);
	check_path(infile);
	cub->input = read_file(infile);
	get_textures(cub);
	get_colores(cub);
	check_if_complete(cub);
	check_map(cub);
	return (0);
}
