/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 01:48:30 by bogunlan          #+#    #+#             */
/*   Updated: 2022/08/29 20:01:12 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	wall_in_w_direction(int wi)
{
	if (g_img()->p->instances[0].y + L - 4 >= g_img()->w->instances[wi].y
		&&g_img()->p->instances[0].y - 4 <= g_img()->w->instances[wi].y + L
		&&g_img()->p->instances[0].x <= g_img()->w->instances[wi].x + L
		&&g_img()->p->instances[0].x + L >= g_img()->w->instances[wi].x
	)
		return (1);
	return (0);
}

int	wall_in_s_direction(int wi)
{
	if (g_img()->p->instances[0].y + L + 4 >= g_img()->w->instances[wi].y
		&&g_img()->p->instances[0].y + 4 <= g_img()->w->instances[wi].y + L
		&&g_img()->p->instances[0].x <= g_img()->w->instances[wi].x + L
		&&g_img()->p->instances[0].x + L >= g_img()->w->instances[wi].x
	)
	{
		return (1);
	}
	return (0);
}

int	wall_in_a_direction(int wi)
{
	if (g_img()->p->instances[0].y + L >= g_img()->w->instances[wi].y
		&&g_img()->p->instances[0].y <= g_img()->w->instances[wi].y + L
		&&g_img()->p->instances[0].x - 4 <= g_img()->w->instances[wi].x + L
		&&g_img()->p->instances[0].x + L - 4 >= g_img()->w->instances[wi].x
	)
	{
		return (1);
	}
	return (0);
}

int	wall_in_d_direction(int wi)
{
	if (g_img()->p->instances[0].y + L >= g_img()->w->instances[wi].y
		&&g_img()->p->instances[0].y <= g_img()->w->instances[wi].y + L
		&&g_img()->p->instances[0].x + 4 <= g_img()->w->instances[wi].x + L
		&&g_img()->p->instances[0].x + L + 4 >= g_img()->w->instances[wi].x
	)
	{
		return (1);
	}
	return (0);
}
