/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennacir <rennacir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:20:29 by rennacir          #+#    #+#             */
/*   Updated: 2023/09/27 12:09:43 by rennacir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	add_value(t_list *list, char *value, int flag)
{
	if (flag == 1)
	{
		if (list->no)
			error("Error : NO is duplicated\n");
		list->no = ft_strdup(value);
	}
	else if (flag == 2)
	{
		if (list->ea)
			error("Error : EA is duplicated\n");
		list->ea = ft_strdup(value);
	}
	else if (flag == 3)
	{
		if (list->we)
			error("Error : we is duplicated\n");
		list->we = ft_strdup(value);
	}
	else if (flag == 4)
	{
		if (list->so)
			error("Error : so is duplicated\n");
		list->so = ft_strdup(value);
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

void	check_elem_and_value_help(char *sub, int k, char *value, t_list *list)
{
	static int	f;
	static int	c;

	if (!ft_strcmp(sub, "F") && k < 6)
	{
		check_f_and_c(value);
		list->f = get_rgb_value(value);
		f++;
	}
	else if (!ft_strcmp(sub, "C") && k < 6)
	{
		check_f_and_c(value);
		list->c = get_rgb_value(value);
		c++;
	}
	if (c > 1 || f > 1)
		error("Error\n");
}

void	check_elem_and_value(char *line, char *sub, int j, t_list *list)
{
	char		*value;
	static int	k;

	value = NULL;
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
	else if ((!ft_strcmp(sub, "F") || !ft_strcmp(sub, "C")) && k < 6)
		check_elem_and_value_help(sub, k, value, list);
	else if (ft_strcmp(sub, "NO")
		&& ft_strcmp(sub, "EA") && ft_strcmp(sub, "WE")
		&& ft_strcmp(sub, "SO") && ft_strcmp(sub, "F") && ft_strcmp(sub, "C"))
		error("Error\n");
	free(value);
	k++;
}
