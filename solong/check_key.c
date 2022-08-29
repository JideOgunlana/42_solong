/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 01:51:25 by bogunlan          #+#    #+#             */
/*   Updated: 2022/08/28 20:25:17 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	check_for_w_move(int grabbed_eggs, int egg_index, int wall_index)
{
	t_params	params;

	params.i = -1;
	while (g_m_data()->arr[++params.i] != 0)
	{
		params.j = -1;
		while (g_m_data()->arr[params.i][++params.j] != '\0')
		{
			if (player_wins(grabbed_eggs, params.i, params.j))
				exit(1);
			if (g_m_data()->arr[params.i][params.j] == 'C')
			{
				if (player_on_collectible_tile(egg_index))
					break ;
				egg_index += 1;
			}
			if (g_m_data()->arr[params.i][params.j] == '1')
			{
				if (wall_in_w_direction(wall_index))
					return (0);
				wall_index += 1;
			}
		}
	}
	return (1);
}

int	check_for_s_move(int grabbed_eggs, int egg_index, int wall_index)
{
	t_params	params;

	params.i = -1;
	while (g_m_data()->arr[++params.i] != 0)
	{
		params.j = -1;
		while (g_m_data()->arr[params.i][++params.j] != '\0')
		{
			if (player_wins(grabbed_eggs, params.i, params.j))
				exit(1);
			if (g_m_data()->arr[params.i][params.j] == 'C')
			{
				if (player_on_collectible_tile(egg_index))
					break ;
				egg_index += 1;
			}
			if (g_m_data()->arr[params.i][params.j] == '1')
			{
				if (wall_in_s_direction(wall_index))
					return (0);
				wall_index += 1;
			}
		}
	}
	return (1);
}

int	check_for_a_move(int grabbed_eggs, int egg_index, int wall_index)
{
	t_params	params;

	params.i = -1;
	while (g_m_data()->arr[++params.i] != 0)
	{
		params.j = -1;
		while (g_m_data()->arr[params.i][++params.j] != '\0')
		{
			if (player_wins(grabbed_eggs, params.i, params.j))
				exit(1);
			if (g_m_data()->arr[params.i][params.j] == 'C')
			{
				if (player_on_collectible_tile(egg_index))
					break ;
				egg_index += 1;
			}
			if (g_m_data()->arr[params.i][params.j] == '1')
			{
				if (wall_in_a_direction(wall_index))
					return (0);
				wall_index += 1;
			}
		}
	}
	return (1);
}

int	check_for_d_move(int grabbed_eggs, int egg_index, int wall_index)
{
	t_params	params;

	params.i = -1;
	while (g_m_data()->arr[++params.i] != 0)
	{
		params.j = -1;
		while (g_m_data()->arr[params.i][++params.j] != '\0')
		{
			if (player_wins(grabbed_eggs, params.i, params.j))
				exit(1);
			if (g_m_data()->arr[params.i][params.j] == 'C')
			{
				if (player_on_collectible_tile(egg_index))
					break ;
				egg_index += 1;
			}
			if (g_m_data()->arr[params.i][params.j] == '1')
			{
				if (wall_in_d_direction(wall_index))
					return (0);
				wall_index += 1;
			}
		}
	}
	return (1);
}
