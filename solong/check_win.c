/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_win.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 01:54:25 by bogunlan          #+#    #+#             */
/*   Updated: 2022/08/28 18:13:56 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"



int	player_can_exit_game(t_img *g_images)
{
	if (g_images->player->instances[0].y + OBJ_LENGTH >= g_images->escape->instances[0].y
		&& g_images->player->instances[0].y <= g_images->escape->instances[0].y + OBJ_LENGTH
		&& g_images->player->instances[0].x <= g_images->escape->instances[0].x + OBJ_LENGTH
		&& g_images->player->instances[0].x + OBJ_LENGTH >= g_images->escape->instances[0].x
	)
	{
		return (1);
	}
	return (0);
}

int	player_on_exit_tile(t_img *g_images)
{
	if (player_can_exit_game(g_images))
		return (1);
	return (0);
}

int	player_wins(t_map_data *g_m_data, t_img *g_images, int i, int j)
{
	if (g_m_data->grabbed_eggs == g_images->collectible->count)
	{
		if (g_m_data->arr[i][j] == 'E')
			if (player_on_exit_tile(g_images))
			{
				ft_putstr_fd("Yeepee! Way to Dino\n", STDOUT_FILENO);
				return (1);
			}
	}
	return (0);
}
