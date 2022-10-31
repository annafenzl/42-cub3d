/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 14:46:10 by afenzl            #+#    #+#             */
/*   Updated: 2022/10/31 14:43:15 by afenzl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	DEBUG(t_cub *cub)
{
	printf("<<<<<<<<<<<<<<>>>>>>>>>>>>>>>\n");
	ft_print2(cub->input);
	printf("----------------------------\n");
	printf("NORTH:	%p\n", cub->tex_dir[north]);
	printf("SOUTH:	%p\n", cub->tex_dir[south]);
	printf("WEST:	%p\n", cub->tex_dir[west]);
	printf("EAST:	%p\n", cub->tex_dir[east]);
	printf("\n");
	printf("FLOOR:		%i\n", cub->floor_color);
	printf("CEILING:	%i\n", cub->ceiling_color);
	printf("\n");
	printf("MAP HEIGHT:	%i	|| MAP WIDTH	%i\n", cub->mp_height, cub->mp_width);
	printf("PLAYER_X:	%i	|| PLAYER_Y	%i\n\n", (int)cub->window.player_x, (int)cub->window.player_y);
	printf("MAP:\n");
	ft_print2(cub->map);
	printf("\n");
	printf("<<<<<<<<<<<<<<>>>>>>>>>>>>>>>\n");
}

void	free_info(t_cub *cub)
{
	if (cub && cub->input)
		free(cub->input);
	if (cub && cub->map)
		free(cub->map);
}

void game_loop(void *param)
{
	t_cub		*cub;
	t_window	*window;
	int			x;
	t_ray		ray;

	cub = (t_cub *) param;
	window = &cub->window;
	x = 0;
	draw_floor_and_ceiling(window->window_img, cub->ceiling_color, cub->floor_color);
	while (x < cub->mlx->width)
	{
		ray.cam_x = 2 * x / (double)cub->mlx->width - 1;
		ray.ray_dir_x = window->dir_x + window->plane_x * ray.cam_x;
		ray.ray_dir_y = window->dir_y + window->plane_y * ray.cam_x;
		ray.map_x = (int) window->player_x;
		ray.map_y = (int) window->player_y;
		set_side_and_delta(&ray, window->player_x, window->player_y);
		apply_dda(&ray, cub->map);
		get_start_and_end(&ray, cub->mlx->height, window->player_x, window->player_y);
		draw(cub, &ray, x);
		x++;
	}
}

int	main(int argc, char **argv)
{
	t_cub		cub;
	mlx_image_t	*img;

	if (argc != 2)
		print_error_msg("Please execute with: './cub3d path/to/map/MAPNAME.cub'", NULL);
	parse(argv[1], &cub);
	DEBUG(&cub);
	cub.mlx = mlx_init(1920, 1080, "Cub3D", true);
	img = mlx_new_image(cub.mlx, cub.mlx->width, cub.mlx->height);
	cub.window.window_img = img;
	mlx_image_to_window(cub.mlx, img, 0, 0);
	mlx_loop_hook(cub.mlx, &game_loop, &cub);
	mlx_key_hook(cub.mlx, &reg_keys, &cub);
	mlx_loop(cub.mlx);
	mlx_terminate(cub.mlx);
	free_info(&cub);
	return (0);
}
