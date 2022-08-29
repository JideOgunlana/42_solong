/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 01:01:06 by bogunlan          #+#    #+#             */
/*   Updated: 2022/08/29 20:13:51 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	is_top_wall_valid(void)
{
	int	i;

	i = 0;
	while (g_m_data()->arr[0][i] != '\0' && g_m_data()->arr[0][i] != '\n')
	{
		if (g_m_data()->arr[0][i] != '1')
		{
			ft_putstr_fd("Error\nMap not valid\n", STDOUT_FILENO);
			exit(1);
		}
		i++;
	}
}

void	is_bottom_wall_valid(void)
{
	int	i;

	i = 0;
	g_m_data()->last_line = g_m_data()->lc - 1;
	while (g_m_data()->arr[g_m_data()->last_line][i] != '\0'
		&& g_m_data()->arr[g_m_data()->last_line][i] != '\n')
	{
		if (g_m_data()->arr[g_m_data()->last_line][i] != '1')
		{
			ft_putstr_fd("Error\nMap not valid\n", STDOUT_FILENO);
			exit(1);
		}
		i++;
	}
}

void	is_left_wall_valid(void)
{
	int	i;

	i = 0;
	while (i < g_m_data()->lc)
	{
		if (g_m_data()->arr[i][0] != '1')
		{
			ft_putstr_fd("Error\nMap not valid\n", STDOUT_FILENO);
			exit(1);
		}
		i++;
	}
}

void	is_right_wall_valid(void)
{
	int	i;

	i = 0;
	while (i < g_m_data()->lc)
	{
		if (g_m_data()->arr[i][g_m_data()->mw1] != '1')
		{
			ft_putstr_fd("Error\nMap not valid\n", STDOUT_FILENO);
			exit(1);
		}
		i++;
	}
}

void	check_walls(void)
{
	is_top_wall_valid();
	is_bottom_wall_valid();
	is_left_wall_valid();
	is_right_wall_valid();
}
