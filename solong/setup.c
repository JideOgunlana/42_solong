/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 00:31:04 by bogunlan          #+#    #+#             */
/*   Updated: 2022/08/28 17:32:49 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"


void	create_textures(t_img *val)
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

void	create_g_images(mlx_t *mlx, t_img *val)
{
	val->bg = mlx_texture_to_image(mlx, val->bg_texture);
	val->player = mlx_texture_to_image(mlx, val->player_texture);
	val->wall = mlx_texture_to_image(mlx, val->wall_texture);
	val->collectible = mlx_texture_to_image(mlx, val->collectible_texture);
	val->escape = mlx_texture_to_image(mlx, val->escape_texture);

	if (!val->bg || !val->player
		|| !val->wall || !val->collectible
		|| !val->escape)
	{
		ft_putstr_fd("Error\nFailed to load\n", STDOUT_FILENO);
		exit(EXIT_FAILURE);
	}
}