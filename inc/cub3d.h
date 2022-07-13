/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:04:31 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/14 01:47:02 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/Libft/inc/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"

# include <fcntl.h>
# include <math.h>
# include <stdbool.h>

# define SUCC 1
# define FAIL 0
# define FILE_NOT_FOUND -1
# define FILENAME_NOT_CORRECT -2

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
	char		*map;
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

int		file_parser(char *filename);
void	raycast_dda_prototype(mlx_t *mlx, mlx_image_t *img);

void	raycast_prototype_2();
void	raycast_prototype_3(mlx_image_t *img);
float	deg_to_rad(float degree);

void hook(void *param);

t_vect start_pos;
t_vect dir;
t_vect plane;

# define WIDTH 1080
# define HEIGHT 720

# define PI 3.1415926535
# define PI2 PI/2
# define PI3 3 * PI / 2

#define MOV 0.5
#define ROT 0.02
#define FOV 60

t_vect player;
float player_angle;

// NOTE:
// [X,Y]
// Looking North:	DIR[0, -1], PLANE[-0.66, 0]
// Looking East:	DIR[-1, 0], PLANE[0, 0.66]
// Looking South:	DIR[0, 1], PLANE[0.66, 0]
// Looking West:	DIR[1, 0], PLANE[0, -0.66]

#endif