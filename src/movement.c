#include "../inc/cub3d.h"

void reg_keys(mlx_key_data_t keydata, void *param)
{
	t_cub *cub = (t_cub *)param;
	t_window *window = &cub->window;
	if (cub->mlx != NULL) 
	{
		if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		{
			if(cub->map[(int)(window->player_x + window->dir_x * MOVESPEED)][(int)(window->player_y)] != '1') window->player_x += window->dir_x * MOVESPEED;
     		if(cub->map[(int)(window->player_x)][(int)(window->player_y + window->dir_y * MOVESPEED)] != '1') window->player_y += window->dir_y * MOVESPEED;
		}
		if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		{
			if(cub->map[(int)(window->player_x - window->dir_x * MOVESPEED)][(int)(window->player_y)] != '1') window->player_x -= window->dir_x * MOVESPEED;
     		if(cub->map[(int)(window->player_x)][(int)(window->player_y + window->dir_y * MOVESPEED)] != '1') window->player_y -= window->dir_y * MOVESPEED;
		}
		if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		{
			double oldDirX = window->dir_x;
      		window->dir_x = window->dir_x * cos(-ROTATION_SPEED) - window->dir_y * sin(-ROTATION_SPEED);
      		window->dir_y = oldDirX * sin(-ROTATION_SPEED) + window->dir_y * cos(-ROTATION_SPEED);
      		double oldPlaneX = window->plane_x;
     		window->plane_x = window->plane_x * cos(-ROTATION_SPEED) - window->plane_y * sin(-ROTATION_SPEED);
      		window->plane_y = oldPlaneX * sin(-ROTATION_SPEED) + window->plane_y * cos(-ROTATION_SPEED);
		}
		if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		{
			//both camera direction and camera plane must be rotated
      		double oldDirX = window->dir_x;
     		 window->dir_x = window->dir_x * cos(ROTATION_SPEED) - window->dir_y * sin(ROTATION_SPEED);
      		window->dir_y = oldDirX * sin(ROTATION_SPEED) + window->dir_y * cos(ROTATION_SPEED);
      		double oldPlaneX = window->plane_x;
      		window->plane_x = window->plane_x * cos(ROTATION_SPEED) - window->plane_y * sin(ROTATION_SPEED);
			window->plane_y = oldPlaneX * sin(ROTATION_SPEED) + window->plane_y * cos(ROTATION_SPEED);
		}
	}	
}