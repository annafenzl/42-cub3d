/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhamdiev <dhamdiev@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:27:08 by dhamdiev          #+#    #+#             */
/*   Updated: 2022/10/31 17:10:26 by dhamdiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	move_up_down(t_window *window, t_cub *cub)
{
	if (mlx_is_key_down(cub->mlx, MLX_KEY_W))
	{
		if (cub->map[(int)(window->player_y)]
			[(int)(window->player_x + window->dir_x * MOVESPEED * 5)] != '1')
			window->player_x += window->dir_x * MOVESPEED;
		if (cub->map[(int)(window->player_y + window->dir_y * MOVESPEED * 5)]
			[(int)(window->player_x)] != '1')
			window->player_y += window->dir_y * MOVESPEED;
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_S))
	{
		if (cub->map[(int)(window->player_y)]
			[(int)(window->player_x - window->dir_x * MOVESPEED * 5)] != '1')
			window->player_x -= window->dir_x * MOVESPEED;
		if (cub->map[(int)(window->player_y - window->dir_y * MOVESPEED * 5)]
			[(int)(window->player_x)] != '1')
			window->player_y -= window->dir_y * MOVESPEED;
	}
}

void	move_right_left(t_window *window, t_cub *cub)
{
	if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
	{
		if (cub->map[(int)(window->player_y)]
		[(int)(window->player_x + -window->dir_y * MOVESPEED * 5)] != '1')
			window->player_x += -window->dir_y * MOVESPEED;
		if (cub->map[(int)(window->player_y + window->dir_x * MOVESPEED * 5)]
			[(int)(window->player_x)] != '1')
			window->player_y += window->dir_x * MOVESPEED;
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_D))
	{
		if (cub->map[(int)(window->player_y)]
		[(int)(window->player_x - -window->dir_y * MOVESPEED * 5)] != '1')
			window->player_x -= -window->dir_y * MOVESPEED;
		if (cub->map[(int)(window->player_y - window->dir_x * MOVESPEED * 5)]
			[(int)(window->player_x)] != '1')
			window->player_y -= window->dir_x * MOVESPEED;
	}
}

void	rotate_right(t_window *window, t_cub *cub)
{
	double	old_dir_x;
	double	old_plane_x;

	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
	{
		old_dir_x = window->dir_x;
		window->dir_x = window->dir_x * cos(-ROTATION_SPEED)
			- window->dir_y * sin(-ROTATION_SPEED);
		window->dir_y = old_dir_x * sin(-ROTATION_SPEED)
			+ window->dir_y * cos(-ROTATION_SPEED);
		old_plane_x = window->plane_x;
		window->plane_x = window->plane_x * cos(-ROTATION_SPEED)
			- window->plane_y * sin(-ROTATION_SPEED);
		window->plane_y = old_plane_x * sin(-ROTATION_SPEED)
			+ window->plane_y * cos(-ROTATION_SPEED);
	}
}

void	rotate_left(t_window *window, t_cub *cub)
{
	double	old_dir_x;
	double	old_plane_x;

	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
	{
		old_dir_x = window->dir_x;
		window->dir_x = window->dir_x * cos(ROTATION_SPEED)
			- window->dir_y * sin(ROTATION_SPEED);
		window->dir_y = old_dir_x * sin (ROTATION_SPEED)
			+ window->dir_y * cos(ROTATION_SPEED);
		old_plane_x = window->plane_x;
		window->plane_x = window->plane_x * cos(ROTATION_SPEED)
			- window->plane_y * sin(ROTATION_SPEED);
		window->plane_y = old_plane_x * sin(ROTATION_SPEED)
			+ window->plane_y * cos(ROTATION_SPEED);
	}
}

void	reg_keys(void *param)
{
	t_cub		*cub;
	t_window	*window;

	cub = (t_cub *)param;
	window = &cub->window;
	if (cub->mlx != NULL)
	{
		move_up_down(window, cub);
		move_right_left(window, cub);
		rotate_right(window, cub);
		rotate_left(window, cub);
		if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
		{
			mlx_terminate(cub->mlx);
			mlx_close_window(cub->mlx);
			exit(0);
		}
	}
}
