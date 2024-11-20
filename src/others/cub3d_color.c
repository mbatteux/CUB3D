/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:39:43 by mbatteux          #+#    #+#             */
/*   Updated: 2024/03/09 23:34:54 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

unsigned long	creatergba(int r, int g, int b, int a)
{
	return (((r & 0xff) << 24) + ((g & 0xff) << 16)
		+ ((b & 0xff) << 8) + (a & 0xff));
}

unsigned long	**alloc_tabh(t_png *png)
{
	uint32_t		y;
	unsigned long	**tab;

	y = 0;
	tab = ft_calloc(png->text->height + 1, sizeof(unsigned long *));
	if (!tab)
		return (NULL);
	while (y < png->text->height)
	{
		tab[y] = ft_calloc(png->text->width, sizeof(unsigned long));
		if (!tab[y])
			return (NULL);
		y++;
	}
	return (tab);
}

static int	png_setter(t_png *png, char *path)
{
	png->text = mlx_load_png(path);
	if (png->text == NULL)
	{
		free(png->text);
		return (-1);
	}
	if (png->tabh == NULL)
		png->tabh = alloc_tabh(png);
	return (0);
}

int	create_tab_hexa(t_png *png, char *path)
{
	uint32_t	x;
	uint32_t	y;
	int			n;

	x = 0;
	y = 0;
	n = 0;
	if (png_setter(png, path))
		return (-1);
	while (y < png->text->height)
	{
		while (x < png->text->width)
		{
			png->tabh[y][x] = creatergba((int)png->text->pixels[n],
					(int)png->text->pixels[n + 1],
					(int)png->text->pixels[n + 2],
					(int)png->text->pixels[n + 3]);
			n += 4;
			x++;
		}
		x = 0;
		y++;
	}
	return (0);
}
