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
	int		move;
}			params_t;

// variables to create an image
mlx_image_t* img;
mlx_image_t* wall;
mlx_image_t *collectible;
mlx_image_t *escape;
mlx_image_t *bg;


// variables to create map data and work with the map (coordinates)
int player_location_x;
int player_location_y;
char *arr[10000000];
int movement_count = 0;
// movement_count = 0;
// int grabbed_eggs;

int object_length = 42;

int	wall_in_w_direction(int wall_index)
{
	if (img->instances[0].y + object_length - 4 >= wall->instances[wall_index].y &&			// predicting the future by x amount of px to detect a wall
	img->instances[0].y - 4 <= wall->instances[wall_index].y + object_length &&
	img->instances[0].x <= wall->instances[wall_index].x + object_length &&
	img->instances[0].x + object_length >= wall->instances[wall_index].x
	)
	{
		return (1);
	}
	return (0);
}

int wall_in_s_direction(int wall_index)
{
	if (img->instances[0].y + object_length + 4 >= wall->instances[wall_index].y &&
	img->instances[0].y + 4 <= wall->instances[wall_index].y + object_length &&
	img->instances[0].x <= wall->instances[wall_index].x + object_length &&
	img->instances[0].x + object_length >= wall->instances[wall_index].x
	)
	{
		return (1);
	}
	return (0);
}

int wall_in_a_direction(int wall_index)
{
	if (img->instances[0].y + object_length >= wall->instances[wall_index].y &&
	img->instances[0].y <= wall->instances[wall_index].y + object_length &&
	img->instances[0].x - 4 <= wall->instances[wall_index].x + object_length &&
	img->instances[0].x + object_length - 4 >= wall->instances[wall_index].x
	)
	{
		return (1);
	}
	return (0);
}

int wall_in_d_direction(int wall_index)
{
	if (img->instances[0].y + object_length >= wall->instances[wall_index].y &&
	img->instances[0].y <= wall->instances[wall_index].y + object_length &&
	img->instances[0].x + 4 <= wall->instances[wall_index].x + object_length &&
	img->instances[0].x + object_length + 4 >= wall->instances[wall_index].x
	)
	{
		return (1);
	}
	return (0);
}

int	picked_collectible(int egg_index)
{
	if (img->instances[0].y + object_length >= collectible->instances[egg_index].y &&
	img->instances[0].y <= collectible->instances[egg_index].y + object_length &&
	img->instances[0].x <= collectible->instances[egg_index].x + object_length &&
	img->instances[0].x + object_length >= collectible->instances[egg_index].x
	)
	{
		return (1);
	}
	return (0);
}

int	player_can_exit_game(int egg_index)
{
	if (img->instances[0].y + object_length >= escape->instances[egg_index].y &&
	img->instances[0].y <= escape->instances[egg_index].y + object_length &&
	img->instances[0].x <= escape->instances[egg_index].x + object_length &&
	img->instances[0].x + object_length >= escape->instances[egg_index].x
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
		if (collectible->instances[k].enabled == 0)
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
		printf("collectible - (%d, %d)\n", collectible->instances[egg_index].x, collectible->instances[egg_index].y);
		// printf("%d, %d", egg_index, i + j);

		collectible->instances[egg_index].enabled = 0;
		if (collectible->instances[egg_index].enabled == 0)
		{
			printf("Number of collectibles on screen: %d\n", collectible->count);
			return 1 ;
		}
	}
	return 0;
}


int	player_wins(int grabbed_eggs, int egg_index, int i, int j)
{
	if (grabbed_eggs == collectible->count)
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
	return (params.move + 1);
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
	return (params.move + 1);
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
	return (params.move + 1);
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
	return (params.move + 1);
}

void	w_key_pressed(int grabbed_eggs, int egg_index, int wall_index)
{
	int move;

	grabbed_eggs += picked_collectibles_count(collectible->count, grabbed_eggs);
	move = check_for_w_move(grabbed_eggs,  egg_index, wall_index);
	if (move && movement_count++)
		img->instances[0].y -= 4;
	// if (movement_count %48 == 0)
		printf("moves: %d\n", movement_count /* / 48 */);
}

