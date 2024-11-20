/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_raycaster2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:20:16 by mbatteux          #+#    #+#             */
/*   Updated: 2024/03/09 23:35:29 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

//calcul la taille de adj et de opp qui 
//sont essentiel aux calculs des cosinus
void	get_adj_and_opp(t_p *p, float ran)
{
	p->adj = 0;
	p->opp = 0;
	p->hx = 0;
	p->hy = 0;
	if (sinf(ran) > 0)
		p->opp = ((int)p->n_py) - p->n_py + 1;
	else if (sinf(ran) < 0)
	{
		p->opp = -1;
		if ((int)p->n_py - p->n_py != 0)
			p->opp = ((int)p->n_py) - p->n_py;
	}
	if (cosf(ran) > 0)
		p->adj = ((int)p->n_px) + 1 - p->n_px;
	else if (cosf(ran) < 0)
	{
		p->adj = -1;
		if (((int)p->n_px) - p->n_px != 0)
			p->adj = ((int)p->n_px) - p->n_px;
	}
}

//calcul la taille du rayon souhaiter grace a son pan 
//et renvoie 1 si le ray touche un x et 0 si y
float	find_len_ray(t_dta *dta, t_p *p, float ran)
{
	get_adj_and_opp(p, ran);
	p->hy = p->opp / sinf(ran);
	p->hx = p->adj / cosf(ran);
	if (p->hy < p->hx)
	{
		p->n_py += p->opp;
		p->n_px += cosf(ran) * p->hy;
		dta->len += fabsf(p->hy);
		dta->wy = 1;
		dta->wx = 0;
	}
	else
	{
		p->n_px += p->adj;
		p->n_py += sinf(ran) * p->hx;
		dta->len += fabsf(p->hx);
		dta->wy = 0;
		dta->wx = 1;
	}
	return (dta->len);
}

//renvoie 1 si un mur x est toucher en fonction de l'angle du rayon
int	touchwallx(t_dta *dta, t_p *p)
{
	if (cosf(dta->ran) > 0)
	{
		if (dta->cub[(int)p->n_py][(int)p->n_px] == '1')
			return (1);
		else if (dta->cub[(int)p->n_py][(int)p->n_px] == 'P')
			return (2);
	}
	else if (cosf(dta->ran) < 0)
	{
		if (dta->cub[(int)p->n_py][(int)p->n_px - 1] == '1')
			return (1);
		else if (dta->cub[(int)p->n_py][(int)p->n_px - 1] == 'P')
			return (2);
	}
	return (0);
}

//renvoie 1 si un mur y est toucher en fonction de l'angle du rayon
int	touchwally(t_dta *dta, t_p *p)
{
	if (sinf(dta->ran) > 0)
	{
		if (dta->cub[(int)p->n_py][(int)p->n_px] == '1')
			return (1);
		else if (dta->cub[(int)p->n_py][(int)p->n_px] == 'P')
			return (2);
	}
	else if (sinf(dta->ran) < 0)
	{
		if (dta->cub[(int)p->n_py - 1][(int)p->n_px] == '1')
			return (1);
		else if (dta->cub[(int)p->n_py - 1][(int)p->n_px] == 'P')
			return (2);
	}
	return (0);
}

//permet de savoir si le rayon lancer a toucher un mur
int	iftouch_wall(t_dta *dta, t_p *p, int i)
{
	if (dta->len > 0 && dta->wx == 1 && dta->wy == 0)
	{
		if (touchwallx(dta, p) == 1)
			if (!displaywall(dta, i, 0))
				return (1);
		if (touchwallx(dta, p) == 2)
			if (!displaydoor(dta, i, 0))
				return (2);
	}
	else if (dta->len > 0 && dta->wy == 1 && dta->wx == 0)
	{
		if (touchwally(dta, p) == 1)
			if (!displaywall(dta, i, 0))
				return (1);
		if (touchwally(dta, p) == 2)
			if (!displaydoor(dta, i, 0))
				return (2);
	}
	return (0);
}
