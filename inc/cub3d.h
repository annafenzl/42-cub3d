/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 15:55:27 by afenzl            #+#    #+#             */
/*   Updated: 2022/11/02 16:49:07 by afenzl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define RESET "\033[0m"
# define MOVESPEED 0.06
# define ROTATION_SPEED 0.04
# define BPP 4
# define TEXTURE_SIZE 64

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>

# include "../libft/libs.h"
# include "MLX42/MLX42.h"

enum e_dir
{
	north,
	south,
	west,
	east,
};

typedef struct s_window
{	
	double		player_x;
	double		player_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;

	mlx_image_t	*window_img;

}				t_window;

typedef struct s_ray
{
	double	cam_x;
	double	wall_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;

	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side;
	int		draw_start;
	int		draw_end;
	int		line_height;

}		t_ray;

typedef struct s_cub
{
	mlx_t			*mlx;
	t_window		window;
	mlx_texture_t	*tex_dir[4];

	char			**input;

	char			**map;
	int				mp_height;
	int				mp_width;

	int				floor_color;
	int				ceiling_color;

}			t_cub;

// ************** parsing **************
void	print_error_msg(char *msg, t_cub *cub);
int		parse(char *infile, t_cub *cub);
void	free_info(t_cub *cub);

//check
void	check_path(char const *path);
void	check_walls(t_cub *cub, int y, int x);
void	check_map(t_cub *cub);
void	check_if_complete(t_cub *cub);
// get
char	*read_file(char *infile);
void	get_textures_and_color(t_cub *cub);
// set
void	set_to_default(t_cub *cub);
int		set_colores(char *rgb, t_cub *cub);
void	set_textures(t_cub *cub, char	*line, int direction);
void	set_directions(t_window *window,
			double dir_x, double dir_y, double plane);
// // raycaster
void	reg_keys(void *param);
void	draw_floor_and_ceiling(mlx_image_t *window, int ceiling_c, int floor_c);
void	apply_dda(t_ray *ray, t_cub *cub);
void	set_side_and_delta(t_ray *ray, double player_x, double player_y);
void	get_start_and_end(t_ray *ray,
			int screen_height, double player_x, double player_y);
void	draw(t_cub *cub, t_ray *ray, int x);

#endif //CUB3D