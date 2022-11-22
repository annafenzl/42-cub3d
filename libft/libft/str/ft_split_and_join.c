/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_and_join.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 16:56:48 by afenzl            #+#    #+#             */
/*   Updated: 2022/11/22 15:18:12 by afenzl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_split_and_join(char	*str, char c)
{
	int		i;
	char	**split;
	char	*tmp;

	i = 0;
	tmp = ft_strdup("");
	split = ft_split(str, c);
	while (split && split[i])
	{
		tmp = ft_strjoin_free(tmp, split[i]);
		i++;
	}
	ft_free2(split);
	return (tmp);
}
