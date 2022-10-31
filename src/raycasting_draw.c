/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_draw.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhamdiev <dhamdiev@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:27:28 by dhamdiev          #+#    #+#             */
/*   Updated: 2022/10/31 17:14:09 by dhamdiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_floor_and_ceiling(mlx_image_t *window, int ceiling_c, int floor_c)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	while (i < window->width)
	{
		j = 0;
		while (j < window->height)
		{
			if (j < window->height / 2)
				mlx_put_pixel(window, i, j, ceiling_c);
			else
				mlx_put_pixel(window, i, j, floor_c);
			j++;
		}
		i++;
	}
}

int	get_texture_index(t_ray *ray)
{
	if (!ray->side && ray->ray_dir_x > 0)
	{
		return (north);
	}
	else if (!ray->side && ray->ray_dir_x < 0)
	{
		return (south);
	}
	if (ray->side && ray->ray_dir_y < 0)
	{
		return (west);
	}
	else if (ray->side && ray->ray_dir_y > 0)
	{
		return (east);
	}
	return (0);
}

void	draw(t_cub *cub, t_ray *ray, int x)
{
	int				y;
	int				tex_x;
	int				tex_y;
	double			tex_pos;
	double			step;

	tex_x = (int)(ray->wall_x * (double)(cub->tex_dir[0]->width));
	if (ray->side == 0 && ray->ray_dir_x > 0)
		tex_x = cub->tex_dir[0]->width - tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		tex_x = cub->tex_dir[0]->width - tex_x - 1;
	step = 1.0 * cub->tex_dir[0]->height / ray->line_height;
	tex_pos = (ray->draw_start - cub->mlx->height / 2
			+ ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		tex_y = (int)tex_pos & (TEXTURE_SIZE - 1);
		tex_pos += step;
		ft_memcpy(&cub->window.window_img->pixels
		[(y * (int)cub->mlx->width + x) * BPP],
			&cub->tex_dir[get_texture_index(ray)]->pixels
		[(tex_y * cub->tex_dir[0]->width + tex_x) * BPP], BPP);
		y++;
	}
}
