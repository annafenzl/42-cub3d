# include "../inc/cub3d.h"

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
				set_textures(cub, line, north);
			else if (ft_strncmp(line[0], "SO", 3) == 0 && !cub->tex_dir[south])
				set_textures(cub, line, south);
			else if (ft_strncmp(line[0], "WE", 3) == 0 && !cub->tex_dir[west])
				set_textures(cub, line, west);
			else if (ft_strncmp(line[0], "EA", 3) == 0 && !cub->tex_dir[east])
				set_textures(cub, line, east);
			free(line);
		}
		i++;
	}
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
				cub->floor_color = set_colores(ft_split(line[1], ','), cub);
			else if (ft_strncmp(line[0], "C", 2) == 0)
				cub->ceiling_color = set_colores(ft_split(line[1], ','), cub);
			ft_free2(line);
		}
		i++;
	}
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