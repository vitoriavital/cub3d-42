/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_3d_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavitori <mavitori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:08:53 by mavitori          #+#    #+#             */
/*   Updated: 2024/10/22 17:29:31 by mavitori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_3D_BONUS_H
# define CUB_3D_BONUS_H

# include "../libs/MLX42/include/MLX42/MLX42.h"
# include "../libs/libft/libft.h"
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

// # define MAP_WIDTH 10
// # define MAP_HEIGHT 10 tirei
# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 600
# define PI 3.141592653589793

typedef enum e_direction	t_direction;
enum						e_direction
{
	EAST = -4,
	WEST = -3,
	SOUTH = -2,
	NORTH = -1,
	UP = 0,
	DOWN = 1,
	RIGHT = 2,
	LEFT = 3,
};

typedef enum e_wall_type	t_wall_type;
enum						e_wall_type
{
	WALL = 0,
	DOOR = 1,
	PORTAL = 2,
};

typedef struct s_mini
{
	int			width;
	int			height;
	int			offset;
	int			px;
	int			py;
	int			tile;
}				t_mini;

typedef struct s_player
{
	int			line;
	int			column;
	t_direction	dir;
}				t_player;

typedef struct s_map
{
	char		*north_texture;
	char		*south_texture;
	char		*west_texture;
	char		*east_texture;
	char		*door_texture;
	char		*portal_texture;
	char		*floor_color;
	char		*ceiling_color;
	char		*old_floor_color;
	char		*old_ceiling_color;
	char		**full_map;
}				t_map;

typedef struct s_vector
{
	float	x;
	float	y;
}				t_vector;

typedef struct s_wall
{
	int			height;
	int			start;
	int			end;
	double		x;
	double		step;
	double		tex_pos;
	int			tex_height;
	int			tex_width;
	int			tex_x;
	int			tex_y;
}				t_wall;

typedef struct s_dda
{
	double		multiplier;
	float		delta_dist_x;
	float		delta_dist_y;
	float		dist_to_side_x;
	float		dist_to_side_y;
	int			step_x;
	int			step_y;
	int			hit_side;
	float		tmp_dda_x;
	float		tmp_dda_y;
	float		player_dist_wall;
	float		wall_x;
	float		wall_y;
	int			wall_type;
}				t_dda;

typedef struct s_game
{
	t_map			*map;
	char			**map_fill;
	t_player		*player;
	mlx_image_t		*image;
	mlx_t			*mlx;
	t_vector		*pos;
	t_vector		*dir;
	t_vector		*plane;
	t_vector		*map_pos;
	t_vector		*camera_pixel;
	t_vector		*ray_dir;
	uint32_t		current_pixel;
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*ea;
	mlx_texture_t	*we;
	mlx_texture_t	*door;
	mlx_texture_t	*portal;
	mlx_texture_t	*texture;
}				t_game;

// VECTOR UTILS
float		ft_vector_magnitude(t_vector *v);
void		ft_vector_normalize(t_vector *v);
void		ft_vector_rotate(t_vector *v, float angle);

// VECTOR OPERATIONS
t_vector	*ft_vector_create(float x, float y);
void		ft_vector_add(t_vector *v1, t_vector *v2, t_vector *result);
t_vector	*ft_vector_copy(t_vector *v);
void		ft_vector_floor(t_vector *v, t_vector *result);
void		ft_vector_scalar(t_vector *v, double scalar, t_vector *result);

// SETUP
void		player_direction(t_game *game);
int			read_map(char *map_file, t_game *game);

// FREE DATA
void		free_game(t_game *game);
int			free_invalid_content(char **config, char **map);
void		free_split(char **content);

// HOOKS
void		ft_hook(void *param);
void		move_player_up_down(t_game *game, int key, int multiplier);
void		move_player_left_right(t_game *game, int key, int multiplier);

// BUILD
void		delta_dist(t_game *game, t_dda *dda);
void		dist_to_side(t_game *game, t_dda *dda);
void		build_ray(t_game *game, t_dda *dda);

// DRAW
void		draw_floor(t_game *game);
void		draw_ceiling(t_game *game);
void		draw_wall(t_game *game, float dist, t_dda *dda);
int32_t		ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
// GAME
void		ft_game(void *param);

// DRAW TEXTURE
void		draw_wall_line(t_wall *wall, t_dda *dda, t_game *game);

// VALIDATE MAP
void		set_position(char **map, t_game *game);
void		count_player(char c, int *player);
int			check_map(char **lines, t_game *game);
int			check_file_dir(char *file);

// VALIDATE CONFIG
int			check_c_f(char *rgb);
int			check_config_signal(char *line);
int			check_config(char **line, t_game *game);

//PARSER
int			read_file(char *map_file, t_game *game);

// MINI MAP
void		ft_mini_map(void *param);

// DOOR PORTAL
void		switch_door_portal(t_game *game);

#endif