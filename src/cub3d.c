/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:41:26 by mbatteux          #+#    #+#             */
/*   Updated: 2024/03/10 00:46:14 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

//segfault avec les portes si elles sont en bordure de map !!!!

int	main(int argc, char **argv)
{
	t_dta	*dta;

	dta = NULL;
	if (argc == 2)
	{
		dta = ft_calloc(1, sizeof(t_dta) + 1);
		if (!dta)
			return (0);
		if (dta_init(dta, argv[1]) == -1)
			return (err("Error\nInitialisation failed \n"));
		dta->mlx = mlx_init(X, Y, "cub3d", 0);
		dta->img = mlx_new_image(dta->mlx, X, Y);
		mlx_set_cursor_mode(dta->mlx, MLX_MOUSE_HIDDEN);
		ft_reload(dta, dta->p);
		mlx_image_to_window(dta->mlx, dta->img, 0, 0);
		mlx_cursor_hook(dta->mlx, deal_mouse, dta);
		mlx_loop_hook(dta->mlx, deal_key, dta);
		mlx_loop(dta->mlx);
	}
	else
		return (err("Error:\nToo many or too few arguments\n"));
	exit_window(dta, "THANKS FOR PLAYING !\n");
	return (0);
}
