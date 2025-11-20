/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimal.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faikhan <faikhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 23:54:28 by faikhan           #+#    #+#             */
/*   Updated: 2025/11/20 23:54:31 by faikhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAL_H
# define MINIMAL_H

# include "minilibx/mlx.h"
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>

typedef struct s_pos
{
	double	x;
	double	y;
}t_pos;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		screen_x;
	int		screen_y;

	/* simple map */
	char	**map;
	int		rows;
	int		cols;

	/* player */
	t_pos	player;
	t_pos	dir;
	t_pos	plane;
	double	movespeed;

	/* colors */
	int		floor_color;
	int		ceiling_color;
}t_data;

/* main */
int		minimal_main(void);

/* init */
int		min_init(t_data *data);
void	min_setup_map(t_data *data);

/* render */
int		min_render(t_data *data);
void	min_put_pixel(t_data *data, int x, int y, int color);

/* input */
int		min_keypress(int keysym, t_data *data);
void	min_move_forward(t_data *data);
void	min_move_back(t_data *data);
void	min_move_left(t_data *data);
void	min_move_right(t_data *data);
void	min_turn(t_data *data, double ang);

#endif
