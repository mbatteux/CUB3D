/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:18:04 by mbatteux          #+#    #+#             */
/*   Updated: 2024/03/09 23:33:58 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = c;
		i++;
	}
	return (s);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_memset((unsigned char *)ptr, 0, nmemb * size);
	return (ptr);
}

void	ft_freetab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i++]);
	}
	free(tab);
}

void	ft_free_tabh(unsigned long **tabh)
{
	int	i;

	i = 0;
	while (tabh && tabh[i])
		free(tabh[i++]);
	free(tabh);
}

//ferme la fenetre et free
int	exit_window(t_dta *dta, char *msg)
{
	if (msg)
		printf("%s", msg);
	ft_freetab(dta->map);
	ft_freetab(dta->cub);
	free(dta->p);
	free_png(dta);
	free(dta->clr);
	mlx_close_window(dta->mlx);
	mlx_terminate(dta->mlx);
	free(dta);
	exit (0);
}
