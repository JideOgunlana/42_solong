/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 00:34:35 by bogunlan          #+#    #+#             */
/*   Updated: 2022/08/28 05:01:56 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

extern t_game_image		*g_images;
extern t_map_data		*g_m_data;

void	get_player_location(t_map_parsing *p_map)
{
		g_m_data->player_location_x = 48 * p_map->x;
		g_m_data->player_location_y = 48 * p_map->y;
		p_map->player_count++;
}

void	check_map_composition(t_map_parsing *p_map)
{
			if (p_map->line[p_map->j] != '1' && p_map->line[p_map->j] != 'P'
			&& p_map->line[p_map->j] != 'E' && p_map->line[p_map->j] != 'C'
			&& p_map->line[p_map->j] != '0' && p_map->line[p_map->j] != '\n')
			{
				ft_putstr_fd("Error\nMap contains invalid composition\n", STDOUT_FILENO);
				ft_putstr_fd("Valid Compositions are: ", STDOUT_FILENO);
				ft_putstr_fd("0, 1, C, P and E\n", STDOUT_FILENO);
				exit(1);
			}
}

void	check_line(mlx_t *mlx, t_map_parsing *p_map)
{
	while (p_map->line[p_map->j] != '\0')
	{
		check_map_composition(p_map);
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
			mlx_image_to_window(mlx, g_images->escape, 48 * p_map->x, 48 * p_map->y);
			p_map->escape_count++;
		}
		if (p_map->line[p_map->j] == '0')
			p_map->space_count++;
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
	if (p_map->collectible_count < 1 || p_map->player_count != 1
		|| p_map->escape_count != 1 || p_map->space_count < 1)
	{
		ft_putstr_fd("Error\n* Map not valid *   Possilbe reasons:\n\t", 1);
		ft_putstr_fd("1.No spaces\n\t2.More than 1 player\n", 1);
		ft_putstr_fd("\t2.More than 1 exit\n\t3.No collectibles found\n", 1);
		exit(1);
	}
	close(p_map->fd);
}

void	check_map_dimensions(void)
{
	int	i;
	int	j;

	i = 0;
	while (g_m_data->arr[i] != 0)
	{
		j = 0;
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
					ft_putstr_fd("Error\nMap not valid\n", 1);
					exit(1);
				}
			}
			j++;
		}
		i++;
	}
}
