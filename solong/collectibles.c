/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectibles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 01:55:52 by bogunlan          #+#    #+#             */
/*   Updated: 2022/08/29 20:01:40 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	picked_collectible(int egg_index)
{
	if (g_img()->p->instances[0].y + L >= g_img()->c->instances[egg_index].y
		&&g_img()->p->instances[0].y <= g_img()->c->instances[egg_index].y + L
		&&g_img()->p->instances[0].x <= g_img()->c->instances[egg_index].x + L
		&&g_img()->p->instances[0].x + L >= g_img()->c->instances[egg_index].x
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
		if (g_img()->c->instances[k].enabled == 0)
			grabbed_eggs += 1;
		k++;
	}
	return (grabbed_eggs);
}

int	player_on_collectible_tile(int egg_index)
{
	if (picked_collectible(egg_index))
	{
		g_img()->c->instances[egg_index].enabled = 0;
	}
	return (0);
}
