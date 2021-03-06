/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpham <mpham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 13:13:24 by minh              #+#    #+#             */
/*   Updated: 2018/01/22 17:54:49 by mpham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "math3D.h"

void        draw_form(void *mlx, void *win, t_list *list)
{
    int         x;
	int         y;
    int         z;
    // int         w;
    // vec3_t     	vecteur;
    // vec4_t     	vecteur_pos;
    // vec4_t     	matrice;
	// mat4_t     	translation;
	// mat4_t		rotationz;
	// mat4_t		rotationy;
	// vec4_t		resultat;

	x = 0;
    y = 0;
    z = 0;
    // w = 1;
    // vecteur = vec3((WIN_WIDTH - (19 * TILE_WIDTH)) / 2, (WIN_HEIGHT - (11 * TILE_HEIGHT)) / 2, 0);
	// translation = m4_translation(vecteur);
	// rotationz = m4_rotationz(330 * 3.14 / 180);
	// rotationy = m4_rotationy(45 * 3.14 / 180);

	while (list)
	{
		x = ((t_point *)(*list).content)->x; 
		y = ((t_point *)(*list).content)->y;
		z = ((t_point *)(*list).content)->z;
		x = x * TILE_WIDTH;
		y = y * TILE_HEIGHT;
		// vecteur_pos = vec4(x, y, z, w);
		// matrice = m4_mult_pos(rotationz, vecteur_pos);
		// resultat = m4_mult_pos(rotationy, matrice);
		// resultat = m4_mult_pos(translation, resultat);
		ft_bresenham(mlx, win, 0, 0, 25, 0);
		list = list->next;
	}
}

int     expose_hook(t_env *e)
{
	draw_form(e->mlx, e->win, e->list);
	return (0);
}

// int     mouse_hook(int button, int x, int y, t_env *e)
// {
//     printf("mouse: %d (%d:%d)\n", button, x, y);
//     return (0);
// }

// int     key_hook(int keycode, t_env *e)
// {
//     printf("key event %d\n", keycode);
//     if (keycode == 53) // exit
//         exit(0);
//     if (keycode == 49) // reset

//     if (keycode == 126) // up
//     if (keycode == 125) // down
//     if (keycode == 124) // right
//     if (keycode == 123) // left

//     return (0);
// }


t_list **ft_read_and_stock(t_list **list, char *line)
{
	int         i;
	int         x;
	static int  y = 0;
	char        **str;

	i = 0;
	x = 0;
	str = ft_strsplit(line, ' ');
	while (str[i] != '\0')
	{
		if (((*list = (t_list*)malloc(sizeof(t_list))) == NULL) ||
				((*list)->content = (t_point*)malloc(sizeof(t_point) * 4)) == NULL)
			exit(1);
		((t_point *)(*list)->content)->x = x;
		((t_point *)(*list)->content)->y = y;
		((t_point *)(*list)->content)->z = ft_getnbr(&str[i][0]);
		((t_point *)(*list)->content)->color = ft_strchr(str[i], ',') ?  &str[i][2] : "0xFFFFFF";
		i++;
		x++;
		list = &(*list)->next;
	}
	*list = NULL;
	y++;
	return (list);
}

int		main(int argc, char **argv)
{
	int		fd;
	char	*line;
	t_list  *list;
	t_list  **p_list;
	t_env   e;

	if (argc != 2)
		ft_putstr("too many or too few arguments\n");
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		ft_putstr("open() failed\n");
	}
	p_list = &list;
	while (get_next_line(fd, &line) > 0)
	{
		p_list = ft_read_and_stock(p_list, line);
	}
	//ft_print_list(list);
	free(line);
	if (close(fd) == -1)
	{
		ft_putstr("close() failed\n");
	}
	e.mlx = mlx_init();
	e.win = mlx_new_window(e.mlx, WIN_WIDTH, WIN_HEIGHT, "mlx 42");
	e.list = list;
	mlx_expose_hook(e.win, expose_hook, &e);
	// mlx_key_hook(e.win, key_hook, &e);
	// mlx_mouse_hook(e.win, mouse_hook, &e);
	mlx_loop(e.mlx);
	return (0);
}
