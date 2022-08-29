/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_win.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 01:54:25 by bogunlan          #+#    #+#             */
/*   Updated: 2022/08/29 20:02:19 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	player_can_exit_game(void)
{
	if (g_img()->p->instances[0].y + L >= g_img()->e->instances[0].y
		&&g_img()->p->instances[0].y <= g_img()->e->instances[0].y + L
		&&g_img()->p->instances[0].x <= g_img()->e->instances[0].x + L
		&&g_img()->p->instances[0].x + L >= g_img()->e->instances[0].x
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
	if (grabbed_eggs == g_img()->c->count)
	{
		if (g_m_data()->arr[i][j] == 'E')
		{
			if (player_on_exit_tile())
			{
				ft_putstr_fd("Yeepee! Way to Dino\n", STDOUT_FILENO);
				return (1);
			}
		}
	}
	return (0);
}
