/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 09:59:22 by mbatteux          #+#    #+#             */
/*   Updated: 2024/03/10 00:13:29 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

//affiche le joueur sur la minimap
int	ft_player(t_dta *dta, float x, float y, int clr)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < 2)
	{
		while (i < 2)
			mlx_put_pixel(dta->img, (x * dta->maplen)
				+ i++, (y * dta->maplen) + j, clr);
		i = 0;
		j++;
	}
	return (0);
}

//affiche la minimap
int	ft_minimap(t_dta *dta, char **cub, float x, float y)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < ft_tablen(cub) && cub[i])
	{
		while (++j < ft_strlen(cub[i]) && cub[i][j])
		{
			if (cub[i][j] == '0')
				ft_floor(dta, x, y);
			else if (cub[i][j] == '1')
				ft_wall(dta, x, y, BLC);
			else if (cub[i][j] == 'P')
				ft_wall(dta, x, y, GRN);
			else if (cub[i][j] == 'O')
				ft_wall(dta, x, y, GRS);
			ft_player(dta, dta->p->px, dta->p->py, RG);
			x += dta->maplen;
		}
		x = 0;
		j = -1;
		y += dta->maplen;
	}
	return (0);
}

// affiche les murs de la minimap
int	ft_wall(t_dta *dta, float x, float y, int c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < dta->maplen)
	{
		while (i < dta->maplen)
			mlx_put_pixel(dta->img, x + i++, y + j, c);
		i = 0;
		j++;
	}
	return (0);
}

// affiche le sol de la minimap
int	ft_floor(t_dta *dta, float x, float y)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	ft_wall(dta, x, y, 0);
	while (i < dta->maplen)
		mlx_put_pixel(dta->img, x + i++, y, GRS);
	while (j < dta->maplen)
		mlx_put_pixel(dta->img, x + i, y + j++, GRS);
	while (i != 0)
		mlx_put_pixel(dta->img, x + i--, y + j, GRS);
	while (j != 0)
		mlx_put_pixel(dta->img, x + i, y + j--, GRS);
	return (0);
}
