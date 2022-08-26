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
#include "../libft/libft.h"

#define WIDTH 960
#define HEIGHT 288
#define OBJ_LENGTH 42


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
	mlx_texture_t* wall_texture;
	mlx_texture_t* player_texture;
	mlx_texture_t* bg_texture; 
	mlx_texture_t* collectible_texture;
	mlx_texture_t* escape_texture;
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
	char	*line;
}			t_map_parsing;


// variables to create map data and work with the map (coordinates)
typedef struct s_map_data
{
	char	*arr[10000000];
	int 	player_location_x;
	int		player_location_y;
	int		movement_count;
	int		line_count;
	int		map_width1;
	int		map_width2;
	int 	last_line;
}			t_map_data;


t_game_image	*g_images;
t_map_data		*g_m_data;
char			*ber_file;

int	wall_in_w_direction(int wall_index)
{
	if (g_images->player->instances[0].y + OBJ_LENGTH - 4 >= g_images->wall->instances[wall_index].y &&			// predicting the future by x amount of px to detect a wall
	g_images->player->instances[0].y - 4 <= g_images->wall->instances[wall_index].y + OBJ_LENGTH &&
	g_images->player->instances[0].x <= g_images->wall->instances[wall_index].x + OBJ_LENGTH &&
	g_images->player->instances[0].x + OBJ_LENGTH >= g_images->wall->instances[wall_index].x
	)
	{
		return (1);
	}
	return (0);
}

int wall_in_s_direction(int wall_index)
{
	if (g_images->player->instances[0].y + OBJ_LENGTH + 4 >= g_images->wall->instances[wall_index].y &&
	g_images->player->instances[0].y + 4 <= g_images->wall->instances[wall_index].y + OBJ_LENGTH &&
	g_images->player->instances[0].x <= g_images->wall->instances[wall_index].x + OBJ_LENGTH &&
	g_images->player->instances[0].x + OBJ_LENGTH >= g_images->wall->instances[wall_index].x
	)
	{
		return (1);
	}
	return (0);
}

int wall_in_a_direction(int wall_index)
{
	if (g_images->player->instances[0].y + OBJ_LENGTH >= g_images->wall->instances[wall_index].y &&
	g_images->player->instances[0].y <= g_images->wall->instances[wall_index].y + OBJ_LENGTH &&
	g_images->player->instances[0].x - 4 <= g_images->wall->instances[wall_index].x + OBJ_LENGTH &&
	g_images->player->instances[0].x + OBJ_LENGTH - 4 >= g_images->wall->instances[wall_index].x
	)
	{
		return (1);
	}
	return (0);
}

int wall_in_d_direction(int wall_index)
{
	if (g_images->player->instances[0].y + OBJ_LENGTH >= g_images->wall->instances[wall_index].y &&
	g_images->player->instances[0].y <= g_images->wall->instances[wall_index].y + OBJ_LENGTH &&
	g_images->player->instances[0].x + 4 <= g_images->wall->instances[wall_index].x + OBJ_LENGTH &&
	g_images->player->instances[0].x + OBJ_LENGTH + 4 >= g_images->wall->instances[wall_index].x
	)
	{
		return (1);
	}
	return (0);
}

int	picked_collectible(int egg_index)
{
	if (g_images->player->instances[0].y + OBJ_LENGTH >= g_images->collectible->instances[egg_index].y &&
	g_images->player->instances[0].y <= g_images->collectible->instances[egg_index].y + OBJ_LENGTH &&
	g_images->player->instances[0].x <= g_images->collectible->instances[egg_index].x + OBJ_LENGTH &&
	g_images->player->instances[0].x + OBJ_LENGTH >= g_images->collectible->instances[egg_index].x
	)
	{
		return (1);
	}
	return (0);
}

int	player_can_exit_game(int egg_index)
{
	if (g_images->player->instances[0].y + OBJ_LENGTH >= g_images->escape->instances[egg_index].y &&
	g_images->player->instances[0].y <= g_images->escape->instances[egg_index].y + OBJ_LENGTH &&
	g_images->player->instances[0].x <= g_images->escape->instances[egg_index].x + OBJ_LENGTH &&
	g_images->player->instances[0].x + OBJ_LENGTH >= g_images->escape->instances[egg_index].x
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
		if (g_images->collectible->instances[k].enabled == 0)
			grabbed_eggs += 1;
		k++;
	}
	return grabbed_eggs;
}

int	player_on_exit_tile(int egg_index)
{
	if (player_can_exit_game(egg_index))
		return 1;
	return 0;
}

int	player_on_collectible_tile(int egg_index)
{
	if (picked_collectible(egg_index))
	{
		printf("collectible - (%d, %d)\n", g_images->collectible->instances[egg_index].x, g_images->collectible->instances[egg_index].y);
		g_images->collectible->instances[egg_index].enabled = 0;
	}
	return 0;
}


