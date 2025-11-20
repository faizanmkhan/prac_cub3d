/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faikhan <faikhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 23:54:40 by faikhan           #+#    #+#             */
/*   Updated: 2025/11/20 23:54:46 by faikhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimal.h"

/* small local struct to keep ray variables together */
typedef struct s_ray
{
    double  raydir_x;
    double  raydir_y;
    double  side_dist_x;
    double  side_dist_y;
    double  delta_dist_x;
    double  delta_dist_y;
    int     map_x;
    int     map_y;
    int     step_x;
    int     step_y;
    int     side;
}               t_ray;

/* draw helpers */
void    min_put_pixel(t_data *data, int x, int y, int color)
{
    char *dst;

    if (x < 0 || x >= data->screen_x || y < 0 || y >= data->screen_y)
        return;
    data->addr = mlx_get_data_addr(data->img_ptr, &data->bits_per_pixel,
            &data->line_length, &data->endian);
    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

static void draw_vertical_line(t_data *d, int x, int draw_start, int draw_end, int shade)
{
    int y;

    y = 0;
    /* ceiling */
    while (y < draw_start)
    {
        min_put_pixel(d, x, y, d->ceiling_color);
        y++;
    }
    /* wall */
    while (y <= draw_end)
    {
        int color = 0xAA0000; /* base red */
        if (shade)
            color = (color >> 1) & 0x7F7F7F; /* darker */
        min_put_pixel(d, x, y, color);
        y++;
    }
    /* floor */
    while (y < d->screen_y)
    {
        min_put_pixel(d, x, y, d->floor_color);
        y++;
    }
}

static void init_ray(t_data *data, t_ray *r, double camera_x)
{
    r->raydir_x = data->dir.x + data->plane.x * camera_x;
    r->raydir_y = data->dir.y + data->plane.y * camera_x;
    r->map_x = (int)data->player.x;
    r->map_y = (int)data->player.y;
    r->delta_dist_x = (r->raydir_x == 0) ? 1e30 : fabs(1.0 / r->raydir_x);
    r->delta_dist_y = (r->raydir_y == 0) ? 1e30 : fabs(1.0 / r->raydir_y);
    if (r->raydir_x < 0)
    {
        r->step_x = -1;
        r->side_dist_x = (data->player.x - r->map_x) * r->delta_dist_x;
    }
    else
    {
        r->step_x = 1;
        r->side_dist_x = (r->map_x + 1.0 - data->player.x) * r->delta_dist_x;
    }
    if (r->raydir_y < 0)
    {
        r->step_y = -1;
        r->side_dist_y = (data->player.y - r->map_y) * r->delta_dist_y;
    }
    else
    {
        r->step_y = 1;
        r->side_dist_y = (r->map_y + 1.0 - data->player.y) * r->delta_dist_y;
    }
}

static void perform_dda(t_data *data, t_ray *r)
{
    while (1)
    {
        if (r->side_dist_x < r->side_dist_y)
        {
            r->side_dist_x += r->delta_dist_x;
            r->map_x += r->step_x;
            r->side = 0;
        }
        else
        {
            r->side_dist_y += r->delta_dist_y;
            r->map_y += r->step_y;
            r->side = 1;
        }
        if (r->map_x < 0 || r->map_y < 0 || r->map_x >= data->rows || r->map_y >= data->cols)
            break; /* out of bounds -> treat as wall */
        if (data->map[r->map_x][r->map_y] == '1')
            break;
    }
}

static void compute_and_draw(t_data *data, t_ray *r, int x)
{
    double perp_wall_dist;

    if (r->side == 0)
        perp_wall_dist = (r->side_dist_x - r->delta_dist_x);
    else
        perp_wall_dist = (r->side_dist_y - r->delta_dist_y);
    if (perp_wall_dist <= 0.0)
        perp_wall_dist = 1e-6; /* guard against division by zero or negative */
    int line_height = (int)(data->screen_y / perp_wall_dist);
    int draw_start = -line_height / 2 + data->screen_y / 2;
    if (draw_start < 0)
        draw_start = 0;
    int draw_end = line_height / 2 + data->screen_y / 2;
    if (draw_end >= data->screen_y)
        draw_end = data->screen_y - 1;
    draw_vertical_line(data, x, draw_start, draw_end, r->side == 1);
}

int    min_render(t_data *data)
{
    double x;

    /* create fresh image */
    if (data->img_ptr)
        mlx_destroy_image(data->mlx_ptr, data->img_ptr);
    data->img_ptr = mlx_new_image(data->mlx_ptr, data->screen_x, data->screen_y);
    if (!data->img_ptr)
        return (0);

    x = 0;
    while (x < data->screen_x)
    {
        t_ray r;
        double camera_x = 2.0 * x / (double)data->screen_x - 1.0;

        init_ray(data, &r, camera_x);
        perform_dda(data, &r);
        compute_and_draw(data, &r, (int)x);
        x += 1.0;
    }

    /* push image to window */
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
    return (0);
}