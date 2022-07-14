/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:04:31 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/15 01:04:27 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*
** -----------------------------------------------------------------------------
** INCLUDES, DEFINES, COLOUR CODES, ...
*/

# include "../lib/Libft/inc/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"

# include <fcntl.h>
# include <math.h>
# include <stdbool.h>

# define SUCC 1
# define FAIL 0
# define FILE_NOT_FOUND -1
# define FILENAME_NOT_CORRECT -2

# define WIDTH 640
# define HEIGHT 480
# define MOV 0.08
# define ROT 0.08

# define BLACK		"\033[0;30m"
# define RED		"\033[0;31m"
# define GREEN		"\033[0;32m"
# define YELLOW		"\033[0;33m"
# define BLUE		"\033[0;34m"
# define PURPLE		"\033[0;35m"
# define CYAN		"\033[0;36m"
# define WHITE		"\033[0;37m"
# define RESET		"\033[0m"
# define GREEN_BG	"\e[42m"

/*
** -----------------------------------------------------------------------------
** STRUCTS
*/

typedef struct	s_vect
{
	float	x;
	float	y;
}				t_vect;

typedef struct	s_colour
{
	int	red;
	int	green;
	int	blue;
}				t_colour;

typedef struct	s_ray
{
	float	camera;
	t_vect	dir;
	t_vect	pos;
	t_vect	side_dist;
	t_vect	delta_dist;
	t_vect	step;
	int		side;
	int		hit;
	float	wall_dist;
}				t_ray;

typedef struct	s_player
{
	t_vect	pos;
	t_vect	dir;
	t_vect	plane;
}				t_player;

typedef struct	s_data
{
	t_player	*player;
	char		*file;
	char		**map;
	int			map_int[10][10]; //temp
	char		*n_texture;
	char		*e_texture;
	char		*s_texture;
	char		*w_texture;
	t_colour	c_colour;
	t_colour	f_colour;

	mlx_t		*mlx;
	mlx_image_t	*img;
}				t_data;

typedef struct	s_parser_check
{
	bool	n_identifier;
	bool	e_identifier;
	bool	s_identifier;
	bool	w_identifier;
	bool	c_identifier;
	bool	f_identifier;
	bool	map_identifier;
}				t_parser_check;

/*
** -----------------------------------------------------------------------------
** FUNCTIONS
*/

int		file_parser(char *filename);
void	raycast_dda_prototype(t_data *data);

void	raycast_prototype_2();
void	raycast_prototype_3(mlx_image_t *img);
float	deg_to_rad(float degree);

void hook(void *param);

// NOTE:
// [X,Y]
// Looking North:	DIR[0, -1], PLANE[-0.66, 0]
// Looking East:	DIR[-1, 0], PLANE[0, 0.66]
// Looking South:	DIR[0, 1], PLANE[0.66, 0]
// Looking West:	DIR[1, 0], PLANE[0, -0.66]

#endif