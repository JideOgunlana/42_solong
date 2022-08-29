/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 01:16:13 by bogunlan          #+#    #+#             */
/*   Updated: 2022/08/29 16:16:10 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"


void	w_key_pressed(int grabbed_eggs, int egg_index, int wall_index)
{
	int	move;

	grabbed_eggs += picked_collectibles_count(g_images()->collectible->count, grabbed_eggs);
	move = check_for_w_move(grabbed_eggs, egg_index, wall_index);
	if (move && g_m_data()->movement_count++)
		g_images()->player->instances[0].y -= 4;
	if (g_m_data()->movement_count % 4 == 0)
	{
		ft_putstr_fd("moves: ", STDOUT_FILENO);
		ft_putnbr_fd(g_m_data()->movement_count / 4, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
}

void	s_key_pressed(int grabbed_eggs, int egg_index, int wall_index)
{
	int	move;

	grabbed_eggs += picked_collectibles_count(g_images()->collectible->count, grabbed_eggs);
	move = check_for_s_move(grabbed_eggs, egg_index, wall_index);
	if (move && g_m_data()->movement_count++)
		g_images()->player->instances[0].y += 4;
	if (g_m_data()->movement_count % 4 == 0)
	{
		ft_putstr_fd("moves: ", STDOUT_FILENO);
		ft_putnbr_fd(g_m_data()->movement_count / 4, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
}

void	a_key_pressed(int grabbed_eggs, int egg_index, int wall_index)
{
	int	move;

	grabbed_eggs += picked_collectibles_count(g_images()->collectible->count, grabbed_eggs);
	move = check_for_a_move(grabbed_eggs, egg_index, wall_index);
	if (move && g_m_data()->movement_count++)
		g_images()->player->instances[0].x -= 4;
	if (g_m_data()->movement_count % 4 == 0)
	{
		ft_putstr_fd("moves: ", STDOUT_FILENO);
		ft_putnbr_fd(g_m_data()->movement_count / 4, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
}

void	d_key_pressed(int grabbed_eggs, int egg_index, int wall_index)
{
	int	move;

	grabbed_eggs += picked_collectibles_count(g_images()->collectible->count, grabbed_eggs);
	move = check_for_d_move(grabbed_eggs, egg_index, wall_index);
	if (move && g_m_data()->movement_count++)
		g_images()->player->instances[0].x += 4;
	if (g_m_data()->movement_count % 4 == 0)
	{
		ft_putstr_fd("moves: ", STDOUT_FILENO);
		ft_putnbr_fd(g_m_data()->movement_count / 4, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
}
