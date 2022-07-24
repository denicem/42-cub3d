/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:04:31 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/24 19:19:06 by dmontema         ###   ########.fr       */
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

# define SUCCESS 0
# define FAILURE 1
# define FILE_NOT_FOUND -1
# define FILENAME_NOT_CORRECT -2

# define WIDTH 1920
# define HEIGHT 1080
# define PLANE 1.66
# define MOV 0.055
# define ROT 0.033

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

typedef struct s_str_node
{
	char				*str;
	bool				map;
	bool				empty;
	struct s_str_node	*next;
}					t_str_node;

t_str_node	*new_str_node(char *str);
t_str_node	*get_last_str_node(t_str_node *head);
t_str_node	*append_str_node(t_str_node **head, t_str_node *new);
void		del_last_node(t_str_node **head);
void		free_str_node(t_str_node **node);

typedef struct s_parser_check
{
	bool	n_identifier;
	bool	e_identifier;
	bool	s_identifier;
	bool	w_identifier;
	bool	c_identifier;
	bool	f_identifier;
}				t_parser_check;

typedef struct s_invec
{
	int	x;
	int	y;
}				t_invec;

typedef struct s_vect
{
	float	x;
	float	y;
}				t_vect;

typedef struct s_colour
{
	int	red;
	int	green;
	int	blue;
}				t_colour;

typedef struct s_ray
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

typedef struct s_player
{
	t_vect	pos;
	t_vect	dir;
	t_vect	plane;
}				t_player;

typedef struct s_data
{
	int				fd;
	char			*file_path;
	t_str_node		*file_data;

	t_player		*player;
	t_player		player_start;
	char			**map;
	int				map_width;
	int				map_height;
	char			**texture_paths;
	t_colour		c_colour;
	t_colour		f_colour;
	mlx_texture_t	*png[4];
	t_ray			ray;
	int				tex_x;
	int				tex_y;

	mlx_t			*mlx;
	mlx_image_t		*img;

	t_parser_check	check;
}					t_data;

/*
** -----------------------------------------------------------------------------
** FUNCTIONS
*/

void		init_data(t_data *data);
int			file_parser(char *filename);
void		get_data(t_data *data);
void		parser(t_data *data);
void		init_val(t_data *data);
void		texture_identifier(t_data *data, char *dir, char *path);
void		color_identifier(t_data *data, char c, char *c_code);
void		map_parser(t_data *data);

void		create_map(t_data *data);
bool		is_player_char(int c);
bool		is_surround_char(int c);
bool		is_map_char(int c);
bool		is_str_map(char *str);
t_str_node	*get_first_map_str(t_str_node *node);
void		set_player(t_data *data);

void		raycast(t_data *data);
void		init_ray(t_ray *ray, t_data *data, int rayCount);
void		set_dist(t_ray *ray, t_data *data);
void		dda(t_ray *ray, t_data *data);
void		set_ray_dist(t_ray *ray);
void		set_draw_val(t_ray *ray, int *height, int *wallStart, int *wallEnd);

int			render_world(t_data *data);
void		draw_vertical_line(int ray_count, int wallStart,
				int wallEnd, t_data *data);
int			get_rgba(t_data *data, int c, int a);

void		hook(void *param);

void		insert_textures(t_data *info, int x, int draw_start, int draw_end);
int			get_textures(t_data *data);

void		exit_error(t_data *data, char *msg, int error_code);
void		free_data(t_data *data);

#endif