/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:22:15 by mbatteux          #+#    #+#             */
/*   Updated: 2024/03/10 00:47:25 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	check_png(t_dta *dta, t_png **png)
{
	if (create_tab_hexa(png[0], dta->clr->no) == -1)
		return (-1);
	if (create_tab_hexa(png[1], dta->clr->so) == -1)
		return (-1);
	if (create_tab_hexa(png[2], dta->clr->ea) == -1)
		return (-1);
	if (create_tab_hexa(png[3], dta->clr->we) == -1)
		return (-1);
	if (create_tab_hexa(png[4], "./assets/door.png") == -1)
		return (-1);
	return (0);
}

int	dta_init(t_dta *dta, char *argv)
{
	int	i;

	i = 0;
	dta->map = ft_get_map(argv);
	dta->clr = ft_calloc(1, sizeof(t_color));
	dta->png = ft_calloc(5, sizeof(t_png *));
	while (i < 5)
		dta->png[i++] = ft_calloc(1, sizeof(t_png));
	dta->clr->no = NULL;
	dta->clr->so = NULL;
	dta->clr->we = NULL;
	dta->clr->ea = NULL;
	dta->clr->floor = -1;
	dta->clr->ceiling = -1;
	dta->mousex = X / 2;
	dta->mousey = Y / 2;
	dta->p = ft_calloc(1, sizeof(t_p));
	if (parser(dta))
		return (-1);
	if (dta != NULL && dta->cub != NULL)
		dta->maplen = calcul_minimap(dta);
	return (0);
}

int	check_player(t_dta *dta)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < ft_tablen(dta->cub))
	{
		while (j < ft_strlen(dta->cub[i]))
		{
			if (dta->cub[i][j] == 'N' || dta->cub[i][j] == 'W' \
				|| dta->cub[i][j] == 'E' || dta->cub[i][j] == 'S')
			{
				dta->p->pan = 1;
				return (0);
			}
			j++;
		}
		i++;
		j = 0;
	}
	return (err("Error\nNo player found\n"));
}

int	parser(t_dta *dta)
{
	if (dta->map == NULL)
		return (free_1(dta), 1);
	else if (stock_texture(dta, dta->clr, dta->map))
		return (free_2(dta), 1);
	else if (stock_color(dta->clr, dta->map))
		return (free_2(dta), 1);
	else if (stock_cub(dta, dta->map))
		return (free_2(dta), 1);
	else if (check_player(dta))
		return (free_3(dta), 1);
	else if (check_cub(dta, dta->cub))
		return (free_3(dta), 1);
	else if (check_cub_parser(dta, dta->cub))
		return (free_4(dta), 1);
	else if (check_png(dta, dta->png))
		return (free_4(dta), 1);
	return (0);
}
