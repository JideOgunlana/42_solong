// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   test.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/01/31 00:40:08 by W2Wizard          #+#    #+#             */
// /*   Updated: 2022/08/16 14:49:03 by bogunlan         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "MLX42/include/MLX42/MLX42.h"

#include "gnl/get_next_line.h"

#define WIDTH 960
#define HEIGHT 288


// My struct to save lines

typedef struct params_s
{
	int		i;
	int		j;
}			params_t;


// variables to create textures
typedef struct texture_s
{
	mlx_texture_t* wall_texture;
	mlx_texture_t* texture;
	mlx_texture_t* bg_texture; 
	mlx_texture_t* collectible_texture;
	mlx_texture_t* escape_texture;
}				texture_t;

// variables to create an image
typedef struct game_images_s
{
	mlx_image_t	*img;
	mlx_image_t	*wall;
	mlx_image_t	*collectible;
	mlx_image_t	*escape;
	mlx_image_t	*bg;
}				game_image_t;

game_image_t *images;

// variables to parse the map
typedef struct map_parsing_s
{
	int		x;
	int		y;
	int		j;
	int		fd;
	int		player_count;
	int		escape_count;
	int		collectible_count;
	char	*line;

}			map_parsing_t;


// variables to create map data and work with the map (coordinates)
int player_location_x;
int player_location_y;
char *arr[10000000];
int movement_count = 0;
int line_count = 0;
int map_width1 = 0;
int map_width2 = 0;
int last_line;


int object_length = 42;

int	wall_in_w_direction(int wall_index)
{
	if (images->img->instances[0].y + object_length - 4 >= images->wall->instances[wall_index].y &&			// predicting the future by x amount of px to detect a wall
	images->img->instances[0].y - 4 <= images->wall->instances[wall_index].y + object_length &&
	images->img->instances[0].x <= images->wall->instances[wall_index].x + object_length &&
	images->img->instances[0].x + object_length >= images->wall->instances[wall_index].x
	)
	{
		return (1);
	}
	return (0);
}

int wall_in_s_direction(int wall_index)
{
	if (images->img->instances[0].y + object_length + 4 >= images->wall->instances[wall_index].y &&
	images->img->instances[0].y + 4 <= images->wall->instances[wall_index].y + object_length &&
	images->img->instances[0].x <= images->wall->instances[wall_index].x + object_length &&
	images->img->instances[0].x + object_length >= images->wall->instances[wall_index].x
	)
	{
		return (1);
	}
	return (0);
}

int wall_in_a_direction(int wall_index)
{
	if (images->img->instances[0].y + object_length >= images->wall->instances[wall_index].y &&
	images->img->instances[0].y <= images->wall->instances[wall_index].y + object_length &&
	images->img->instances[0].x - 4 <= images->wall->instances[wall_index].x + object_length &&
	images->img->instances[0].x + object_length - 4 >= images->wall->instances[wall_index].x
	)
	{
		return (1);
	}
	return (0);
}

int wall_in_d_direction(int wall_index)
{
	if (images->img->instances[0].y + object_length >= images->wall->instances[wall_index].y &&
	images->img->instances[0].y <= images->wall->instances[wall_index].y + object_length &&
	images->img->instances[0].x + 4 <= images->wall->instances[wall_index].x + object_length &&
	images->img->instances[0].x + object_length + 4 >= images->wall->instances[wall_index].x
	)
	{
		return (1);
	}
	return (0);
}

int	picked_collectible(int egg_index)
{
	if (images->img->instances[0].y + object_length >= images->collectible->instances[egg_index].y &&
	images->img->instances[0].y <= images->collectible->instances[egg_index].y + object_length &&
	images->img->instances[0].x <= images->collectible->instances[egg_index].x + object_length &&
	images->img->instances[0].x + object_length >= images->collectible->instances[egg_index].x
	)
	{
		return (1);
	}
	return (0);
}

int	player_can_exit_game(int egg_index)
{
	if (images->img->instances[0].y + object_length >= images->escape->instances[egg_index].y &&
	images->img->instances[0].y <= images->escape->instances[egg_index].y + object_length &&
	images->img->instances[0].x <= images->escape->instances[egg_index].x + object_length &&
	images->img->instances[0].x + object_length >= images->escape->instances[egg_index].x
	)
	{
		return (1);
	}
	return (0);
}

