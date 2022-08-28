/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 01:16:13 by bogunlan          #+#    #+#             */
/*   Updated: 2022/08/28 18:31:34 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"


void	w_key_pressed(t_map_data *g_m_data, t_img *g_img)
{
	int	move;

	g_m_data->grabbed_eggs += picked_collectibles_count(g_img->collectible->count, g_m_data->grabbed_eggs);
	move = check_for_w_move(g_m_data);
	if (move && g_m_data->movement_count++)
		g_img->player->instances[0].y -= 4;
	ft_putstr_fd("moves: ", STDOUT_FILENO);
	ft_putnbr_fd(g_m_data->movement_count, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
}

void	s_key_pressed(t_map_data *g_m_data, t_img *g_img)
{
	int	move;

	g_m_data->grabbed_eggs += picked_collectibles_count(g_img->collectible->count, g_m_data->grabbed_eggs);
	move = check_for_s_move(g_m_data);
	if (move && g_m_data->movement_count++)
		g_img->player->instances[0].y += 4;
	ft_putstr_fd("moves: ", STDOUT_FILENO);
	ft_putnbr_fd(g_m_data->movement_count, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
}

void	a_key_pressed(t_map_data *g_m_data,t_img *g_img)
{
	int	move;

	g_m_data->grabbed_eggs += picked_collectibles_count(g_img->collectible->count, g_m_data->grabbed_eggs);
	move = check_for_a_move(g_m_data);
	if (move && g_m_data->movement_count++)
		g_img->player->instances[0].x -= 4;
	ft_putstr_fd("moves: ", STDOUT_FILENO);
	ft_putnbr_fd(g_m_data->movement_count, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
}

void	d_key_pressed(t_map_data *g_m_data,t_img *g_img)
{
	int	move;

	g_m_data->grabbed_eggs += picked_collectibles_count(g_img->collectible->count, g_m_data->grabbed_eggs);
	move = check_for_d_move(g_m_data);
	if (move && g_m_data->movement_count++)
		g_img->player->instances[0].x += 4;
	ft_putstr_fd("moves: ", STDOUT_FILENO);
	ft_putnbr_fd(g_m_data->movement_count, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
}
