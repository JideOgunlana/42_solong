/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 01:51:25 by bogunlan          #+#    #+#             */
/*   Updated: 2022/08/28 18:07:59 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"


int	check_for_w_move(t_map_data *g_m_data)
{
	t_params	params;

	params.i = -1;
	while (g_m_data->arr[++params.i] != 0)
	{
		params.j = -1;
		while (g_m_data->arr[params.i][++params.j] != '\0')
		{
			if (player_wins(g_m_data->grabbed_eggs, params.i, params.j))
				exit(1);
			if (g_m_data->arr[params.i][params.j] == 'C')
			{
				if (player_on_collectible_tile(g_m_data->egg_index))
					break ;
				g_m_data->egg_index += 1;
			}
			if (g_m_data->arr[params.i][params.j] == '1')
			{
				if (wall_in_w_direction(g_m_data->wall_index))
					return (0);
				g_m_data->wall_index += 1;
			}
		}
	}
	return (1);
}

int	check_for_s_move(t_map_data *g_m_data)
{
	t_params	params;

	params.i = -1;
	while (g_m_data->arr[++params.i] != 0)
	{
		params.j = -1;
		while (g_m_data->arr[params.i][++params.j] != '\0')
		{
			if (player_wins(g_m_data->grabbed_eggs, params.i, params.j))
				exit(1);
			if (g_m_data->arr[params.i][params.j] == 'C')
			{
				if (player_on_collectible_tile(g_m_data->egg_index))
					break ;
				g_m_data->egg_index += 1;
			}
			if (g_m_data->arr[params.i][params.j] == '1')
			{
				if (wall_in_s_direction(g_m_data->wall_index))
					return (0);
				g_m_data->wall_index += 1;
			}
		}
	}
	return (1);
}

int	check_for_a_move(t_map_data *g_m_data)
{
	t_params	params;

	params.i = -1;
	while (g_m_data->arr[++params.i] != 0)
	{
		params.j = -1;
		while (g_m_data->arr[params.i][++params.j] != '\0')
		{
			if (player_wins(g_m_data->grabbed_eggs, params.i, params.j))
				exit(1);
			if (g_m_data->arr[params.i][params.j] == 'C')
			{
				if (player_on_collectible_tile(g_m_data->egg_index))
					break ;
				g_m_data->egg_index += 1;
			}
			if (g_m_data->arr[params.i][params.j] == '1')
			{
				if (wall_in_a_direction(g_m_data->wall_index))
					return (0);
				g_m_data->wall_index += 1;
			}
		}
	}
	return (1);
}

int	check_for_d_move(t_map_data *g_m_data)
{
	t_params	params;

	params.i = -1;
	while (g_m_data->arr[++params.i] != 0)
	{
		params.j = -1;
		while (g_m_data->arr[params.i][++params.j] != '\0')
		{
			if (player_wins(g_m_data->grabbed_eggs, params.i, params.j))
				exit(1);
			if (g_m_data->arr[params.i][params.j] == 'C')
			{
				if (player_on_collectible_tile(g_m_data->egg_index))
					break ;
				g_m_data->egg_index += 1;
			}
			if (g_m_data->arr[params.i][params.j] == '1')
			{
				if (wall_in_d_direction(g_m_data->wall_index))
					return (0);
				g_m_data->wall_index += 1;
			}
		}
	}
	return (1);
}
