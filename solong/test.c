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


mlx_image_t* img;
mlx_image_t* wall;
mlx_image_t *collectible;
mlx_image_t *escape;

int player_location_x;
int player_location_y;
char *arr[10000000];
int movement_count = 0;
// movement_count = 0;


mlx_t* mlx;

void	hook(void *param)
{
	mlx_t	*mlx;
	mlx = param;

	int move;
	int object_length = 42;
	int egg_index;
	egg_index = 0;


	if (mlx_is_key_down(param, MLX_KEY_ESCAPE))
		mlx_close_window(param);
	else if (mlx_is_key_down(param, MLX_KEY_UP) || mlx_is_key_down(param, MLX_KEY_W))
	{
		int i = 0;
		int j;
		int wall_index;
		wall_index = 0;
		move = 1;
		int k = 0;
		int grabbed_eggs = 0;

		while (k < collectible->count)
		{
			if (collectible->instances[k].enabled == 0)
				grabbed_eggs += 1;
			k++;
		}
		while (arr[i] != 0)
		{
			j = 0;
			while (arr[i][j] != '\0')
			{
				// reading walls correctly
				if (grabbed_eggs == collectible->count)
				{
					if (arr[i][j] == 'E')
					{
						if (img->instances[0].y + object_length >= escape->instances[egg_index].y &&
						img->instances[0].y <= escape->instances[egg_index].y + object_length &&
						img->instances[0].x <= escape->instances[egg_index].x + object_length &&
						img->instances[0].x + object_length >= escape->instances[egg_index].x
						)
						{
							printf("Well done, you saved the dinosaurs!");
							break ;
						}
					}
				}
				if (arr[i][j] == 'C')
				{
					if (img->instances[0].y + object_length >= collectible->instances[egg_index].y &&
						img->instances[0].y <= collectible->instances[egg_index].y + object_length &&
						img->instances[0].x <= collectible->instances[egg_index].x + object_length &&
						img->instances[0].x + object_length >= collectible->instances[egg_index].x
					)
					{
						printf("collectible - (%d, %d)\n", collectible->instances[egg_index].x, collectible->instances[egg_index].y);
						printf("%d, %d", egg_index, i + j);

						collectible->instances[egg_index].enabled = 0;
						if (collectible->instances[egg_index].enabled == 0)
						{
							printf("Number of collectibles on screen: %d\n", collectible->count);
							break ;
						}
					}
					egg_index += 1;
				}
				if (arr[i][j] == '1')
				{
					if (img->instances[0].y + object_length - 3 >= wall->instances[wall_index].y &&
						img->instances[0].y - 3 <= wall->instances[wall_index].y + object_length &&
						img->instances[0].x <= wall->instances[wall_index].x + object_length &&
						img->instances[0].x + object_length >= wall->instances[wall_index].x
					)
					{
						move = 0;
						break ;
					}
					wall_index += 1;
				}
				j++;
			}
			i++;
		}
		if (move)
		{
			img->instances[0].y -= 3;
			movement_count += 1;
		}
		printf("player (A key) - (%i, %i)\n", img->instances[0].x , img->instances[0].y);
		printf("Number of moves made: %d\n", movement_count);
	}
	else if (mlx_is_key_down(param, MLX_KEY_DOWN) || mlx_is_key_down(param, MLX_KEY_S))
	{
		int i = 0;
		int j;
		int wall_index;
		wall_index = 0;
		move = 1;
		int k = 0;
		int grabbed_eggs = 0;
		while (k < collectible->count)
		{
			if (collectible->instances[k].enabled == 0)
				grabbed_eggs+= 1;
			k++;
		}
		while (arr[i] != 0)
		{
			j = 0;
			while (arr[i][j] != '\0')
			{
				if (grabbed_eggs == collectible->count)
				{
					if (arr[i][j] == 'E')
					{
						if (img->instances[0].y + object_length >= escape->instances[egg_index].y &&
						img->instances[0].y <= escape->instances[egg_index].y + object_length &&
						img->instances[0].x <= escape->instances[egg_index].x + object_length &&
						img->instances[0].x + object_length >= escape->instances[egg_index].x
						)
						{
							printf("Well done, you saved the dinosaurs!");
							break ;
						}
					}
				}
				if (arr[i][j] == 'C')
				{
					if (img->instances[0].y + object_length >= collectible->instances[egg_index].y &&
						img->instances[0].y <= collectible->instances[egg_index].y + object_length &&
						img->instances[0].x <= collectible->instances[egg_index].x + object_length &&
						img->instances[0].x + object_length >= collectible->instances[egg_index].x
					)
					{
						printf("collectible - (%d, %d)\n", collectible->instances[egg_index].x, collectible->instances[egg_index].y);
						printf("%d, %d", egg_index, i + j);

						collectible->instances[egg_index].enabled = 0;
						if (collectible->instances[egg_index].enabled == 0)
						{
							printf("Number of collectibles on screen: %d\n", collectible->count);
							break ;
						}
					}
					egg_index += 1;
				}

				if (arr[i][j] == '1')
				{
					if (img->instances[0].y + object_length + 3 >= wall->instances[wall_index].y &&  // predicting the future by 1px to detect a wall
						img->instances[0].y + 3 <= wall->instances[wall_index].y + object_length &&
						img->instances[0].x <= wall->instances[wall_index].x + object_length &&
						img->instances[0].x + object_length >= wall->instances[wall_index].x
					)     
					{
						move = 0;
						break ;
					}
					wall_index += 1;
				}
				j++;
			}
			i++;
		}
		if (move)
		{
			img->instances[0].y += 3;
			movement_count += 1;
		}
		printf("player (S key) - (%i, %i)\n", img->instances[0].x , img->instances[0].y);
		printf("Number of moves made: %d\n", movement_count);
	}
	else if (mlx_is_key_down(param, MLX_KEY_LEFT) || mlx_is_key_down(param, MLX_KEY_A))
	{
		int i = 0;
		int j;
		int wall_index;
		wall_index = 0;
		move = 1;
		int k = 0;
		int grabbed_eggs = 0;

		while (k < collectible->count)
		{
			printf("collectible state - %d\n", collectible->instances[k].enabled);
			if (collectible->instances[k].enabled == 0)
				grabbed_eggs+= 1;
			k++;
		}
		printf("Number of eggs collected - %d\n", grabbed_eggs);
		while (arr[i] != 0)
		{
			j = 0;
			while (arr[i][j] != '\0')
			{
				if (grabbed_eggs == collectible->count)
				{
					// printf("*********grabbed all eggs\n");
					if (arr[i][j] == 'E')
					{
						if (img->instances[0].y + object_length >= escape->instances[egg_index].y &&
						img->instances[0].y <= escape->instances[egg_index].y + object_length &&
						img->instances[0].x <= escape->instances[egg_index].x + object_length &&
						img->instances[0].x + object_length >= escape->instances[egg_index].x
						)
						{
							printf("Well done, you saved the dinosaurs!");
							break ;
						}
					}
				}
				if (arr[i][j] == 'C')
				{
					if (img->instances[0].y + object_length >= collectible->instances[egg_index].y &&
						img->instances[0].y <= collectible->instances[egg_index].y + object_length &&
						img->instances[0].x <= collectible->instances[egg_index].x + object_length &&
						img->instances[0].x + object_length >= collectible->instances[egg_index].x
					)
					{
						printf("collectible - (%d, %d)\n", collectible->instances[egg_index].x, collectible->instances[egg_index].y);
						printf("%d, %d", egg_index, i + j);
						collectible->instances[egg_index].enabled = 0;
						if (collectible->instances[egg_index].enabled == 0)
						{
							printf("Number of collectibles on screen: %d\n", collectible->count);
							break ;
						}
					}
					egg_index += 1;
				}
				if (arr[i][j] == '1')
				{
					if (img->instances[0].y + object_length >= wall->instances[wall_index].y &&
						img->instances[0].y <= wall->instances[wall_index].y + object_length &&
						img->instances[0].x - 3 <= wall->instances[wall_index].x + object_length &&
						img->instances[0].x + object_length - 3 >= wall->instances[wall_index].x
					)     
					{
						move = 0;
						break ;
					}
					wall_index += 1;
				}
				j++;
			}
			i++;
		}
		if (move)
		{
			img->instances[0].x -= 3;
			movement_count += 1;
		}
		printf("player (A key) - (%i, %i)\n", img->instances[0].x , img->instances[0].y);
		printf("Number of moves made: %d\n", movement_count);
	}
	else if (mlx_is_key_down(param, MLX_KEY_RIGHT) || mlx_is_key_down(param, MLX_KEY_D))
	{
		int i = 0;
		int j;
		int wall_index;
		wall_index = 0;
		move = 1;
		int k = 0;
		int grabbed_eggs = 0;

		while (k < collectible->count)
		{
			printf("collectible state - %d\n", collectible->instances[k].enabled);
			if (collectible->instances[k].enabled == 0)
				grabbed_eggs+= 1;
			k++;
		}
		printf("Number of eggs collected - %d\n", grabbed_eggs);
		while (arr[i] != 0)
		{
			j = 0;
			while (arr[i][j] != '\0')
			{
				if (grabbed_eggs == collectible->count)
				{
					if (arr[i][j] == 'E')
					{
						if (img->instances[0].y + object_length >= escape->instances[egg_index].y &&
						img->instances[0].y <= escape->instances[egg_index].y + object_length &&
						img->instances[0].x <= escape->instances[egg_index].x + object_length &&
						img->instances[0].x + object_length >= escape->instances[egg_index].x
						)
						{
							printf("Well done, you saved the dinosaurs!");
							break ;
						}
					}
				}
				if (arr[i][j] == 'C')
				{
					if (img->instances[0].y + object_length >= collectible->instances[egg_index].y &&
						img->instances[0].y <= collectible->instances[egg_index].y + object_length &&
						img->instances[0].x <= collectible->instances[egg_index].x + object_length &&
						img->instances[0].x + object_length >= collectible->instances[egg_index].x
					)
					{
						printf("collectible - (%d, %d)\n", collectible->instances[egg_index].x, collectible->instances[egg_index].y);
						printf("%d, %d", egg_index, i + j);
						collectible->instances[egg_index].enabled = 0;
						if (collectible->instances[egg_index].enabled == 0)
						{
							printf("Number of collectibles on screen: %d\n", collectible->count);
							break ;
						}
					}
					egg_index += 1;
				}
				if (arr[i][j] == '1')
				{
					if (img->instances[0].y + object_length >= wall->instances[wall_index].y &&
						img->instances[0].y <= wall->instances[wall_index].y + object_length &&
						img->instances[0].x + 3 <= wall->instances[wall_index].x + object_length &&
						img->instances[0].x + object_length + 3 >= wall->instances[wall_index].x
					)     
					{
						move = 0;
						break ;
					}
					wall_index += 1;
				}
				j++;
			}
			i++;
		}
		if (move)
		{
			img->instances[0].x += 3;
			movement_count += 1;
		}
		printf("player (D key) - (%i, %i)\n", img->instances[0].x , img->instances[0].y);
		printf("Number of moves made: %d\n", movement_count);
	}
}

