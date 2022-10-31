/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:14:14 by afenzl            #+#    #+#             */
/*   Updated: 2022/10/31 15:12:50 by afenzl           ###   ########.fr       */
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
