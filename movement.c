/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faikhan <faikhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 23:54:33 by faikhan           #+#    #+#             */
/*   Updated: 2025/11/20 23:54:35 by faikhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimal.h"

void	min_turn(t_data *data, double ang)
{
	double olddirx = data->dir.x;
	double oldplanex = data->plane.x;
	data->dir.x = data->dir.x * cos(ang) - data->dir.y * sin(ang);
	data->dir.y = olddirx * sin(ang) + data->dir.y * cos(ang);
	data->plane.x = data->plane.x * cos(ang) - data->plane.y * sin(ang);
	data->plane.y = oldplanex * sin(ang) + data->plane.y * cos(ang);
}

static int	is_walkable(t_data *d, double nx, double ny)
{
	int mx = (int)nx;
	int my = (int)ny;
	if (mx < 0 || my < 0 || mx >= d->rows || my >= d->cols)
		return (0);
	return (d->map[mx][my] == '0');
}

void	min_move_forward(t_data *data)
{
	double nx = data->player.x + data->dir.x * data->movespeed;
	double ny = data->player.y + data->dir.y * data->movespeed;
	if (is_walkable(data, nx, data->player.y))
		data->player.x = nx;
	if (is_walkable(data, data->player.x, ny))
		data->player.y = ny;
}

void	min_move_back(t_data *data)
{
	double nx = data->player.x - data->dir.x * data->movespeed;
	double ny = data->player.y - data->dir.y * data->movespeed;
	if (is_walkable(data, nx, data->player.y))
		data->player.x = nx;
	if (is_walkable(data, data->player.x, ny))
		data->player.y = ny;
}

void	min_move_left(t_data *data)
{
	double nx = data->player.x - data->plane.x * data->movespeed;
	double ny = data->player.y - data->plane.y * data->movespeed;
	if (is_walkable(data, nx, data->player.y))
		data->player.x = nx;
	if (is_walkable(data, data->player.x, ny))
		data->player.y = ny;
}

void	min_move_right(t_data *data)
{
	double nx = data->player.x + data->plane.x * data->movespeed;
	double ny = data->player.y + data->plane.y * data->movespeed;
	if (is_walkable(data, nx, data->player.y))
		data->player.x = nx;
	if (is_walkable(data, data->player.x, ny))
		data->player.y = ny;
}

int	min_keypress(int keysym, t_data *data)
{
	if (keysym == 65307 || keysym == 53) /* ESC */
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		exit(0);
	}
	if (keysym == 119) /* w */
		min_move_forward(data);
	if (keysym == 115) /* s */
		min_move_back(data);
	if (keysym == 97) /* a */
		min_move_left(data);
	if (keysym == 100) /* d */
		min_move_right(data);
	if (keysym == 65361) /* left arrow */
		min_turn(data, 0.05);
	if (keysym == 65363) /* right arrow */
		min_turn(data, -0.05);
	return (0);
}
