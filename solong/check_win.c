/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_win.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 01:54:25 by bogunlan          #+#    #+#             */
/*   Updated: 2022/08/28 20:25:41 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"


int	player_can_exit_game(void)
{
	if (g_images()->player->instances[0].y + OBJ_LENGTH >= g_images()->escape->instances[0].y
		&& g_images()->player->instances[0].y <= g_images()->escape->instances[0].y + OBJ_LENGTH
		&& g_images()->player->instances[0].x <= g_images()->escape->instances[0].x + OBJ_LENGTH
		&& g_images()->player->instances[0].x + OBJ_LENGTH >= g_images()->escape->instances[0].x
	)
	{
		return (1);
	}
	return (0);
}

int	player_on_exit_tile(void)
{
	if (player_can_exit_game())
		return (1);
	return (0);
}

int	player_wins(int grabbed_eggs, int i, int j)
{
	if (grabbed_eggs == g_images()->collectible->count)
	{
		if (g_m_data()->arr[i][j] == 'E')
			if (player_on_exit_tile())
			{
				ft_putstr_fd("Yeepee! Way to Dino\n", STDOUT_FILENO);
				return (1);
			}
	}
	return (0);
}
