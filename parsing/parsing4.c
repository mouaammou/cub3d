/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennacir <rennacir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:21:21 by rennacir          #+#    #+#             */
/*   Updated: 2023/09/26 18:07:44 by rennacir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	count_max_size(char **map)
{
	int	count;
	int	i;

	i = 0;
	if (!map || !map[i])
		return (0);
	count = ft_strlen(map[i]);
	i++;
	while (map && map[i])
	{
		if (count < (int)ft_strlen(map[i]))
			count = ft_strlen(map[i]);
		i++;
	}
	return (count);
}

char	*al_spaces(int len)
{
	char	*res;
	int		i;

	i = 0;
	res = malloc (len + 1);
	if (!res)
		return (NULL);
	while (i < len)
	{
		res[i] = ' ';
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	**join_line_with_spaces(char **map, int count)
{
	int		i;
	int		j;
	char	**m;

	i = 0;
	j = 0;
	while (map[i])
		i++;
	m = malloc (sizeof(char *) * (i + 1));
	if (!m)
		return (NULL);
	i = 0;
	while (map[i])
	{
		if ((int)ft_strlen(map[i]) == count)
			m[j++] = ft_strdup(map[i]);
		else
			m[j++] = ft_strjoin(ft_strdup(map[i]),
					al_spaces(count - ft_strlen(map[i])));
		i++;
	}
	m[j] = NULL;
	return (m);
}

void	check_first_and_last_line(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] == ' ')
		i++;
	while (s[i])
	{
		if (s[i] != '1' && s[i] != ' ')
			error("Error : map is not close1\n");
		i++;
	}
}
