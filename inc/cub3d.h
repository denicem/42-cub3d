/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:04:31 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/21 17:51:24 by mrojas-e         ###   ########.fr       */
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

# define WIDTH 1920
# define HEIGHT 1080
# define PLANE 1.66
# define MOV 0.055
# define ROT 0.022

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

typedef struct		s_str_node
{
	char				*str;
	bool				map;
	struct s_str_node	*next;
}					t_str_node;

t_str_node	*new_str_node(char *str);
t_str_node	*get_last_str_node(t_str_node *head);
t_str_node	*append_str_node(t_str_node **head, t_str_node *new);

typedef struct	s_invec
{
	int	x;
	int	y;
}				t_invec;

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
	t_invec	pos;
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
	int				fd;
	char			*file_path;
	t_str_node		*file_data;
	
	t_player		*player;
	t_player		player_start;
	char			**map;
	int				map_width;
	int				map_height;
	int				side;
	mlx_texture_t	png[4];
	char			*n_texture;
	char			*e_texture;
	char			*s_texture;
	char			*w_texture;
	t_colour		c_colour;
	t_colour		f_colour;

	mlx_t			*mlx;
	mlx_texture_t	*m_wall;
	mlx_image_t		*img;
}					t_data;

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

void	init_data(t_data *data);
int		file_parser(char *filename);
void	get_data(t_data *data);
void	parser(t_data *data);
void	init_val(t_data *data);

void		create_map(t_data *data);
bool		is_player_char(int c);
bool		is_surround_char(int c);
bool		is_map_char(int c);
bool		is_str_map(char *str);
t_str_node	*get_first_map_str(t_str_node *node);

void	set_player(t_data *data);

void	raycast(t_data *data);
void	init_ray(t_ray *ray, t_data *data, int rayCount);
void	set_dist(t_ray *ray, t_data *data);
void	dda(t_ray *ray, t_data *data);
void	set_ray_dist(t_ray *ray);
void	set_draw_val(t_ray *ray, int *height, int *wallStart, int* wallEnd);

int		render_world(t_data *data);
void	draw_vertical_line(int ray_count, int wallStart, int wallEnd, t_data *data, t_ray *ray);
int		get_rgba(int r, int g, int b, int a);

void	hook(void *param);

// NOTE: temp funcs - for debuggin' purposes
void	print_str_node(t_str_node *node);
void	print_map(t_data *data);
void	print_player_info(t_data *data);

// TEXTURES

void	insert_textures(t_data *info, int x, int draw_start, int draw_end, t_ray *ray);
int	get_textures(t_data *data);
#endif