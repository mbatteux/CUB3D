/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:23:43 by mbatteux          #+#    #+#             */
/*   Updated: 2024/03/09 23:34:14 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	err(char *str)
{
	if (str == NULL)
		return (-1);
	write(2, str, ft_strlen(str));
	return (-1);
}

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (-1);
	while (i < n && s1[i])
	{
		if (s1[i] == s2[i])
			i++;
		else
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	if (s2[i] && i < n)
		return (-1);
	return (0);
}

int	ft_isdigit(char c)
{
	if (c > 47 && c < 58)
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int	res;
	int	o;

	res = 0;
	o = 0;
	if (ft_strlen(str) > 3)
		return (-1);
	while (str[o] == '0')
		o++;
	while (str[o])
	{
		if (ft_isdigit(str[o]) == 0)
			return (-1);
		res = res * 10 + str[o++] - '0';
	}
	return (res);
}
