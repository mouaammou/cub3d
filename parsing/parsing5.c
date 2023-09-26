/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennacir <rennacir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:22:02 by rennacir          #+#    #+#             */
/*   Updated: 2023/09/26 19:39:39 by rennacir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	check_elements_help(char *m, int *player)
{
	int	j;

	j = 0;
	while (m[j])
	{
		if (m[j] != '0' && m[j] != ' ' && m[j] != '1'
			&& m[j] != 'N' && m[j] != 'W' && m[j] != 'S' && m[j] != 'E' )
			error("Error : foreign element detected\n");
		if (m[j] == 'N' || m[j] == 'W' || m[j] == 'E' || m[j] == 'S')
			(*player)++;
		j++;
	}
}

void	check_elements(char **m)
{
	int	i;
	int	player;

	i = 0;
	player = 0;
	while (m[i])
	{
		check_elements_help(m[i], &player);
		i++;
	}
	if (player != 1)
		error("Error : an error occured considering player\n");
}

void	check_middle_lines_help(char **m, int *i)
{
	int	j;

	while (m[(*i)] && m[(*i) + 1] && !line_of_white_spaces(m[(*i) + 1]))
	{
		j = 0;
		while (m[(*i)][j] && m[(*i)][j] == ' ')
			j++;
		if (m[(*i)][j] != '1')
			error("Error : map is not close\n");
		j++;
		while (m[(*i)][j] && m[(*i)][j + 1])
		{
			if (m[(*i)][j] == '0' || m[(*i)][j] == 'N')
			{
				if (!check_four_sides(m, *i, j))
					error("Error : map is not close\n");
			}
			j++;
		}
		if (m[(*i)][j] != '1' && m[(*i)][j] != ' ')
			error("Error : map is not close4\n");
		(*i)++;
	}
}

void	check_middle_lines(char **m)
{
	int		i;

	i = 1;
	check_middle_lines_help(m, &i);
	check_first_and_last_line(m[i]);
	i++;
	while (m[i] && line_of_white_spaces(m[i]))
		i++;
	if (m[i])
		error("Error : considering map\n");
}

void	pars_map(t_list *list, char **map)
{
	int		i;
	int		count;
	char	**m;

	i = 0;
	while (map[i])
		i++;
	list->map = malloc (sizeof(char *) * (i + 1));
	if (!list->map)
		return ;
	i = -1;
	while (map[++i])
		list->map[i] = ft_strdup(map[i]);
	list->map[i] = NULL;
	count = count_max_size(list->map);
	m = join_line_with_spaces(list->map, count);
	i = 0;
	check_elements(m);
	check_first_and_last_line(m[i]);
	check_middle_lines(m);
	free_2d_tab(list->map);
	list->map = m;
}
