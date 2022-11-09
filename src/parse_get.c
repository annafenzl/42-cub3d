/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:28:43 by afenzl            #+#    #+#             */
/*   Updated: 2022/11/02 17:09:00 by afenzl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// void	free_three(void *ptr1, void *ptr2, void *ptr3)
// {
// 	if (ptr1)
// 		free(ptr1);
// 	if (ptr2)
// 		free(ptr2);
// 	if (ptr3)
// 		free(ptr3);
// }

char	*checks_in_read(char *tmp, char *tmp2, char *lines, bool *map_start)
{
	if (tmp2[0] == '1')
		*map_start = true;
	if (*map_start == true && ft_strncmp(tmp2, "\n", 2) == 0)
	{
		free(tmp);
		free(tmp2);
		free(lines);
		print_error_msg("Empty line in map.", NULL);
	}
	return (ft_strjoin_free(lines, tmp));
}

char	*read_file(char *infile)
{
	int		fd;
	char	*tmp;
	char	*tmp2;
	char	*lines;
	bool	map_start;

	tmp = ft_strdup("");
	tmp2 = ft_strdup("");
	lines = ft_strdup("");
	fd = open(infile, O_RDONLY);
	map_start = false;
	while (tmp != NULL)
	{
		free(tmp);
		free(tmp2);
		tmp = get_next_line(fd);
		tmp2 = ft_strtrim(tmp, " \t");
		if (tmp != NULL)
			lines = checks_in_read(tmp, tmp2, lines, &map_start);
	}
	close(fd);
	return (lines);
}

void	get_textures_and_color(t_cub *cub)
{
	int		i;
	char	*line;

	i = 0;
	while (i < 6)
	{
		line = cub->input[i];
		if (ft_strncmp(line, "NO ", 3) == 0 && !cub->tex_dir[north])
			set_textures(cub, line, north);
		else if (ft_strncmp(line, "SO ", 3) == 0 && !cub->tex_dir[south])
			set_textures(cub, line, south);
		else if (ft_strncmp(line, "WE ", 3) == 0 && !cub->tex_dir[west])
			set_textures(cub, line, west);
		else if (ft_strncmp(line, "EA ", 3) == 0 && !cub->tex_dir[east])
			set_textures(cub, line, east);
		else if (ft_strncmp(line, "F ", 2) == 0)
			cub->floor_color = set_colores(line, cub);
		else if (ft_strncmp(line, "C ", 2) == 0)
			cub->ceiling_color = set_colores(line, cub);
		else
			print_error_msg("invalid input.", cub);
		i++;
	}
}

int	parse(char *infile, t_cub *cub)
{
	char	*input;

	set_to_default(cub);
	check_path(infile);
	input = read_file(infile);
	cub->input = ft_split(input, '\n');
	free(input);
	get_textures_and_color(cub);
	check_map(cub);
	return (0);
}