void	s_key_pressed(int grabbed_eggs, int egg_index, int wall_index)
{
	int move;

	grabbed_eggs += picked_collectibles_count(collectible->count, grabbed_eggs);
	move = check_for_s_move(grabbed_eggs,  egg_index, wall_index);
	if (move && movement_count++)
		img->instances[0].y += 4;
	// if (movement_count %48 == 0)
		printf("moves: %d\n", movement_count /* / 48 */);
}

void	a_key_pressed(int grabbed_eggs, int egg_index, int wall_index)
{
	int move;

	grabbed_eggs += picked_collectibles_count(collectible->count, grabbed_eggs);
	move = check_for_a_move(grabbed_eggs,  egg_index, wall_index);
	if (move && movement_count++)
		img->instances[0].x -= 4;
	// if (movement_count %48 == 0)
		printf("moves: %d\n", movement_count /* / 48 */);
}

void	d_key_pressed(int grabbed_eggs, int egg_index, int wall_index)
{
	int move;

	grabbed_eggs += picked_collectibles_count(collectible->count, grabbed_eggs);
	move = check_for_d_move(grabbed_eggs,  egg_index, wall_index);
	if (move && movement_count++)
		img->instances[0].x += 4;
	// if (movement_count %48 == 0)
		printf("moves: %d\n", movement_count /* / 48 */);
}

void	hook(void *key)
{
	mlx_t	*mlx;
	mlx = key;

	// int object_length = 42;
	int egg_index;
	egg_index = 0;
	int wall_index;
	wall_index = 0;
	int grabbed_eggs = 0;

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

int32_t	main(void)
{
	// Start mlx
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "Test", true);
	// mlx = mlx_init(WIDTH, HEIGHT, "Test", true);
	if (!mlx)
        error();

	// Try to load the file
	mlx_texture_t* wall_texture = mlx_load_png("./img/wall1.png");
	mlx_texture_t* texture = mlx_load_png("./img/dion.png");
	mlx_texture_t* bg_texture = mlx_load_png("./img/map.png");
	mlx_texture_t* collectible_texture = mlx_load_png("./img/egg1.png");
	mlx_texture_t* escape_texture = mlx_load_png("./img/escape.png");



	if (!texture)
		error();

	// Convert texture to a displayable image
	/* mlx_image_t* */ bg = mlx_texture_to_image(mlx, bg_texture);
	img = mlx_texture_to_image(mlx, texture);
	/*mlx_image_t*/ wall = mlx_texture_to_image(mlx, wall_texture);
	/* mlx_image_t */ collectible = mlx_texture_to_image(mlx, collectible_texture);
	/* mlx_image_t */ escape = mlx_texture_to_image(mlx, escape_texture);




	if (!img)
        error();

	// Display the image

	if (mlx_image_to_window(mlx, bg, 0, 0) < 0)
		error();

	// mlx_image_to_window(mlx, wall, 0, 0);
	// mlx_image_to_window(mlx, wall, 48, 0);
	// mlx_image_to_window(mlx, wall, 96, 0);
	// mlx_image_to_window(mlx, wall, 144, 0);
	// mlx_image_to_window(mlx, wall, 192, 0);
	// mlx_image_to_window(mlx, wall, 0, 48);
	// mlx_image_to_window(mlx, wall, 0, 96);
	// mlx_image_to_window(mlx, wall, 0,144);
	// mlx_image_to_window(mlx, wall, 0,192);
	// mlx_image_to_window(mlx, wall, 48, 192);
	// mlx_image_to_window(mlx, wall, 96, 192);
	// mlx_image_to_window(mlx, wall, 144, 192);

	// test code to render map to screen
	int x;
	int y = 0;
	// int i = 0;
	int j;
	int fd = open("./maps/map01.ber", O_RDONLY);
	// int check_line = 1;
	int line_count = 0;
	int player_count = 0;
	int escape_count = 0;
	int collectible_count = 0;
	// int player_location_x;
	// int player_location_y;
	// char *arr[1000000];
	while (1)
	{
		char *line = get_next_line(fd);
		if (!line)
		{
			// check_line = 0;
			break ;
		}
		j = 0;
		x = 0;
		arr[y] = line;
		while (line[j] != '\0')
		{
			// printf("%c", line[j]);
			if (line[j] != '1' && line[j] != 'P' && line[j] != 'E' && line[j] != 'C' && line[j] != '0' && line[j] != '\n')
			{
				printf("%c, %d\n", line[j], j);
				// perror("Error\n");
				exit(1);
			}
			if (line[j] == '1')
				mlx_image_to_window(mlx, wall, 48 * x, 48 * y);
			if (line[j] == 'P')
			{
				player_location_x = 48 * x;
				player_location_y = 48 * y;
				player_count++;
			}
			if (line[j] == 'C')
			{
				mlx_image_to_window(mlx, collectible, 48 * x, 48 * y);
				collectible_count += 1;
			}
			if (line[j] == 'E')
			{
				mlx_image_to_window(mlx, escape, 48 * x , 48 * y);
				escape_count++;
			}
			x++;
			j++;
		}
		line_count += 1;
		y++;
	}
	if (collectible_count < 1 || player_count != 1 || escape_count != 1)
	{
		printf("|only one player allowed| -OR- |only one exit allowed|  -OR- |No collectibles on map|");
		exit(0);
	}

	// checking validity of map
	int i = 0;
	int map_width1 = 0;
	int map_width2 = 0;
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
	if (line_count == map_width1 + 1)
	{
		printf("Map is a square, it should be rectangular\n");
		exit(1);
	}

	// checking map has walls on all sides
	//top
	int last_line = line_count - 1;
	i = 0;
	while (arr[0][i] != '\0' && arr[0][i] != '\n')
	{
		if (arr[0][i] != '1')
		{
			printf("Top Outer wall is not valid\n");
			exit(1);
		}
		i++;
	}

	// bottom
	i = 0;
	while (arr[last_line][i] != '\0' && arr[last_line][i] != '\n')
	{
		if (arr[last_line][i] != '1')
		{
			printf("bottom Outer wall is not valid\n");
			exit(1);
		}
		i++;
	}

	// left
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

	// right
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

	printf("number of rows - %d\n", line_count);

	printf("Number of collectibles on screen: %d\n", collectible->count);


	mlx_loop_hook(mlx, &hook, mlx);

	mlx_image_to_window(mlx, img, player_location_x, player_location_y);


	mlx_loop(mlx);

	// Optional, terminate will clean up any left overs, this is just to demonstrate.
	mlx_delete_image(mlx, img);
	mlx_delete_texture(texture);
	mlx_terminate(mlx);

	return (EXIT_SUCCESS);
}






