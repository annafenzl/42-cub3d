/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 14:46:10 by afenzl            #+#    #+#             */
/*   Updated: 2022/10/23 15:54:21 by afenzl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	error(char *msg)
{
	ft_printf_fd(2, "\n\t%s%s%s\n", RED, msg, RESET);
	exit(1);
}

int	parse(char *path, t_cub cub)
{
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	(void) argv;
	if (argc != 2)
		error("Please execute with: './cub3d path/to/map/MAPNAME.cub'\n");
	// parse(argv[1], &cub);
	return (0);
}
