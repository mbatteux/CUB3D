/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 11:01:54 by jolecomt          #+#    #+#             */
/*   Updated: 2024/03/09 23:34:05 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	free_png(t_dta *dta)
{
	int	i;

	i = 4;
	while (i >= 0)
	{
		if (dta->png[i]->tabh)
			ft_free_tabh(dta->png[i]->tabh);
		if (dta->png[i]->text)
			mlx_delete_texture(dta->png[i]->text);
		if (dta->png[i])
			free(dta->png[i]);
		i--;
	}
	if (dta->png)
		free(dta->png);
}

int	ft_strlcpy(char *dst, const char *src, int size)
{
	int	i;

	i = 0;
	if (size)
	{
		while (i < size - 1 && src[i])
		{
			dst[i] = src[i];
			i++;
		}
	}
	return (ft_strlen(src));
}

//supprime les espaces a la fin d'une line
char	*ft_suppr_space(char *line)
{
	int	i;

	i = ft_strlen(line);
	if (i == 0)
		return (line);
	while (i != 0 && line[i - 1] == ' ')
		i--;
	line[i] = '\0';
	return (line);
}