// #include "MLX42/include/MLX42/MLX42.h"
// #include <stdlib.h>
// #include <stdio.h>
// #include <unistd.h>
// #include <memory.h>
// #define WIDTH 256
// #define HEIGHT 256

// mlx_image_t	*g_img;

// void	hook(void *param)
// {
// 	mlx_t	*mlx;

// 	mlx = param;
// 	if (mlx_is_key_down(param, MLX_KEY_ESCAPE))
// 		mlx_close_window(param);
// 	if (mlx_is_key_down(param, MLX_KEY_UP))
// 		g_img->instances[0].y -= 5;
// 	if (mlx_is_key_down(param, MLX_KEY_DOWN))
// 		g_img->instances[0].y += 5;
// 	if (mlx_is_key_down(param, MLX_KEY_LEFT))
// 		g_img->instances[0].x -= 5;
// 	if (mlx_is_key_down(param, MLX_KEY_RIGHT))
// 		g_img->instances[0].x += 5;
// }

// int32_t	main(void)
// {
// 	mlx_t	*mlx;

// 	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
// 	if (!mlx)
// 		exit(EXIT_FAILURE);
// 	g_img = mlx_new_image(mlx, 128, 128);
// 	memset(g_img->pixels, 255, g_img->width * g_img->height * sizeof(int));
// 	mlx_image_to_window(mlx, g_img, 0, 0);
// 	mlx_loop_hook(mlx, &hook, mlx);
// 	mlx_loop(mlx);
// 	mlx_terminate(mlx);
// 	return (EXIT_SUCCESS);
// }
