/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faikhan <faikhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 23:54:03 by faikhan           #+#    #+#             */
/*   Updated: 2025/11/21 21:47:05 by faikhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimal.h"

static char *default_map[] = {
"1111111111111111111111111",
"1000000000110000000000001",
"1011000001110000000000001",
"1001000000011000000000001",
"1110000000000000000000001",
"1000000000110111111101111",
"1000000000000000000000001",
"1111011111111101110010001",
"1100000011010101000010001",
"1000000000000000100010001",
"1000000000000000110010001",
"1100000000000000000000001",
"1111111111110101110110001",
	NULL
};

static int	init_mlx_window_image(t_data *data)
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
	return (0);
}

static int	init_map(t_data *data)
{
	int i = 0;

	while (default_map[i])
		i++;
	data->rows = i;
	data->cols = (int)strlen(default_map[0]);
	data->map = malloc(sizeof(char *) * (data->rows + 1));
	if (!data->map)
	{
		fprintf(stderr, "Error: malloc failed for map\n");
		return (1);
	}
	for (i = 0; i < data->rows; i++)
	{
		data->map[i] = strdup(default_map[i]);
		if (!data->map[i])
		{
			fprintf(stderr, "Error: strdup failed for map row %d\n", i);
			return (1);
		}
	}
	data->map[data->rows] = NULL;
	return (0);
}

static void	init_player_and_camera(t_data *data)
{
	data->player.x = 5.0;
	data->player.y = 5.0;
	/* facing north-ish */
	data->dir.x = -1.0;
	data->dir.y = 0.0;
	/* camera plane (FOV) */
	data->plane.x = 0.0;
	data->plane.y = 0.66;
	data->movespeed = 0.12;
}

static void	init_colors(t_data *data)
{
	data->ceiling_color = 0x87CEEB; /* skyblue */
	data->floor_color = 0x707070; /* gray */
}

int	min_init(t_data *data)
{
	if (init_mlx_window_image(data) != 0)
		return (1);
	if (init_map(data) != 0)
		return (1);
	init_player_and_camera(data);
	init_colors(data);
	return (0);
}

void	min_setup_map(t_data *data)
{
	/* no-op here (map already set in min_init) */
	(void)data;
}
