/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 12:46:30 by bogunlan          #+#    #+#             */
/*   Updated: 2022/08/28 05:01:20 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLONG_H

# define SOLONG_H
# define WIDTH 960
# define HEIGHT 288
# define OBJ_LENGTH 42

# include <unistd.h>
# include <stdlib.h>
#include <stdio.h>
# include "MLX42/include/MLX42/MLX42.h"
# include "gnl/get_next_line.h"
# include "../libft/libft.h"

// My struct to save lines
typedef struct s_params
{
	int		i;
	int		j;
	int		valid_file;
}			t_params;

// variables to create textures
typedef struct s_texture
{
	mlx_texture_t	*wall_texture;
	mlx_texture_t	*player_texture;
	mlx_texture_t	*bg_texture;
	mlx_texture_t	*collectible_texture;
	mlx_texture_t	*escape_texture;
}				t_texture;

// variables to create an image
typedef struct s_game_image
{
	mlx_image_t	*player;
	mlx_image_t	*wall;
	mlx_image_t	*collectible;
	mlx_image_t	*escape;
	mlx_image_t	*bg;
}				t_game_image;

// variables to parse the map
typedef struct s_map_parsing
{
	int		x;
	int		y;
	int		j;
	int		fd;
	int		player_count;
	int		escape_count;
	int		collectible_count;
	int		space_count;
	char	*line;
}			t_map_parsing;

// variables to create map data and work with the map (coordinates)
typedef struct s_map_data
{
	char	*arr[10000000];
	int		player_location_x;
	int		player_location_y;
	int		movement_count;
	int		line_count;
	int		map_width1;
	int		map_width2;
	int		last_line;
}			t_map_data;

void	create_textures(t_texture *val);
void	create_g_images(t_game_image* g_images, mlx_t *mlx, t_texture *val);
void	parse_game_map(mlx_t *mlx, t_map_parsing *p_map);
void	check_map_dimensions(void);
void	w_key_pressed(int grabbed_eggs, int egg_index, int wall_index);
void	s_key_pressed(int grabbed_eggs, int egg_index, int wall_index);
void	d_key_pressed(int grabbed_eggs, int egg_index, int wall_index);
void	a_key_pressed(int grabbed_eggs, int egg_index, int wall_index);
void	check_walls(t_map_data *g_m_data);
void	clean_up(mlx_t *mlx, t_texture *val);
int		picked_collectible(int egg_index);
int		check_for_w_move(int grabbed_eggs, int egg_index, int wall_index);
int		check_for_s_move(int grabbed_eggs, int egg_index, int wall_index);
int		check_for_a_move(int grabbed_eggs, int egg_index, int wall_index);
int		check_for_d_move(int grabbed_eggs, int egg_index, int wall_index);
int		player_wins(int grabbed_eggs, int i, int j);
int		player_on_collectible_tile(int egg_index);
int		wall_in_w_direction(int wall_index);
int		wall_in_s_direction(int wall_index);
int		wall_in_a_direction(int wall_index);
int		wall_in_d_direction(int wall_index);
int		picked_collectibles_count(int collectibles_count, int grabbed_eggs);












#endif
