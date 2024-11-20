/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_keybindings.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:50:45 by mbatteux          #+#    #+#             */
/*   Updated: 2024/03/09 23:35:01 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

//Permet de se deplacer
void	direction(t_p *p, int key, float *x, float *y)
{
	if (key == MLX_KEY_W)
	{
		(*y) += sin(p->pan) * SPD;
		(*x) += cos(p->pan) * SPD;
	}
	if (key == MLX_KEY_S)
	{
		(*y) -= sin(p->pan) * SPD;
		(*x) -= cos(p->pan) * SPD;
	}
	if (key == MLX_KEY_D)
	{
		(*y) += sin(p->pan + PI / 2) * SPD;
		(*x) += cos(p->pan + PI / 2) * SPD;
	}
	if (key == MLX_KEY_A)
	{
		(*y) -= sin(p->pan + PI / 2) * SPD;
		(*x) -= cos(p->pan + PI / 2) * SPD;
	}
}

//deplace le joueur remplace sa position par la nouvelle
void	keybind(t_dta *dta, t_p *p, int key)
{
	float	x;
	float	y;

	x = p->px;
	y = p->py;
	direction(p, key, &x, &y);
	if (dta->cub[(int)y][(int)x] == '1' || dta->cub[(int)y][(int)x] == 'P')
		return ;
	p->py = y;
	p->px = x;
}

void	deal_mouse(double posx, double posy, void *param)
{
	t_dta	*dta;

	dta = param;
	mlx_get_mouse_pos(dta->mlx, (int32_t *)&posx, (int32_t *)&posy);
	if (posx > dta->mousex + 10)
		dta->p->pan += SENSI_MOUSE * RA;
	else if (posx < dta->mousex - 10)
		dta->p->pan -= SENSI_MOUSE * RA;
	mlx_set_mouse_pos(dta->mlx, X / 2, Y / 2);
}

void	open_or_close(mlx_key_data_t keydata, void *param)
{
	t_dta	*dta;

	dta = param;
	if (keydata.key != MLX_KEY_F || keydata.action != MLX_PRESS)
		return ;
	if (find_len_ray(dta, dta->p, dta->p->pan) - 1 < 2)
	{
		if (dta->cub[(int)dta->p->py][(int)dta->p->px - 1] == 'P')
			dta->cub[(int)dta->p->py][(int)dta->p->px - 1] = 'O';
		else if (dta->cub[(int)dta->p->py][(int)dta->p->px - 1] == 'O')
			dta->cub[(int)dta->p->py][(int)dta->p->px - 1] = 'P';
		else if (dta->cub[(int)dta->p->py][(int)dta->p->px + 1] == 'P')
			dta->cub[(int)dta->p->py][(int)dta->p->px + 1] = 'O';
		else if (dta->cub[(int)dta->p->py][(int)dta->p->px + 1] == 'O')
			dta->cub[(int)dta->p->py][(int)dta->p->px + 1] = 'P';
		else if (dta->cub[(int)dta->p->py + 1][(int)dta->p->px] == 'P')
			dta->cub[(int)dta->p->py + 1][(int)dta->p->px] = 'O';
		else if (dta->cub[(int)dta->p->py + 1][(int)dta->p->px] == 'O')
			dta->cub[(int)dta->p->py + 1][(int)dta->p->px] = 'P';
		else if (dta->cub[(int)dta->p->py - 1][(int)dta->p->px] == 'P')
			dta->cub[(int)dta->p->py - 1][(int)dta->p->px] = 'O';
		else if (dta->cub[(int)dta->p->py - 1][(int)dta->p->px] == 'O')
			dta->cub[(int)dta->p->py - 1][(int)dta->p->px] = 'P';
	}
}

//permet de recuperer les touches et les envoie a keybind 
void	deal_key(void *param)
{
	t_dta	*dta;

	dta = param;
	mlx_key_hook(dta->mlx, open_or_close, dta);
	if (mlx_is_key_down(dta->mlx, MLX_KEY_ESCAPE))
		exit_window(dta, "THANKS FOR PLAYING !\n");
	if (mlx_is_key_down(dta->mlx, MLX_KEY_S))
		keybind(dta, dta->p, MLX_KEY_S);
	else if (mlx_is_key_down(dta->mlx, MLX_KEY_W))
		keybind(dta, dta->p, MLX_KEY_W);
	else if (mlx_is_key_down(dta->mlx, MLX_KEY_D))
		keybind(dta, dta->p, MLX_KEY_D);
	else if (mlx_is_key_down(dta->mlx, MLX_KEY_A))
		keybind(dta, dta->p, MLX_KEY_A);
	if (mlx_is_key_down(dta->mlx, MLX_KEY_LEFT))
		dta->p->pan -= SENSI * RA;
	if (mlx_is_key_down(dta->mlx, MLX_KEY_RIGHT))
		dta->p->pan += SENSI * RA;
	ft_reload(dta, dta->p);
	return ;
}
