/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 01:48:30 by bogunlan          #+#    #+#             */
/*   Updated: 2022/08/28 20:26:39 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"


int	wall_in_w_direction(int wall_index)
{
	if (g_images()->player->instances[0].y + OBJ_LENGTH - 4 >= g_images()->wall->instances[wall_index].y
		&& g_images()->player->instances[0].y - 4 <= g_images()->wall->instances[wall_index].y + OBJ_LENGTH
		&& g_images()->player->instances[0].x <= g_images()->wall->instances[wall_index].x + OBJ_LENGTH
		&& g_images()->player->instances[0].x + OBJ_LENGTH >= g_images()->wall->instances[wall_index].x
	)
		return (1);
	return (0);
}

int	wall_in_s_direction(int wall_index)
{
	if (g_images()->player->instances[0].y + OBJ_LENGTH + 4 >= g_images()->wall->instances[wall_index].y
		&& g_images()->player->instances[0].y + 4 <= g_images()->wall->instances[wall_index].y + OBJ_LENGTH
		&& g_images()->player->instances[0].x <= g_images()->wall->instances[wall_index].x + OBJ_LENGTH
		&& g_images()->player->instances[0].x + OBJ_LENGTH >= g_images()->wall->instances[wall_index].x
	)
	{
		return (1);
	}
	return (0);
}

int	wall_in_a_direction(int wall_index)
{
	if (g_images()->player->instances[0].y + OBJ_LENGTH >= g_images()->wall->instances[wall_index].y
		&& g_images()->player->instances[0].y <= g_images()->wall->instances[wall_index].y + OBJ_LENGTH
		&& g_images()->player->instances[0].x - 4 <= g_images()->wall->instances[wall_index].x + OBJ_LENGTH
		&& g_images()->player->instances[0].x + OBJ_LENGTH - 4 >= g_images()->wall->instances[wall_index].x
	)
	{
		return (1);
	}
	return (0);
}

int	wall_in_d_direction(int wall_index)
{
	if (g_images()->player->instances[0].y + OBJ_LENGTH >= g_images()->wall->instances[wall_index].y
		&& g_images()->player->instances[0].y <= g_images()->wall->instances[wall_index].y + OBJ_LENGTH
		&& g_images()->player->instances[0].x + 4 <= g_images()->wall->instances[wall_index].x + OBJ_LENGTH
		&& g_images()->player->instances[0].x + OBJ_LENGTH + 4 >= g_images()->wall->instances[wall_index].x
	)
	{
		return (1);
	}
	return (0);
}