int	picked_collectibles_count(int collectibles_count, int grabbed_eggs)
{
	int k = 0;
	while (k  < collectibles_count)
	{
		if (images->collectible->instances[k].enabled == 0)
			grabbed_eggs += 1;
		k++;
	}
	return grabbed_eggs;
}

int	player_on_exit_tile(int egg_index)
{
	if (player_can_exit_game(egg_index))
	{
		// printf("Well done, you saved the dinosaurs!");
		return 1;
	}
	return 0;
}

int	player_on_collectible_tile(int egg_index)
{
	if (picked_collectible(egg_index))
	{
		printf("collectible - (%d, %d)\n", images->collectible->instances[egg_index].x, images->collectible->instances[egg_index].y);
		// printf("%d, %d", egg_index, i + j);

		images->collectible->instances[egg_index].enabled = 0;
		if (images->collectible->instances[egg_index].enabled == 0)
		{
			printf("Number of collectibles on screen: %d\n", images->collectible->count);
			return 1 ;
		}
	}
	return 0;
}


int	player_wins(int grabbed_eggs, int egg_index, int i, int j)
{
	if (grabbed_eggs == images->collectible->count)
	{
		if(arr[i][j] == 'E')
			if (player_on_exit_tile(egg_index))
				return 1; //break ;
	}
	return 0;
}

int check_for_w_move(int grabbed_eggs, int egg_index, int wall_index)
{
	params_t params;

	params.i = -1;
	while (arr[++params.i] != 0)
	{
		params.j = -1;
		while (arr[params.i][++params.j] != '\0')
		{
			if (player_wins(grabbed_eggs, egg_index, params.i, params.j))
				break ;
			if (arr[params.i][params.j] == 'C')
			{
				if (player_on_collectible_tile(egg_index))
					break ;
				egg_index += 1;
			}
			if (arr[params.i][params.j] == '1')
			{
				if (wall_in_w_direction(wall_index))
					return 0;
				wall_index += 1;
			}
		}
	}
	return (1);
}


int check_for_s_move(int grabbed_eggs, int egg_index, int wall_index)
{
	params_t params;

	params.i = -1;
	while (arr[++params.i] != 0)
	{
		params.j = -1;
		while (arr[params.i][++params.j] != '\0')
		{
			if (player_wins(grabbed_eggs, egg_index, params.i, params.j))
				break ;
			if (arr[params.i][params.j] == 'C')
			{
				if (player_on_collectible_tile(egg_index))
					break ;
				egg_index += 1;
			}
			if (arr[params.i][params.j] == '1')
			{
				if (wall_in_s_direction(wall_index))
					return 0;
				wall_index += 1;
			}
		}
	}
	return (1);
}

int check_for_a_move(int grabbed_eggs, int egg_index, int wall_index)
{
	params_t params;

	params.i = -1;
	while (arr[++params.i] != 0)
	{
		params.j = -1;
		while (arr[params.i][++params.j] != '\0')
		{
			if (player_wins(grabbed_eggs, egg_index, params.i, params.j))
				break ;
			if (arr[params.i][params.j] == 'C')
			{
				if (player_on_collectible_tile(egg_index))
					break ;
				egg_index += 1;
			}
			if (arr[params.i][params.j] == '1')
			{
				if (wall_in_a_direction(wall_index))
					return 0;
				wall_index += 1;
			}
		}
	}
	return (1);
}

int check_for_d_move(int grabbed_eggs, int egg_index, int wall_index)
{
	params_t params;

	params.i = -1;
	while (arr[++params.i] != 0)
	{
		params.j = -1;
		while (arr[params.i][++params.j] != '\0')
		{
			if (player_wins(grabbed_eggs, egg_index, params.i, params.j))
				break ;
			if (arr[params.i][params.j] == 'C')
			{
				if (player_on_collectible_tile(egg_index))
					break ;
				egg_index += 1;
			}
			if (arr[params.i][params.j] == '1')
			{
				if (wall_in_d_direction(wall_index))
					return 0;
				wall_index += 1;
			}
		}
	}
	return (1);
}

void	w_key_pressed(int grabbed_eggs, int egg_index, int wall_index)
{
	int move;

	grabbed_eggs += picked_collectibles_count(images->collectible->count, grabbed_eggs);
	move = check_for_w_move(grabbed_eggs, egg_index, wall_index);
	if (move && movement_count++)
		images->img->instances[0].y -= 4;
	// if (movement_count %48 == 0)
		printf("moves: %d\n", movement_count /* / 48 */);
}