int	player_wins(int grabbed_eggs, int egg_index, int i, int j)
{
	if (grabbed_eggs == g_images->collectible->count)
	{
		if(g_m_data->arr[i][j] == 'E')
			if (player_on_exit_tile(egg_index))
				return 1;
	}
	return 0;
}

int check_for_w_move(int grabbed_eggs, int egg_index, int wall_index)
{
	t_params params;

	params.i = -1;
	while (g_m_data->arr[++params.i] != 0)
	{
		params.j = -1;
		while (g_m_data->arr[params.i][++params.j] != '\0')
		{
			if (player_wins(grabbed_eggs, egg_index, params.i, params.j))
			{
				printf("You saved the \"Dinosaurs\"\n");
				exit(1);
			}
			if (g_m_data->arr[params.i][params.j] == 'C')
			{
				if (player_on_collectible_tile(egg_index))
					break ;
				egg_index += 1;
			}
			if (g_m_data->arr[params.i][params.j] == '1')
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
	t_params params;

	params.i = -1;
	while (g_m_data->arr[++params.i] != 0)
	{
		params.j = -1;
		while (g_m_data->arr[params.i][++params.j] != '\0')
		{
			if (player_wins(grabbed_eggs, egg_index, params.i, params.j))
			{
				printf("You saved the \"Dinosaurs\"\n");
				exit(1);
			}
			if (g_m_data->arr[params.i][params.j] == 'C')
			{
				if (player_on_collectible_tile(egg_index))
					break ;
				egg_index += 1;
			}
			if (g_m_data->arr[params.i][params.j] == '1')
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
	t_params params;

	params.i = -1;
	while (g_m_data->arr[++params.i] != 0)
	{
		params.j = -1;
		while (g_m_data->arr[params.i][++params.j] != '\0')
		{
			if (player_wins(grabbed_eggs, egg_index, params.i, params.j))
			{
				printf("You saved the \"Dinosaurs\"\n");
				exit(1);
			}
			if (g_m_data->arr[params.i][params.j] == 'C')
			{
				if (player_on_collectible_tile(egg_index))
					break ;
				egg_index += 1;
			}
			if (g_m_data->arr[params.i][params.j] == '1')
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
	t_params params;

	params.i = -1;
	while (g_m_data->arr[++params.i] != 0)
	{
		params.j = -1;
		while (g_m_data->arr[params.i][++params.j] != '\0')
		{
			if (player_wins(grabbed_eggs, egg_index, params.i, params.j))
			{
				printf("You saved the \"Dinosaurs\"\n");
				exit(1);
			}
			if (g_m_data->arr[params.i][params.j] == 'C')
			{
				if (player_on_collectible_tile(egg_index))
					break ;
				egg_index += 1;
			}
			if (g_m_data->arr[params.i][params.j] == '1')
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

	grabbed_eggs += picked_collectibles_count(g_images->collectible->count, grabbed_eggs);
	move = check_for_w_move(grabbed_eggs, egg_index, wall_index);
	if (move && g_m_data->movement_count++)
		g_images->player->instances[0].y -= 4;
		ft_putstr_fd("moves: ", STDOUT_FILENO);
		ft_putnbr_fd(g_m_data->movement_count, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
}

void	s_key_pressed(int grabbed_eggs, int egg_index, int wall_index)
{
	int move;

	grabbed_eggs += picked_collectibles_count(g_images->collectible->count, grabbed_eggs);
	move = check_for_s_move(grabbed_eggs,  egg_index, wall_index);
	if (move && g_m_data->movement_count++)
		g_images->player->instances[0].y += 4;
		ft_putstr_fd("moves: ", STDOUT_FILENO);
		ft_putnbr_fd(g_m_data->movement_count, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
}

void	a_key_pressed(int grabbed_eggs, int egg_index, int wall_index)
{
	int move;

	grabbed_eggs += picked_collectibles_count(g_images->collectible->count, grabbed_eggs);
	move = check_for_a_move(grabbed_eggs,  egg_index, wall_index);
	if (move && g_m_data->movement_count++)
		g_images->player->instances[0].x -= 4;
		ft_putstr_fd("moves: ", STDOUT_FILENO);
		ft_putnbr_fd(g_m_data->movement_count, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
}

void	d_key_pressed(int grabbed_eggs, int egg_index, int wall_index)
{
	int move;

	grabbed_eggs += picked_collectibles_count(g_images->collectible->count, grabbed_eggs);
	move = check_for_d_move(grabbed_eggs,  egg_index, wall_index);
	if (move && g_m_data->movement_count++)
		g_images->player->instances[0].x += 4;
		ft_putstr_fd("moves: ", STDOUT_FILENO);
		ft_putnbr_fd(g_m_data->movement_count, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
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


void	create_textures(t_texture *val)
{
	val->wall_texture =  mlx_load_png("./img/wall1.png");
	val->player_texture = mlx_load_png("./img/dion.png");
	val->bg_texture = mlx_load_png("./img/map.png");
	val->collectible_texture = mlx_load_png("./img/egg1.png");
	val->escape_texture = mlx_load_png("./img/escape.png");

	if (!val->wall_texture || !val->player_texture
		|| !val->bg_texture || !val->collectible_texture 
		|| !val->escape_texture)
	{
		ft_putstr_fd("Error\nFailed to load\n", STDOUT_FILENO);
		exit(EXIT_FAILURE);
	}
}

void	create_g_images(t_game_image* g_images, mlx_t *mlx, t_texture *val)
{
	g_images->bg = mlx_texture_to_image(mlx, val->bg_texture);
	g_images->player = mlx_texture_to_image(mlx, val->player_texture);
	g_images->wall = mlx_texture_to_image(mlx, val->wall_texture);
	g_images->collectible = mlx_texture_to_image(mlx, val->collectible_texture);
	g_images->escape = mlx_texture_to_image(mlx, val->escape_texture);

	if (!g_images->bg || !g_images->player
		|| !g_images->wall || !g_images->collectible
		|| !g_images->escape)
	{
		ft_putstr_fd("Error\nFailed to load\n", STDOUT_FILENO);
		exit(EXIT_FAILURE);
	}
}

void	get_player_location(t_map_parsing *p_map)
{
		g_m_data->player_location_x = 48 * p_map->x;
		g_m_data->player_location_y = 48 * p_map->y;
		p_map->player_count++;
}

void	check_line(mlx_t *mlx, t_map_parsing *p_map)
{
	while (p_map->line[p_map->j] != '\0')
	{
		if (p_map->line[p_map->j] != '1' && p_map->line[p_map->j] != 'P'
			&& p_map->line[p_map->j] != 'E' && p_map->line[p_map->j] != 'C'
			&& p_map->line[p_map->j] != '0' && p_map->line[p_map->j] != '\n')
			exit(1);
		if (p_map->line[p_map->j] == '1')
			mlx_image_to_window(mlx, g_images->wall, 48 * p_map->x, 48 * p_map->y);
		if (p_map->line[p_map->j] == 'P')
			get_player_location(p_map);
		if (p_map->line[p_map->j] == 'C')
		{
			mlx_image_to_window(mlx, g_images->collectible, 48 * p_map->x, 48 * p_map->y);
			p_map->collectible_count += 1;
		}
		 if (p_map->line[p_map->j] == 'E')
		{
			mlx_image_to_window(mlx, g_images->escape, 48 * p_map->x , 48 * p_map->y);
			p_map->escape_count++;
		}
		p_map->x++;
		p_map->j++;
	}
}

void	parse_game_map(mlx_t *mlx, t_map_parsing *p_map)
{
	while (1)
	{
		p_map->j = 0;
		p_map->x = 0;
		p_map->line = get_next_line(p_map->fd);
		if (!p_map->line)
			break ;
		g_m_data->arr[p_map->y] = p_map->line;
		check_line(mlx, p_map);
		g_m_data->line_count += 1;
		p_map->y++;
	}
	if (p_map->collectible_count < 1 || p_map->player_count != 1 || p_map->escape_count != 1)
	{
		ft_putstr_fd("Error\n***PLEASE NOTE*** possible issues with map:\n\t1.Not more than one player allowed\n", STDOUT_FILENO);
		ft_putstr_fd("\t2.Not more than one exit allowed\n\t3.No collectibles found on map\n\t4.Map doesn't exist\n", STDOUT_FILENO);
		exit(1);
	}
	close(p_map->fd);
}

void	check_map_dimensions()
{
	int i;

	i = 0;
	while (g_m_data->arr[i] != 0)
	{
		int j = 0;
		while (g_m_data->arr[i][j] != '\0' && g_m_data->arr[i][j] != '\n')
		{
			if (i == 0 && g_m_data->arr[i][j + 1] == '\n')
				g_m_data->map_width1 = j;
			if (i > 0 && (g_m_data->arr[i][j + 1] == '\n' || g_m_data->arr[i][j + 1] == '\0'))
				g_m_data->map_width2 = j;
			if (g_m_data->map_width1 && g_m_data->map_width2)
			{
				if (g_m_data->map_width1 != g_m_data->map_width2)
				{
					printf("%d, %d:\n", g_m_data->map_width1, g_m_data->map_width2);
					ft_putstr_fd("Error\nNot a valid map\n", STDOUT_FILENO);
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
	while (g_m_data->arr[0][i] != '\0' && g_m_data->arr[0][i] != '\n')
	{
		if (g_m_data->arr[0][i] != '1')
		{
			ft_putstr_fd("Error\nTop Outer wall is not valid\n", STDOUT_FILENO);
			exit(1);
		}
		i++;
	}
}

void	is_bottom_wall_valid()
{
	int i;

	i = 0;
	g_m_data->last_line = g_m_data->line_count - 1;

	while (g_m_data->arr[g_m_data->last_line][i] != '\0' && g_m_data->arr[g_m_data->last_line][i] != '\n')
	{
		if (g_m_data->arr[g_m_data->last_line][i] != '1')
		{
			ft_putstr_fd("Error\nbottom Outer wall is not valid\n", STDOUT_FILENO);
			exit(1);
		}
		i++;
	}
}

void	is_left_wall_valid()
{
	int i;

	i = 0;
	while (i < g_m_data->line_count)
	{
		if (g_m_data->arr[i][0] != '1')
		{
			ft_putstr_fd("Error\nLeft Outer wall is not valid\n", STDOUT_FILENO);
			exit(1);
		}
		i++;
	}
}

void	is_right_wall_valid()
{
	int i;

	i = 0;
	while (i < g_m_data->line_count)
	{
		if (g_m_data->arr[i][g_m_data->map_width1] != '1')
		{
			ft_putstr_fd("Error\nRight outer wall is not valid\n", STDOUT_FILENO);
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

void	clean_up(mlx_t *mlx, t_texture *val)
{
	mlx_delete_image(mlx, g_images->player);
	mlx_delete_image(mlx, g_images->bg);
	mlx_delete_image(mlx, g_images->collectible);
	mlx_delete_image(mlx, g_images->escape);
	mlx_delete_image(mlx, g_images->wall);
	mlx_delete_texture(val->player_texture);
	mlx_delete_texture(val->bg_texture);
	mlx_delete_texture(val->collectible_texture);
	mlx_delete_texture(val->escape_texture);
	mlx_delete_texture(val->wall_texture);
	free(g_images);
	free(g_m_data);
	free(val);
}

void	set_up_game(mlx_t *mlx, t_texture *val, t_map_parsing *p_map)
{
	create_textures(val);
	create_g_images(g_images, mlx, val);
	mlx_image_to_window(mlx, g_images->bg, 0, 0);
	parse_game_map(mlx, p_map);
	check_map_dimensions();
	if (g_m_data->line_count == g_m_data->map_width1 + 1)
	{
		ft_putstr_fd("Error\nMap is a square, it should be rectangular\n", STDOUT_FILENO);
		exit(1);
	}
	check_walls();
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_image_to_window(mlx, g_images->player, g_m_data->player_location_x, g_m_data->player_location_y);
	mlx_set_window_size(mlx, (g_m_data->map_width1 + 1) * 48, g_m_data->line_count * 48);
	mlx_loop(mlx);
	clean_up(mlx, val);
	mlx_terminate(mlx);
}

void	start_game()
{
	mlx_t*			mlx;
	t_texture		*val;
	t_map_parsing	map;
	t_map_parsing	*p_map;

	p_map = &map;
	map.fd = open(ber_file, O_RDONLY);
	if (map.fd == -1)
	{
		perror("Error\n");
		exit(EXIT_FAILURE);
	}
	mlx = mlx_init(WIDTH, HEIGHT, "Jurassic Age", true);
	val = (t_texture*) malloc(sizeof(t_texture));
	g_images = (t_game_image*) malloc(sizeof(t_game_image));
	g_m_data = (t_map_data*) malloc(sizeof(t_map_data));
	if (!g_images || !val || !mlx || !g_m_data)
		return ;
	set_up_game(mlx, val, p_map);
}

int	main(int argc, char *argv[])
{
	t_params	params;

	if (argc != 2)
		ft_putstr_fd("Error\nUsage sample: ./so_long \"./maps/map01.ber\"\n", STDOUT_FILENO);
	else
	{
		while (argv[1][params.i++] != '\0')
		{
			if (argv[1][params.i] == '.')
			{
				if (argv[1][params.i + 1] == 'b' && argv[1][params.i + 2] == 'e'
				&& argv[1][params.i + 3] == 'r')
				{
					if (argv[1][params.i + 4] != '\0')
						break;
					ber_file = argv[1];
					params.valid_file = 1;
					start_game();
				}
			}
		}
		if (!params.valid_file)
			ft_putstr_fd("Error\nFile format not valid\n", STDOUT_FILENO);
	}
	system("leaks test");
	return (EXIT_SUCCESS);
}
