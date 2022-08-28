/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 00:31:04 by bogunlan          #+#    #+#             */
/*   Updated: 2022/08/28 05:01:40 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

extern t_game_image		*g_images;
extern t_map_data		*g_m_data;

void	create_textures(t_texture *val)
{
	val->wall_texture =  mlx_load_png("./img/wall1.png");
	val->player_texture = mlx_load_png("./img/dion.png");
	val->bg_texture = mlx_load_png("./img/map.png");
	val->collectible_texture = mlx_load_png("./img/egg1.png");
	val->escape_texture = mlx_load_png("./img/escape.png");

	if (!val->wall_texture || !val->player_texture
		|| !val->bg_texture || !val->collectible_texture 
		|| !val->escape_texture)
	{
		ft_putstr_fd("Error\nFailed to load\n", STDOUT_FILENO);
		exit(EXIT_FAILURE);
	}
}

void	create_g_images(t_game_image* g_images, mlx_t *mlx, t_texture *val)
{
	g_images->bg = mlx_texture_to_image(mlx, val->bg_texture);
	g_images->player = mlx_texture_to_image(mlx, val->player_texture);
	g_images->wall = mlx_texture_to_image(mlx, val->wall_texture);
	g_images->collectible = mlx_texture_to_image(mlx, val->collectible_texture);
	g_images->escape = mlx_texture_to_image(mlx, val->escape_texture);

	if (!g_images->bg || !g_images->player
		|| !g_images->wall || !g_images->collectible
		|| !g_images->escape)
	{
		ft_putstr_fd("Error\nFailed to load\n", STDOUT_FILENO);
		exit(EXIT_FAILURE);
	}
}