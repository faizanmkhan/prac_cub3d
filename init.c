/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faikhan <faikhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 23:54:03 by faikhan           #+#    #+#             */
/*   Updated: 2025/11/20 23:54:05 by faikhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimal.h"

static char *default_map[] = {
"1111111111111111111111111",
"1000000000110000000000001",
"1011000001110000000000001",
"10010000000D0000000000001",
"1111111110110000011100001",
"100000000011011111D111111",
"1111D111111111D11100000011111",
"11110111111111011101010010001",
"11000000110101011100000010001",
"10000000000000001100000010001",
"10000000000000001101010010001",
"11000001110101011111011110S01",
"11110111 1110101 101111010001",
"11111111 1111111 11111111AAA1",
	NULL
};

int	min_init(t_data *data)
{
	data->screen_x = 640;
	data->screen_y = 480;
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
	{
		fprintf(stderr, "Error: mlx_init failed\n");
		return (1);
	}
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->screen_x, data->screen_y, "minimal_cub3d");
	if (!data->win_ptr)
	{
		fprintf(stderr, "Error: window creation failed\n");
		return (1);
	}
	data->img_ptr = mlx_new_image(data->mlx_ptr, data->screen_x, data->screen_y);
	if (!data->img_ptr)
	{
		fprintf(stderr, "Error: image creation failed\n");
		return (1);
	}
	/* map */
	int i = 0;
	while (default_map[i]) i++;
	data->rows = i;
	data->cols = (int)strlen(default_map[0]);
	data->map = malloc(sizeof(char *) * (data->rows + 1));
	for (i = 0; i < data->rows; i++)
		data->map[i] = strdup(default_map[i]);
	data->map[data->rows] = NULL;

	/* player */
	data->player.x = 5.0;
	data->player.y = 5.0;
	/* facing north-ish */
	data->dir.x = -1.0;
	data->dir.y = 0.0;
	/* camera plane (FOV) */
	data->plane.x = 0.0;
	data->plane.y = 0.66;
	data->movespeed = 0.12;

	/* colors */
	data->ceiling_color = 0x87CEEB; /* skyblue */
	data->floor_color = 0x707070; /* gray */
	return (0);
}

void	min_setup_map(t_data *data)
{
	/* no-op here (map already set in min_init) */
	(void)data;
}
