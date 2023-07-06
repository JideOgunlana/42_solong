/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 00:34:35 by bogunlan          #+#    #+#             */
/*   Updated: 2023/07/05 14:29:01 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	get_p(t_map_parsing *p_map)
{
	g_m_data()->p_x = 48 * p_map->x;
	g_m_data()->p_y = 48 * p_map->y;
	p_map->player_count++;
}

void	check_map_composition(t_map_parsing *p_map)
{
	if (p_map->line[p_map->j] != '1' && p_map->line[p_map->j] != 'P'
		&& p_map->line[p_map->j] != 'E' && p_map->line[p_map->j] != 'C'
		&& p_map->line[p_map->j] != '0' && p_map->line[p_map->j] != '\n')
	{
		ft_putstr_fd("Error\nMap contains invalid composition\n", 1);
		ft_putstr_fd("Valid Compositions are: ", 1);
		ft_putstr_fd("0, 1, C, P and E\n", 1);
		exit(1);
	}
}

void	check_line(mlx_t *mlx, t_map_parsing *m)
{
	while (m->line[m->j] != '\0')
	{
		check_map_composition(m);
		if (m->line[m->j] == '0' || m->line[m->j] == '1' || m->line[m->j] == 'P' ||
			m->line[m->j] == 'C' || m->line[m->j] == 'E'
		)
			mlx_image_to_window(mlx, g_img()->bg, 48 * m->x, 48 * m->y);
		if (m->line[m->j] == '1')
			mlx_image_to_window(mlx, g_img()->w, 48 * m->x, 48 * m->y);
		if (m->line[m->j] == 'P')
			get_p(m);
		if (m->line[m->j] == 'C')
		{
			mlx_image_to_window(mlx, g_img()->c, 48 * m->x, 48 * m->y);
			m->collectible_count += 1;
		}
		if (m->line[m->j] == 'E')
		{
			mlx_image_to_window(mlx, g_img()->e, 48 * m->x, 48 * m->y);
			m->escape_count++;
		}
		if (m->line[m->j] == '0')
			m->space_count++;
		m->x++;
		m->j++;
	}
}

void	parse_game_map(mlx_t *mlx, t_map_parsing *p_map)
{
	p_map->y = 0;
	while (1)
	{
		p_map->j = 0;
		p_map->x = 0;
		p_map->line = get_next_line(p_map->fd);
		if (!p_map->line)
			break ;
		g_m_data()->arr[p_map->y] = p_map->line;
		check_line(mlx, p_map);
		g_m_data()->lc += 1;
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

int	check_map_dimensions(void)
{
	t_params	param;

	param.i = 0;
	while (g_m_data()->arr[param.i] != 0)
	{
		param.j = 0;
		while (g_m_data()->arr[param.i][param.j] != '\0'
			&& g_m_data()->arr[param.i][param.j] != '\n')
		{
			if (param.i == 0 && g_m_data()->arr[param.i][param.j + 1] == '\n')
				g_m_data()->mw1 = param.j;
			if (param.i > 0 && (g_m_data()->arr[param.i][param.j + 1] == '\n'
				|| g_m_data()->arr[param.i][param.j + 1] == '\0'))
				g_m_data()->mw2 = param.j;
			if (g_m_data()->mw1 && g_m_data()->mw2)
			{
				if (g_m_data()->mw1 != g_m_data()->mw2)
					return (1);
			}
			param.j++;
		}
		param.i++;
	}
	return (0);
}
