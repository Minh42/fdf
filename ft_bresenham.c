/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bresenham.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpham <mpham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 11:31:17 by mpham             #+#    #+#             */
/*   Updated: 2018/01/25 16:08:14 by mpham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    ft_bresenham1(void *mlx, void *win, t_algo *b)
{
    int i;

    i = 0;
	mlx_pixel_put(mlx, win, b->x, b->y, 0x0000FFFF);
    b->e = 2 * b->dy - b->dx;
    b->inc1 = 2 * (b->dy - b->dx);
    b->inc2 = 2 * b->dy;
    while (i < b->dx)
    {
        if(b->e >= 0)
        {
            b->y += b->incY;
            b->e += b->inc1;
        }
        else
        {
            b->e += b->inc2;
            b->x += b->incX;
        }
        mlx_pixel_put(mlx, win, b->x, b->y, 0x0000FFFF);
        i++; 
    }
}

void    ft_bresenham2(void *mlx, void *win, t_algo *b)
{
    int i;

    i = 0;
	mlx_pixel_put(mlx, win, b->x, b->y, 0x0000FFFF);
    b->e = 2 * b->dx - b->dy;
    b->inc1 = 2 * (b->dx - b->dy);
    b->inc2 = 2 * b->dx;
    while(i < b->dy)
    {
        if(b->e >= 0)
        {
            b->x += b->incX;
            b->e += b->inc1;
        }
        else 
        {
            b->e += b->inc2;
            b->y += b->incY;
        }
 	    mlx_pixel_put(mlx, win, b->x, b->y, 0x0000FFFF);
        i++;        
    }
}

void    ft_bresenham(void *mlx, void *win, int x1, int y1, int x2, int y2)
{
    t_algo  b;

    b.dx = x2 - x1;
    b.dy = y2 - y1;
    if (b.dx > 0)
        b.incX = 1;
    else
    {
        b.incX = -1;
        b.dx = -(b.dx);
    }      
    if (b.dy > 0)
        b.incY = 1;
    else
    {
        b.incY = -1;
        b.dy = -(b.dy); 
    }
    b.x = x1;
    b.y = y1;
    if (b.dx > b.dy)
        ft_bresenham1(mlx, win, &b);
    else
        ft_bresenham2(mlx, win, &b);
}
