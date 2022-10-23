/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 15:55:27 by afenzl            #+#    #+#             */
/*   Updated: 2022/10/23 15:56:45 by afenzl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define RESET "\033[0m"

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>

# include "../libft/libs.h"
# include "../MLX/mlx.h"

typedef struct s_colour
{
	int	red;
	int	green;
	int	blue;

}			t_colour;

typedef struct s_cub
{
	char		*north;
	char		*south;
	char		*west;
	char		*east;

	t_colour	floor;
	t_colour	ceiling;

}			t_cub;

#endif //CUB3D