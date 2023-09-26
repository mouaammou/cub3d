/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennacir <rennacir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 22:57:16 by rennacir          #+#    #+#             */
/*   Updated: 2023/09/26 19:38:51 by rennacir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*fill_struct_help_help(char *g_map, int *j)
{
	int		start;
	char	*sub;

	while (g_map[(*j)] && g_map[(*j)] == ' ')
		(*j)++;
	start = (*j);
	while (g_map[(*j)] && g_map[(*j)] != ' ')
		(*j)++;
	sub = ft_substr(g_map, start, (*j) - start);
	return (sub);
}

void	fill_struct_help(t_list *list, char **g_map, int *i)
{
	int		k;
	int		j;
	char	*sub;

	k = 0;
	while (g_map[(*i)])
	{
		j = 0;
		if (!ft_strcmp(g_map[(*i)], "") || line_of_white_spaces(g_map[(*i)]))
		{
			(*i)++;
			continue ;
		}
		sub = fill_struct_help_help(g_map[(*i)], &j);
		check_elem_and_value(g_map[(*i)], sub, j, list);
		(*i)++;
		k++;
		free(sub);
		if (k >= 6)
			break ;
	}
}

void	fill_struct(char **argv, t_list *list)
{
	char	**g_map;
	int		i;

	i = 0;
	g_map = get_map(argv);
	fill_struct_help(list, g_map, &i);
	while (g_map[i] && (!ft_strcmp(g_map[i], "")
			|| line_of_white_spaces(g_map[i])))
		i++;
	pars_map(list, g_map + i);
	free_2d_tab(g_map);
}

void	continue_filling_struct(t_list *list)
{
	int	i;
	int	*dem;

	i = 0;
	list->num_col = ft_strlen(list->map[0]);
	while (list->map[i])
		i++;
	list->num_row = i;
	list->win_height = list->num_row * TILE_SIZE;
	list->win_width = list->num_col * TILE_SIZE;
	dem = return_dim(list->map);
	list->player_x = dem[0];
	list->player_y = dem[1];
	free(dem);
}

t_list	*parsing(int argc, char **argv)
{
	t_list	*list;

	check_number_of_args(argc);
	check_extension(argv);
	list = create_and_initialize_list();
	fill_struct(argv, list);
	continue_filling_struct(list);
	return (list);
}
