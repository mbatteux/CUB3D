/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_raycaster.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:46:51 by mbatteux          #+#    #+#             */
/*   Updated: 2024/03/09 23:35:25 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

//calcule la distance de chaque raryon 
//et affiche la colonne de pixel correspondante
void	traceray(t_dta *dta, t_p *p)
{
	int	i;

	i = 0;
	dta->ran = p->pan - (33 * RA);
	while (i < X)
	{
		p->n_px = p->px;
		p->n_py = p->py;
		dta->len = 0;
		while (1)
		{
			dta->len = find_len_ray(dta, p, dta->ran);
			if (iftouch_wall(dta, dta->p, i) > 0)
				break ;
		}
		dta->ran += FOV / X;
		i++;
	}
}

//permet d'afficher le sol et le plafond en fonction des couleurs donnes
int	display_ceilling_floor(t_dta *dta, t_color *clr)
{
	int	i;
	int	j;

	i = 0;
	while (i < Y / 2)
	{
		j = 0;
		while (j < X)
			mlx_put_pixel(dta->img, j++, i, clr->ceiling);
		i++;
	}
	while (i < Y)
	{
		j = 0;
		while (j < X)
			mlx_put_pixel(dta->img, j++, i, clr->floor);
		i++;
	}
	return (0);
}

//fisheye 118
//permet d'afficher le mur en fonction de ou le rayon a taper
int	displaywall(t_dta *dta, int i, unsigned long clr)
{
	int	wall_height;
	int	start;
	int	j;
	int	c;

	if (dta->wx == 1)
		dta->f = dta->p->n_py - (int)dta->p->n_py;
	else if (dta->wy == 1)
		dta->f = dta->p->n_px - (int)dta->p->n_px;
	dta->len = cos(dta->p->pan - dta->ran) * dta->len;
	wall_height = Y / dta->len;
	if (wall_height > Y)
		wall_height = Y;
	start = (Y - wall_height) / 2;
	j = start;
	while (j < wall_height + start)
	{
		c = which_texture(dta);
		clr = ft_texture(dta, wall_height, j - start, dta->png[c]);
		mlx_put_pixel(dta->img, i, j++, clr);
	}
	return (0);
}

//la meme mais version porte
int	displaydoor(t_dta *dta, int i, unsigned long clr)
{
	int	wall_height;
	int	start;
	int	j;
	int	c;

	if (dta->wx == 1)
		dta->f = dta->p->n_py - (int)dta->p->n_py;
	else if (dta->wy == 1)
		dta->f = dta->p->n_px - (int)dta->p->n_px;
	dta->len = cos(dta->p->pan - dta->ran) * dta->len;
	wall_height = Y / dta->len;
	if (wall_height > Y)
		wall_height = Y;
	start = (Y - wall_height) / 2;
	j = start;
	while (j < wall_height + start)
	{
		c = which_texture(dta);
		clr = ft_texture(dta, wall_height, j - start, dta->png[4]);
		mlx_put_pixel(dta->img, i, j++, clr);
	}
	return (0);
}
