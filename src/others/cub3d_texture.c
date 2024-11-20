/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 13:06:47 by mbatteux          #+#    #+#             */
/*   Updated: 2024/03/09 23:35:05 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

//permet de savoir quel mur oin touche pour afficher la texture correspondante
int	which_texture(t_dta *dta)
{
	if (dta->wy && sinf(dta->ran) < 0)
		return (0);
	else if (dta->wy && sinf(dta->ran) > 0)
		return (1);
	else if (dta->wx && cosf(dta->ran) > 0)
		return (2);
	else if (dta->wx && cosf(dta->ran) < 0)
		return (3);
	return (-1);
}

//cherche dans le png de la texure quel x et y 
//on doit afficher sur le mur et renvoie la couleur de ce pixel
unsigned long	ft_texture(t_dta *dta, int wall_height, int j, t_png *png)
{
	uint32_t		y;
	uint32_t		x;
	unsigned long	res;

	y = ((float)png->text->height / (Y / dta->len))
		* ((float)j + ((Y / dta->len) - (float)wall_height) / 2.0);
	x = dta->f * (float)png->text->width;
	if (y >= png->text->height)
		y = png->text->height - 1;
	if (x >= png->text->width)
		x = png->text->width - 1;
	res = png->tabh[y][x];
	return (res);
}
