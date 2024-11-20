/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_map3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:02:50 by mbatteux          #+#    #+#             */
/*   Updated: 2024/03/10 00:34:06 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

//recupere la position du joueur et la stock
int	pos_player(t_dta *dta, t_p *p, int i, int j)
{
	if (p->pan == 1)
	{
		if (dta->cub[i][j] == 'N')
			p->pan = N;
		else if (dta->cub[i][j] == 'S')
			p->pan = S;
		else if (dta->cub[i][j] == 'W')
			p->pan = W;
		else if (dta->cub[i][j] == 'E')
			p->pan = E;
		p->px = j + 1.5;
		p->py = i + 0.5;
		dta->cub[i][j] = '0';
	}
	else
		return (err("Error:\nToo many player or no player\n"));
	return (0);
}

int	skip_space_err(char *s, int *j)
{
	while (s[(*j)] == ' ' || s[(*j)] == '\t')
	{
		if (s[(*j)] == '\t')
			return (1);
		(*j)++;
	}
	return (0);
}

//check si le cub est conforme
int	check_cub(t_dta *dta, char **cub)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < ft_tablen(cub) && cub[i])
	{
		if (skip_space_err(cub[i], &j))
			return (err("Error\nTab in map file not supported !\n"));
		while (cub[i][j] != '\0')
		{
			if (check_cub3(dta, cub, &i, &j) == -1)
				return (-1);
			j++;
		}
		j = 0;
		i++;
	}
	if (check_cub2(cub) == -1)
		return (-1);
	return (0);
}

//deuxieme checker de cub
int	check_cub2(char **cub)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cub[i][j] != '\0')
		if (cub[i][j++] == '0')
			return (err("Error:\nHole in the map\n"));
	i = ft_tablen(cub) - 1;
	j = 0;
	while (cub[i][j] != '\0')
		if (cub[i][j++] == '0')
			return (err("Error:\nHole in the map\n"));
	return (0);
}

//troisieme checker de cub
int	check_cub3(t_dta *dta, char **cub, int *i, int *j)
{
	if (cub[(*i)][(*j)] == 'N' || cub[(*i)][(*j)] == 'E'
		|| cub[(*i)][(*j)] == 'W' || cub[(*i)][(*j)] == 'S')
	{
		if (pos_player(dta, dta->p, *i, *j) == -1)
			return (-1);
	}
	else if (cub[(*i)][(*j)] != '1' && cub[(*i)][(*j)] != '0')
	{
		if (cub[(*i)][(*j)] == ' ' && cub[(*i)][(*j) - 1] == '1'
			&& cub[(*i)][(*j) + 1] == '1')
		{
			(*j)++;
			return (1);
		}
		if (cub[(*i)][(*j)] == 'P')
		{
			(*j)++;
			return (1);
		}
		return (err("Error:\nHole in the map or carac invalid\n"));
	}
	return (0);
}
