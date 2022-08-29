/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 12:46:58 by bogunlan          #+#    #+#             */
/*   Updated: 2022/08/29 15:51:01 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	hook(void *key)
{
	int		egg_index;
	int		wall_index;
	int		grabbed_eggs;

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

void	set_up_game(mlx_t *mlx, t_texture *val, t_map_parsing *p_map)
{
	create_textures(val);
	create_g_images(mlx, val);
	mlx_image_to_window(mlx, g_images()->bg, 0, 0);
	parse_game_map(mlx, p_map);
	check_map_dimensions();
	if (g_m_data()->line_count == g_m_data()->map_width1 + 1)
	{
		ft_putstr_fd("Error\nMap is a square, it should be rectangular\n", STDOUT_FILENO);
		exit(1);
	}
	check_walls(g_m_data());
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_image_to_window(mlx, g_images()->player, g_m_data()->player_location_x, g_m_data()->player_location_y);
	mlx_set_window_size(mlx, (g_m_data()->map_width1 + 1) * 48, (g_m_data()->line_count) * 48);
	mlx_loop(mlx);
	clean_up(mlx, val);
	mlx_terminate(mlx);
}

void	start_game(char *ber_file)
{
	mlx_t*			mlx;
	t_texture		*val;
	t_map_parsing	map;


	map.fd = open(ber_file, O_RDONLY);
	if (map.fd == -1)
	{
		perror("Error\n");
		exit(EXIT_FAILURE);
	}
	mlx = mlx_init(WIDTH, HEIGHT, "Jurassic Age", true);
	val = (t_texture*) malloc(sizeof(t_texture));
	if (!val || !mlx)
		return ;
	set_up_game(mlx, val, &map);
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
					params.valid_file = 1;
					start_game(argv[1]);
				}
			}
		}
		if (!params.valid_file)
			ft_putstr_fd("Error\nFile format not valid\n", STDOUT_FILENO);
	}
	return (EXIT_SUCCESS);
}
