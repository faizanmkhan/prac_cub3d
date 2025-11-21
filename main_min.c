/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_min.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faikhan <faikhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 23:54:13 by faikhan           #+#    #+#             */
/*   Updated: 2025/11/21 21:53:01 by faikhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimal.h"

static int
min_close(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	(void)argc; (void)argv;
	if (min_init(&data) != 0)
		return (1);
	min_setup_map(&data);
	/* center mouse not required here; we use keys */
	mlx_hook(data.win_ptr, 2, 1L << 0, &min_keypress, &data);
	mlx_hook(data.win_ptr, 17, 0, min_close, &data);
	mlx_loop_hook(data.mlx_ptr, min_render, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
