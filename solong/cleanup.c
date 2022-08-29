/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 02:14:56 by bogunlan          #+#    #+#             */
/*   Updated: 2022/08/29 20:01:50 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	clean_up(mlx_t *mlx, t_texture *val)
{
	mlx_delete_image(mlx, g_img()->p);
	mlx_delete_image(mlx, g_img()->bg);
	mlx_delete_image(mlx, g_img()->c);
	mlx_delete_image(mlx, g_img()->e);
	mlx_delete_image(mlx, g_img()->w);
	mlx_delete_texture(val->player_texture);
	mlx_delete_texture(val->bg_texture);
	mlx_delete_texture(val->collectible_texture);
	mlx_delete_texture(val->escape_texture);
	mlx_delete_texture(val->wall_texture);
	free(val);
}
