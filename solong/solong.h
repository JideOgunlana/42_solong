/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 12:46:30 by bogunlan          #+#    #+#             */
/*   Updated: 2023/06/09 16:52:44 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLONG_H

# define SOLONG_H
# define WIDTH 960
# define HEIGHT 288
# define L 42

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "MLX42/include/MLX42/MLX42.h"
# include "includes/gnl/get_next_line.h"
# include "includes/libft/libft.h"

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
	mlx_image_t	*p;
	mlx_image_t	*w;
	mlx_image_t	*c;
	mlx_image_t	*e;
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
	int		p_x;
	int		p_y;
	int		movement_count;
	int		lc;
	int		mw1;
	int		mw2;
	int		last_line;
}			t_map_data;

typedef struct s_tex_img
{
	mlx_image_t	*p_t_i;
	mlx_image_t	*w_t_i;
	mlx_image_t	*bg_t_i;
	mlx_image_t	*c_t_i;
	mlx_image_t	*e_t_i;
}				t_tex_img;

t_game_image	*g_img(void);
t_map_data		*g_m_data(void);
t_params		*all(void);
void			create_textures(t_texture *val);
void			create_g_images(mlx_t *mlx, t_texture *val);
void			parse_game_map(mlx_t *mlx, t_map_parsing *p_map);
int				check_map_dimensions(void);
void			w_key_pressed(int grabbed_eggs, int egg_index, int w_i);
void			s_key_pressed(int grabbed_eggs, int egg_index, int w_i);
void			d_key_pressed(int grabbed_eggs, int egg_index, int w_i);
void			a_key_pressed(int grabbed_eggs, int egg_index, int w_i);
void			check_walls(void);
void			clean_up(mlx_t *mlx, t_texture *val);
int				picked_collectible(int egg_index);
int				check_for_w_move(int grabbed_eggs, int egg_index, int w_i);
int				check_for_s_move(int grabbed_eggs, int egg_index, int w_i);
int				check_for_a_move(int grabbed_eggs, int egg_index, int w_i);
int				check_for_d_move(int grabbed_eggs, int egg_index, int w_i);
int				player_wins(int grabbed_eggs, int i, int j);
int				player_on_collectible_tile(int egg_index);
int				wall_in_w_direction(int w_i);
int				wall_in_s_direction(int w_i);
int				wall_in_a_direction(int w_i);
int				wall_in_d_direction(int w_i);
int				picked_collectibles_count(int c_count, int grabbed_eggs);

#endif
