/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:33:30 by mbatteux          #+#    #+#             */
/*   Updated: 2024/03/09 23:35:56 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

//stock la map dans dta->cub
int	stock_cub(t_dta *dta, char **map)
{
	int	j;

	j = ft_tablen(map) - 1;
	dta->cub = ft_calloc(ft_tablen(map), sizeof(char *));
	while (j > 0)
	{
		if (ft_strncmp(map[j], "\0", 1) == 0)
			break ;
		j--;
	}
	while (j < ft_tablen(map) && map[j])
		dta->cub[ft_tablen(dta->cub)] = map[j++];
	if (ft_strncmp(map[j - 1], "1", 1))
	{
		free(dta->cub);
		return (err("Error:\nMap not a the end\n"));
	}
	return (0);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	i = 0;
	if (little[i] == '\0')
		return ((char *)big);
	while (big[i] && i < len)
	{
		if (ft_strncmp(little, big + i, ft_strlen(little)) == 0
			&& i + ft_strlen(little) <= len)
			return ((char *)big + i);
		i++;
	}
	return (0);
}

// check si les textures sont conformes
int	check_texture(t_dta *dta, char *path, char *line, char *coor)
{
	if (ft_strnstr(line, coor, ft_strlen(line)))
	{
		if (path != NULL)
		{
			dta->err = -1;
			return (-1);
		}
	}
	else if (!ft_strnstr(line, coor, ft_strlen(line)))
		return (1);
	return (0);
}

int	ft_space(char *line)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (i < ft_strlen(line))
	{
		if (line[i] == ' ')
			res++;
		i++;
	}
	return (res);
}

//verifie et stock le path des textures dans des char *
int	stock_texture(t_dta *dta, t_color *clr, char **map)
{
	int	i;

	i = 0;
	while (i < ft_tablen(map))
	{
		map[i] = ft_suppr_space(map[i]);
		if (!check_texture(dta, clr->no, map[i], NO))
			clr->no = map[i] + ft_space(map[i]) + 2;
		else if (!check_texture(dta, clr->so, map[i], SO))
			clr->so = map[i] + ft_space(map[i]) + 2;
		else if (!check_texture(dta, clr->we, map[i], WE))
			clr->we = map[i] + ft_space(map[i]) + 2;
		else if (!check_texture(dta, clr->ea, map[i], EA))
			clr->ea = map[i] + ft_space(map[i]) + 2;
		else if (dta->err == -1)
			return (err("Error:\nDuplicate texture detected\n"));
		i++;
	}
	if (clr->no != NULL && clr->so != NULL
		&& clr->we != NULL && clr->ea != NULL)
		return (0);
	return (err("Error:\nMap invalide texture path\n"));
}
