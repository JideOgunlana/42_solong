/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 02:14:56 by bogunlan          #+#    #+#             */
/*   Updated: 2022/08/28 05:02:08 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

extern t_game_image	*g_images;
extern t_map_data	*g_m_data;

void	clean_up(mlx_t *mlx, t_texture *val)
{
	mlx_delete_image(mlx, g_images->player);
	mlx_delete_image(mlx, g_images->bg);
	mlx_delete_image(mlx, g_images->collectible);
	mlx_delete_image(mlx, g_images->escape);
	mlx_delete_image(mlx, g_images->wall);
	mlx_delete_texture(val->player_texture);
	mlx_delete_texture(val->bg_texture);
	mlx_delete_texture(val->collectible_texture);
	mlx_delete_texture(val->escape_texture);
	mlx_delete_texture(val->wall_texture);
	free(g_images);
	free(val);
}