static void error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

int32_t	main(void)
{
	// Start mlx
	// mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "Test", true);
	mlx = mlx_init(WIDTH, HEIGHT, "Test", true);
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
	mlx_image_t* bg = mlx_texture_to_image(mlx, bg_texture);
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
	// char *line = "1111111111\n1000000001\n1000000001\n1000000001\n1111111111";
	int fd = open("./maps/map01.ber", O_RDONLY);
	// char *line = get_next_line(fd);
	// char *line2 = get_next_line(fd);
	int check_line = 1;
	int line_count = 0;
	int player_count = 0;
	int escape_count = 0;
	int collectible_count = 0;
	// int player_location_x;
	// int player_location_y;
	// char *arr[1000000];
	while (check_line)
	{
		char *line = get_next_line(fd);
		if (!line)
		{
			check_line = 0;
			break ;
		}
		int j = 0;
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
				if (player_count > 1)
				{
					printf("Duplicate: %c, %d\n", line[j], j);
					exit(1);
				}
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
				if (escape_count > 1)
				{
					printf("Duplicate: %c, %d\n", line[j], j);
					exit(1);
				}
			}
			x++;
			j++;
		}
		line_count += 1;
		y++;
	}
	if (collectible_count < 1)
	{
		printf("No collectibles on map");
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