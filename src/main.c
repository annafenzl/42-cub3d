/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhamdiev <dhamdiev@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 14:46:10 by afenzl            #+#    #+#             */
/*   Updated: 2022/10/26 17:00:24 by dhamdiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	error(char *msg)
{
	ft_printf_fd(2, "\n\t%s%s%s\n\n", RED, msg, RESET);
	exit(1);
}

void	check_path(char const *path)
{
	int		fd;
	int		i;

	fd = open(path, O_RDONLY);
	if (fd <= 0)
	{
		close(fd);
		error("Error: the file doesn't exist or does not have the right rights.");
	}
	close(fd);
	i = ft_strlen(path);
	if (path[i - 4] != '.' || path[i - 3] != 'c'
		|| path[i - 2] != 'u' || path[i - 1] != 'b')
		error("Error: the file doesnt have the right format, it should end with '.cub'.");
}

char	**map_read(char *infile)
{
	int		line_number;
	int		fd;
	char	*tmp;
	char	*lines;

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
				error("Error: Map invalid! (empty line)\n");
			lines = ft_strjoin_free(lines, tmp);
		}
		line_number++;
	}
	close(fd);
	return (ft_split(lines, '\n'));
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
			if (line[0] && line [1] && ft_strncmp(line[0], "NO", 3)== 0 && !cub->north)
				cub->north = ft_strdup(line[1]);
			else if (line[0] && line [1] && ft_strncmp(line[0], "SO", 3) == 0 && !cub->south)
				cub->south = ft_strdup(line[1]);
			else if (line[0] && line [1] && ft_strncmp(line[0], "WE", 3) == 0 && !cub->west)
				cub->west = ft_strdup(line[1]);
			else if (line[0] && line [1] && ft_strncmp(line[0], "EA", 3) == 0 && !cub->east)
				cub->east = ft_strdup(line[1]);
			free(line);
		}
		i++;
	}
	printf("\n<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>\n\n");
	printf("NORTH: %s\t| SOUTH: %s\t| WEST: %s\t| EAST: %s\n", cub->north, cub->south, cub->west, cub->east);
	printf("\n<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>\n");
}

void	set_to_default(t_cub *cub)
{
	cub->input = NULL;
	cub->player = NULL;
	cub->north = NULL;
	cub->south = NULL;
	cub->west = NULL;
	cub->east = NULL;
	cub->floor.blue = 0;
	cub->floor.green = 0;
	cub->floor.red = 0;
	cub->ceiling.blue = 0;
	cub->ceiling.green = 0;
	cub->ceiling.red = 0;
}

int	parse(char *infile, t_cub *cub)
{
	set_to_default(cub);
	check_path(infile);
	cub->input = map_read(infile);
	get_textures(cub);
	return (0);
}


static void ft_hook(void* param)
{
	const mlx_t* mlx = param;

	printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
}

static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (argc != 2)
		error("Please execute with: './cub3d path/to/map/MAPNAME.cub'\n");
	parse(argv[1], &cub);
	ft_print2(cub.input);

	mlx_t* mlx = mlx_init(400, 500, "42Balls", true);

	mlx_image_t* img = mlx_new_image(mlx, 256, 256);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error();

	// Even after the image is being displayed, we can still modify the buffer.
	mlx_put_pixel(img, 0, 0, 0xFF0000FF);
	
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	
	return (0);
}
