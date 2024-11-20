/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:37:23 by mbatteux          #+#    #+#             */
/*   Updated: 2024/03/09 23:35:56 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

//supprime l'ancienne image et cree en une nouvelle avec les changements
void	ft_reload(t_dta *dta, t_p *p)
{
	int	d;

	d = (int)((double)1 / dta->mlx->delta_time);
	if (d > 60)
		printf("FPS = 60\n");
	else
		printf("FPS = %d\n", d);
	display_ceilling_floor(dta, dta->clr);
	traceray(dta, p);
	ft_minimap(dta, dta->cub, 0, 0);
}

//check si les nombres des couleurs sont bien separe par des ,
int	check_charset(char *map, char set)
{
	int	i;

	i = 0;
	while (i < ft_strlen(map) && map[i])
	{
		if (ft_isdigit(map[i]) == 1)
			i++;
		else if (map[i] != set)
			return (-1);
		i++;
	}
	return (0);
}

// transforme les int en "hexa" pour les couleurs
int	hexa_color(char *map)
{
	int				res[3];
	int				i;
	char			**clr;

	i = 0;
	if (check_charset(map, ',') == -1)
		return (-1);
	clr = ft_split(map, ',');
	while (i < ft_tablen(clr))
	{
		if (ft_tablen(clr) != 3)
		{
			ft_freetab(clr);
			return (-1);
		}
		res[i] = ft_atoi(clr[i]);
		if (res[i] == -1 || res[i++] > 255)
		{
			ft_freetab(clr);
			return (-1);
		}
	}
	ft_freetab(clr);
	res[0] = creatergba(res[0], res[1], res[2], 255);
	return (res[0]);
}

//verifie et stock la couleur du sol et du plafond
int	stock_color(t_color *clr, char **map)
{
	int	i ;

	i = 0;
	while (i < ft_tablen(map))
	{
		map[i] = ft_suppr_space(map[i]);
		if (ft_strnstr(map[i], "F ", ft_strlen(map[i])))
			clr->floor = hexa_color(map[i] + (ft_space(map[i]) + 1));
		if (ft_strnstr(map[i], "C ", ft_strlen(map[i])))
			clr->ceiling = hexa_color(map[i] + (ft_space(map[i]) + 1));
		i++;
	}
	if (clr->floor != -1 && clr->ceiling != -1)
		return (0);
	return (err("Error:\nMap invalide color\n"));
}

//recupere la map a l'aide de get_next_line
// et la stock dans dta->map grace au return
char	**ft_get_map(char *argv)
{
	int		i;
	int		fd;
	char	**tab;

	i = 0;
	tab = ft_calloc(80, sizeof (char *));
	fd = open(argv, O_RDONLY);
	if (fd == -1)
	{
		free(tab);
		return (err("Error:\nmap inconnue\n"), NULL);
	}
	while (1)
	{
		tab[i] = get_next_line(fd);
		if (tab[i] == NULL)
			break ;
		if (tab[i][ft_strlen(tab[i]) - 1] == '\n')
			tab[i][ft_strlen(tab[i]) - 1] = '\0';
		i++;
	}
	close(fd);
	return (tab);
}
// if (tab[i] != NULL)
// 	printf("%s\n", tab[i]);
