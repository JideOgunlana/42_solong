/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 00:31:04 by bogunlan          #+#    #+#             */
/*   Updated: 2022/08/29 20:00:17 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

t_game_image	*g_img(void)
{
	static t_game_image	all_g_i;

	return (&all_g_i);
}

t_map_data	*g_m_data(void)
{
	static t_map_data	all_m_d;

	return (&all_m_d);
}

void	create_textures(t_texture *val)
{
	val->wall_texture = mlx_load_png("./img/wall1.png");
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

void	create_g_images(mlx_t *mlx, t_texture *val)
{
	t_tex_img	tex_to_img;

	tex_to_img.p_t_i = mlx_texture_to_image(mlx, val->player_texture);
	tex_to_img.bg_t_i = mlx_texture_to_image(mlx, val->bg_texture);
	tex_to_img.w_t_i = mlx_texture_to_image(mlx, val->wall_texture);
	tex_to_img.c_t_i = mlx_texture_to_image(mlx, val->collectible_texture);
	tex_to_img.e_t_i = mlx_texture_to_image(mlx, val->escape_texture);
	g_img()->p = tex_to_img.p_t_i;
	g_img()->w = tex_to_img.w_t_i;
	g_img()->bg = tex_to_img.bg_t_i;
	g_img()->c = tex_to_img.c_t_i;
	g_img()->e = tex_to_img.e_t_i;
	if (!g_img()->bg || !g_img()->p
		|| !g_img()->w || !g_img()->c
		|| !g_img()->e)
	{
		ft_putstr_fd("Error\nFailed to load\n", STDOUT_FILENO);
		exit(EXIT_FAILURE);
	}
}
