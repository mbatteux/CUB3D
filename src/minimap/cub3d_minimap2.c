/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_minimap2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:14:26 by mbatteux          #+#    #+#             */
/*   Updated: 2024/03/10 00:16:22 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	calcul_minimap(t_dta *dta)
{
	int	x;
	int	y;
	int	xlen;
	int	ylen;

	x = X / 4;
	y = Y / 4;
	if (dta->cub != NULL)
		xlen = find_max_len_x(dta->cub);
	else
		xlen = 0;
	ylen = ft_tablen(dta->cub);
	if (x / xlen < y / ylen)
		return (x / xlen);
	else
		return (y / ylen);
}

int	find_max_len_x(char **cub)
{
	int	j;
	int	len;

	j = 0;
	len = 0;
	while (j < ft_tablen(cub) && cub[j])
	{
		if (ft_strlen(cub[j]) > len)
			len = ft_strlen(cub[j]);
		j++;
	}
	return (len);
}
