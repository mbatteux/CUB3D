/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_parser2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 04:10:06 by jolecomt          #+#    #+#             */
/*   Updated: 2024/03/09 23:35:21 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	get_size(char **cub, int len_tab[2])
{
	int	i;

	i = 0;
	len_tab[0] = ft_tablen(cub);
	len_tab[1] = 0;
	while (i < len_tab[0])
	{
		if (ft_strlen(cub[i]) > len_tab[1])
		{
			len_tab[1] = ft_strlen(cub[i]);
			i = 0;
		}
		else
			i++;
	}
}

// printf("[%c][%c][%c]\n[%c][0][%c]\n[%c][%c][%c]\n", cub[i - 1][j + 1]
// 	, cub[i - 1][j - 1], cub[i + 1][j - 1], cub[i + 1][j + 1], cub[i][j - 1]
// 	,cub[i][j + 1], cub[i + 1][j], cub[i - 1][j]);

static int	check_space(char **cub, int len_tab[2], int i, int j)
{
	if (i == 0 || i == (len_tab[0] - 1))
		return (1);
	if (cub[i - 1][j + 1] == ' ' \
		|| cub[i - 1][j - 1] == ' ' \
		|| cub[i + 1][j - 1] == ' ' \
		|| cub[i + 1][j + 1] == ' ' \
		|| cub[i][j - 1] == ' ' \
		|| cub[i][j + 1] == ' ' \
		|| cub[i + 1][j] == ' ' \
		|| cub[i - 1][j] == ' ' )
		return (1);
	return (0);
}

int	ft_tabprint(char **tab)
{
	int	i;
	int	len_tab;

	i = 0;
	len_tab = ft_tablen(tab);
	while (i < len_tab && tab[i] != NULL)
	{
		printf("[%s]\n", tab[i]);
		i++;
	}
	return (i);
}

void	update_cub(int len_tab[2], char **cub)
{
	int		i;
	char	*s;

	i = 0;
	while (i < len_tab[0])
	{
		if (ft_strlen(cub[i]) < len_tab[1] + 2)
		{
			s = cub[i];
			cub[i] = malloc((len_tab[1] + 3) * sizeof(char));
			cub[i] = ft_memset(cub[i], ' ', len_tab[1] + 2);
			cub[i][len_tab[1] + 2] = '\0';
			ft_strlcpy(cub[i] + 1, s, ft_strlen(s) + 1);
		}
		i++;
	}
}

int	check_cub_parser(t_dta *dta, char **cub)
{
	int	len_tab[2];
	int	i;
	int	j;

	i = 0;
	j = 1;
	get_size(dta->cub, len_tab);
	update_cub(len_tab, dta->cub);
	while (i < len_tab[0])
	{
		while (j <= len_tab[1] + 1)
		{
			if (((cub[i][j] == '0' || cub[i][j] == 'P'
				|| cub[i][j] == 'O') && check_space(cub, len_tab, i, j)))
				return (err("Error\nHole in the map or door lead to void\n"));
			j++;
		}
		i++;
		j = 1;
	}
	return (0);
}