void	s_key_pressed(int grabbed_eggs, int egg_index, int wall_index)
{
	int move;

	grabbed_eggs += picked_collectibles_count(images->collectible->count, grabbed_eggs);
	move = check_for_s_move(grabbed_eggs,  egg_index, wall_index);
	if (move && movement_count++)
		images->img->instances[0].y += 4;
	// if (movement_count %48 == 0)
		printf("moves: %d\n", movement_count /* / 48 */);
}

void	a_key_pressed(int grabbed_eggs, int egg_index, int wall_index)
{
	int move;

	grabbed_eggs += picked_collectibles_count(images->collectible->count, grabbed_eggs);
	move = check_for_a_move(grabbed_eggs,  egg_index, wall_index);
	if (move && movement_count++)
		images->img->instances[0].x -= 4;
	// if (movement_count %48 == 0)
		printf("moves: %d\n", movement_count /* / 48 */);
}

void	d_key_pressed(int grabbed_eggs, int egg_index, int wall_index)
{
	int move;

	grabbed_eggs += picked_collectibles_count(images->collectible->count, grabbed_eggs);
	move = check_for_d_move(grabbed_eggs,  egg_index, wall_index);
	if (move && movement_count++)
		images->img->instances[0].x += 4;
	// if (movement_count %48 == 0)
		printf("moves: %d\n", movement_count /* / 48 */);
}

void	hook(void *key)
{
	mlx_t	*mlx;
	int		egg_index;
	int		wall_index;
	int		grabbed_eggs;

	mlx = key;
	egg_index = 0;
	wall_index = 0;
	grabbed_eggs = 0;

	if (mlx_is_key_down(key, MLX_KEY_ESCAPE))
		mlx_close_window(key);
	else if (mlx_is_key_down(key, MLX_KEY_UP) || mlx_is_key_down(key, MLX_KEY_W))
		w_key_pressed(grabbed_eggs,  egg_index, wall_index);
	else if (mlx_is_key_down(key, MLX_KEY_DOWN) || mlx_is_key_down(key, MLX_KEY_S))
		s_key_pressed(grabbed_eggs,  egg_index, wall_index);
	else if (mlx_is_key_down(key, MLX_KEY_LEFT) || mlx_is_key_down(key, MLX_KEY_A))
		a_key_pressed(grabbed_eggs,  egg_index, wall_index);
	else if (mlx_is_key_down(key, MLX_KEY_RIGHT) || mlx_is_key_down(key, MLX_KEY_D))
		d_key_pressed(grabbed_eggs,  egg_index, wall_index);
}

static void error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}



void	create_textures(texture_t *val)
{
	val->wall_texture =  mlx_load_png("./img/wall1.png");
	val->texture = mlx_load_png("./img/dion.png");
	val->bg_texture = mlx_load_png("./img/map.png");
	val->collectible_texture = mlx_load_png("./img/egg1.png");
	val->escape_texture = mlx_load_png("./img/escape.png");

	if (!val->wall_texture || !val->texture || !val->bg_texture || !val->collectible_texture || !val->escape_texture)
		error();
}

void	create_images(game_image_t* images, mlx_t *mlx, texture_t *val)
{
	images->bg = mlx_texture_to_image(mlx, val->bg_texture);
	images->img = mlx_texture_to_image(mlx, val->texture);
	images->wall = mlx_texture_to_image(mlx, val->wall_texture);
	images->collectible = mlx_texture_to_image(mlx, val->collectible_texture);
	images->escape = mlx_texture_to_image(mlx, val->escape_texture);

	if (!images->bg || !images->img || !images->wall || !images->collectible || !images->escape)
		error();
}

