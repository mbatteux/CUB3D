/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 22:19:22 by jolecomt          #+#    #+#             */
/*   Updated: 2024/03/09 23:35:15 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	free_1(t_dta *dta)
{
	free(dta->map);
	free(dta->clr);
	free_png(dta);
	free(dta->p);
	free(dta);
}

void	free_2(t_dta *dta)
{
	ft_freetab(dta->map);
	free(dta->clr);
	free_png(dta);
	free(dta->p);
	free(dta);
}

void	free_3(t_dta *dta)
{
	ft_freetab(dta->map);
	free(dta->cub);
	free(dta->clr);
	free_png(dta);
	free(dta->p);
	free(dta);
}

void	free_4(t_dta *dta)
{
	ft_freetab(dta->map);
	ft_freetab(dta->cub);
	free(dta->clr);
	free_png(dta);
	free(dta->p);
	free(dta);
}
