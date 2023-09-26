/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennacir <rennacir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:20:29 by rennacir          #+#    #+#             */
/*   Updated: 2023/09/26 17:36:23 by rennacir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	add_value(t_list *list, char *value, int flag)
{
	if (flag == 1)
	{
		if (list->NO)
			error("Error : NO is duplicated\n");
		list->NO = ft_strdup(value);
	}
	else if (flag == 2)
	{
		if (list->EA)
			error("Error : EA is duplicated\n");
		list->EA = ft_strdup(value);
	}
	else if (flag == 3)
	{
		if (list->WE)
			error("Error : WE is duplicated\n");
		list->WE = ft_strdup(value);
	}
	else if (flag == 4)
	{
		if (list->SO)
			error("Error : SO is duplicated\n");
		list->SO = ft_strdup(value);
	}
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	get_rgb_value(char *value)
{
	char	**split;
	int		val;

	split = ft_split(value, ',');
	val = create_trgb(0, ft_atoi(split[0]),
			ft_atoi(split[1]), ft_atoi(split[2]));
	free_2d_tab(split);
	return (val);
}

void	check_elem_and_value(char *line, char *sub, int j, t_list *list)
{
	char		*value;
	static int	k;

	if (k < 6)
		value = get_value_of_elmnts(line, j);
	if (!ft_strcmp(sub, "NO") && k < 6)
		add_value(list, value, 1);
	else if (!ft_strcmp(sub, "EA") && k < 6)
		add_value(list, value, 2);
	else if (!ft_strcmp(sub, "WE") && k < 6)
		add_value(list, value, 3);
	else if (!ft_strcmp(sub, "SO") && k < 6)
		add_value(list, value, 4);
	else if (!ft_strcmp(sub, "F") && k < 6)
	{
		check_f_and_c(value);
		list->F = get_rgb_value(value);
	}
	else if (!ft_strcmp(sub, "C") && k < 6 && list->C == -1)
	{
		check_f_and_c(value);
		list->C = get_rgb_value(value);
	}
	free(value);
	k++;
}
