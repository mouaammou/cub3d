/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennacir <rennacir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:16:37 by rennacir          #+#    #+#             */
/*   Updated: 2023/09/26 17:34:48 by rennacir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_list	*create_and_initialize_list(void)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->map = NULL;
	list->NO = NULL;
	list->SO = NULL;
	list->EA = NULL;
	list->WE = NULL;
	list->C = -1;
	list->F = -1;
	list->num_col = -1;
	list->num_row = -1;
	list->win_height = -1;
	list->win_height = -1;
	return (list);
}

int	line_of_white_spaces(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

char	*get_value_of_elmnts(char *line, int j)
{
	int		start;
	char	*sub;

	while (line[j] && line[j] == ' ')
		j++;
	if (!line[j])
		error("Error : a value is missing\n");
	start = j;
	while (line[j] && line[j] != ' ')
		j++;
	sub = ft_substr(line, start, j - start);
	while (line[j] && line[j] == ' ')
		j++;
	if (line[j])
		error("Error : check the value of first elements\n");
	return (sub);
}

void	check_is_digit(char *s)
{
	int	i;

	i = 0;
	if (ft_atoi(s) > 255 || ft_atoi(s) < 0
		|| ft_atoi(s) > 2147483647 || ft_atoi(s) < -2147483648)
		error("Error : about F or C element\n");
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			error("Error : about F or C element\n");
		i++;
	}
}

void	check_f_and_c(char *value)
{
	char	**split;
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (value[i])
	{
		if (value[i] == ',')
			count++;
		i++;
	}
	if (count != 2)
		error("Error : about F or C element\n");
	split = ft_split(value, ',');
	i = 0;
	while (split[i])
	{
		check_is_digit(split[i]);
		i++;
	}
	free_2d_tab(split);
	if (i != 3)
		error("Error : about F or C element\n");
}