void	check_line(mlx_t *mlx, map_parsing_t *p_map)
{
	while (p_map->line[p_map->j] != '\0')
	{
		if (p_map->line[p_map->j] != '1' && p_map->line[p_map->j] != 'P' && p_map->line[p_map->j] != 'E' && p_map->line[p_map->j] != 'C' && p_map->line[p_map->j] != '0' && p_map->line[p_map->j] != '\n')
		{
			printf("%c, %d\n", p_map->line[p_map->j], p_map->j);
			exit(1);
		}
		if (p_map->line[p_map->j] == '1')
			mlx_image_to_window(mlx, images->wall, 48 * p_map->x, 48 * p_map->y);
		if (p_map->line[p_map->j] == 'P')
		{
			player_location_x = 48 * p_map->x;
			player_location_y = 48 * p_map->y;
			p_map->player_count++;
		}
		if (p_map->line[p_map->j] == 'C')
		{
			mlx_image_to_window(mlx, images->collectible, 48 * p_map->x, 48 * p_map->y);
			p_map->collectible_count += 1;
		}
		if (p_map->line[p_map->j] == 'E')
		{
			mlx_image_to_window(mlx, images->escape, 48 * p_map->x , 48 * p_map->y);
			p_map->escape_count++;
		}
		p_map->x++;
		p_map->j++;
	}
}

void	parse_map(mlx_t *mlx)
{
	map_parsing_t	map;
	map_parsing_t	*p_map;

	p_map = &map;
	map.fd = open("./maps/map01.ber", O_RDONLY);
	while (1)
	{
		map.j = 0;
		map.x = 0;
		map.line = get_next_line(map.fd);
		if (!map.line)
			break ;
		arr[map.y] = map.line;
		check_line(mlx, p_map);

		line_count += 1;
		map.y++;
	}
	if (map.collectible_count < 1 || map.player_count != 1 || map.escape_count != 1)
	{
		printf("|only one player allowed| -OR- |only one exit allowed|  -OR- |No collectibles on map|");
		exit(0);
	}
}

void	check_map_dimensions()
{
	int i;

	i = 0;
	while (arr[i] != 0)
	{
		int j = 0;
		while (arr[i][j] != '\0' && arr[i][j] != '\n')
		{
			if (i == 0 && arr[i][j + 1] == '\n')
				map_width1 = j;
			if (i > 0 && (arr[i][j + 1] == '\n' || arr[i][j + 1] == '\0'))
				map_width2 = j;
			if (map_width1 && map_width2)
			{
				if (map_width1 != map_width2)
				{
					printf("%d, %d:\n", map_width1, map_width2);
					printf("Not a valid map\n");
					exit(1);
				}
			}
			j++;
		}
		i++;
	}
}

	// checking map has walls on all sides

void	is_top_wall_valid()
{
	int i = 0;
	while (arr[0][i] != '\0' && arr[0][i] != '\n')
	{
		if (arr[0][i] != '1')
		{
			printf("Top Outer wall is not valid\n");
			exit(1);
		}
		i++;
	}
}

void	is_bottom_wall_valid()
{
	int i;

	i = 0;
	last_line = line_count - 1;

	while (arr[last_line][i] != '\0' && arr[last_line][i] != '\n')
	{
		if (arr[last_line][i] != '1')
		{
			printf("bottom Outer wall is not valid\n");
			exit(1);
		}
		i++;
	}
}

void	is_left_wall_valid()
{
	int i;

	i = 0;
	while (i < line_count)
	{
		if (arr[i][0] != '1')
		{
			printf("Left Outer wall is not valid\n");
			exit(1);
		}
		i++;
	}
}

void	is_right_wall_valid()
{
	int i;

	i = 0;
	while (i < line_count)
	{
		if (arr[i][map_width1] != '1')
		{
			printf("Right outer wall is not valid\n");
			exit(1);
		}
		i++;
	}
}

void	check_walls()
{
	is_top_wall_valid();
	is_bottom_wall_valid();
	is_left_wall_valid();
	is_right_wall_valid();
}

int32_t	main(void)
{
	mlx_t* mlx;
	texture_t *val;

	mlx = mlx_init(WIDTH, HEIGHT, "Test", true);
	val = (texture_t*) malloc(sizeof(texture_t));
	images = (game_image_t*) malloc(sizeof(game_image_t));
	if (!images || !val || !mlx)
		error();
	create_textures(val);
	create_images(images, mlx, val);

	if (mlx_image_to_window(mlx, images->bg, 0, 0) < 0)
		error();
	parse_map(mlx);
	check_map_dimensions();
	if (line_count == map_width1 + 1)
	{
		printf("Map is a square, it should be rectangular\n");
		exit(1);
	}
	check_walls();
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_image_to_window(mlx, images->img, player_location_x, player_location_y);
	mlx_loop(mlx);
	return (EXIT_SUCCESS);
}
