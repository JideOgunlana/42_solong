/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectibles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 01:55:52 by bogunlan          #+#    #+#             */
/*   Updated: 2022/08/28 20:26:18 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"


int	picked_collectible(int egg_index)
{
	if (g_images()->player->instances[0].y + OBJ_LENGTH >= g_images()->collectible->instances[egg_index].y
		&& g_images()->player->instances[0].y <= g_images()->collectible->instances[egg_index].y + OBJ_LENGTH
		&& g_images()->player->instances[0].x <= g_images()->collectible->instances[egg_index].x + OBJ_LENGTH
		&& g_images()->player->instances[0].x + OBJ_LENGTH >= g_images()->collectible->instances[egg_index].x
	)
	{
		return (1);
	}
	return (0);
}

int	picked_collectibles_count(int collectibles_count, int grabbed_eggs)
{
	int	k;

	k = 0;
	while (k < collectibles_count)
	{
		if (g_images()->collectible->instances[k].enabled == 0)
			grabbed_eggs += 1;
		k++;
	}
	return (grabbed_eggs);
}

int	player_on_collectible_tile(int egg_index)
{
	if (picked_collectible(egg_index))
	{
		printf("collectible - (%d, %d)\n", g_images()->collectible->instances[egg_index].x, g_images()->collectible->instances[egg_index].y);
		g_images()->collectible->instances[egg_index].enabled = 0;
	}
	return (0);
}
