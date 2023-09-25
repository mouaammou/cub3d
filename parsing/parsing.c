/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennacir <rennacir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 22:57:16 by rennacir          #+#    #+#             */
/*   Updated: 2023/09/25 23:13:02 by rennacir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	check_number_of_args(int argc)
{
	if (argc != 2)
		error("Error : Please Check number of arguments\n");
}

void	check_extension(char **argv)
{
	char *extension;
	extension = argv[1] + ft_strlen(argv[1]) - 4;
	if (ft_strcmp(extension, ".cub"))
		error("Error : Please Check the extension\n");
}

char **read_map(char **argv, int count)
{
	char	**map;
	char	*gnl;
	int		fd;
	int		i;

	i = 0;
	fd = open (argv[1], O_RDONLY);
	if (fd < 0)
		error("Error : Please choose an existing map\n");
	map = malloc(sizeof(char *) * (count + 1));
	if (!map)
		return (NULL);
	gnl = get_next_line(fd);
	while(gnl)
	{
		map[i] = ft_strdup(gnl);
		free(gnl);
		i++;
		gnl = get_next_line(fd);
	}
	map[i] = NULL;
	return (map);
}

int	count_lines(int fd)
{
	char	*gnl;
	int		count;

	count = 0;
	gnl = get_next_line(fd);
	while (gnl)
	{
		count++;
		free(gnl);
		gnl = get_next_line(fd);
	}
	return (count);
}

char **get_map(char **argv)
{
	int		fd;
	int		count;
	char	**map;
	count = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		error("Error : Please choose an existing map\n");
	count = count_lines(fd);
	close(fd);
	map = read_map(argv, count);
	return (map);
}

t_list	*create_and_initialize_list()
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
	int i = 0;

	while (s[i])
	{
		if (s[i] != ' ')
			return 0;
		i++;
	}
	return 1;
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
	sub = ft_substr(line, start , j - start);
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
	if (ft_atoi(s) > 255 || ft_atoi(s) < 0 || ft_atoi(s) > 2147483647 || ft_atoi(s) < -2147483648)
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
	if (i != 3)
		error("Error : about F or C element\n");
	free_2d_tab(split);
}

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
	val = create_trgb(0, ft_atoi(split[0]), ft_atoi(split[1]), ft_atoi(split[2]));
	free_2d_tab(split);
	return val;
}

void	check_elem_and_value(char *line, char *sub, int j, t_list *list)
{
	char	*value;
	static int k;
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
	return count;
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
	return res;
}

char **join_line_with_spaces(char **map, int count)
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
			m[j++] = ft_strjoin(ft_strdup(map[i]), al_spaces(count - ft_strlen(map[i])));
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
	while(s[i])
	{
		if(s[i] != '1' && s[i] != ' ')
			error("Error : map is not close1\n");
		i++;
	}
}

void	check_elements(char **m)
{
	int	i;
	int	j;
	int	player;

	i = 0;
	j = 0;
	player = 0;
	while (m[i])
	{
		j = 0;
		while (m[i][j])
		{
			if (m[i][j] != '0' && m[i][j] != ' ' && m[i][j] != '1'
				&& m[i][j] != 'N' && m[i][j] != 'W' && m[i][j] != 'S' && m[i][j] != 'E' )
				error("Error : foreign element detected\n");
			if (m[i][j] == 'N' || m[i][j] == 'W' || m[i][j] == 'E' || m[i][j] == 'S')
				player++;
			j++;
		}
		i++;
	}
	if (player != 1)
		error("Error : an error occured considering player\n");
}

int	check_four_sides(char **map, int i, int j)
{
	if (map[i][j - 1] == ' ' || map[i][j + 1] == ' '
		|| map[i - 1][j] == ' ' || map[i + 1][j] == ' ')
			return 0;
	return 1;
}


void	check_middle_lines(char **m)
{
	int		i;
	int		j;

	i = 1;
	while (m[i] && m[i + 1] && !line_of_white_spaces(m[i + 1]))
	{
		j = 0;
		while(m[i][j] && m[i][j] == ' ')
			j++;
		if (m[i][j] != '1')
			error("Error : map is not close2\n");
		j++;
		while(m[i][j] && m[i][j + 1])
		{
			if (m[i][j] == '0' || m[i][j] == 'N')
			{
				if (!check_four_sides(m, i, j))
					error("Error : map is not close3\n");
			}
			j++;
		}
		if (m[i][j] != '1' &&  m[i][j] != ' ')
			error("Error : map is not close4\n");
		i++;
	}
	check_first_and_last_line(m[i]);
	i++;
	while (m[i] && line_of_white_spaces(m[i]))
		i++;
	if (m[i])
		error("an error occured considering map\n");
}


void	pars_map(t_list *list, char **map)
{
	int i = 0;
	int	count;
	char **m;
	while (map[i])
		i++;
	list->map  = malloc (sizeof(char *) * (i + 1));
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

void	fill_struct(char **argv, t_list *list)
{
	char **g_map;
	int i = 0;
	int j = 0;
	int start;
	char	*sub;
	int	k;

	k = 0;
	g_map = get_map(argv);
	while (g_map[i])
	{
		j = 0;
		if (!ft_strcmp(g_map[i], "") || line_of_white_spaces(g_map[i]))
		{
			i++;
			continue;
		}
		while (g_map[i][j] && g_map[i][j] == ' ')
			j++;
		start = j;
		while(g_map[i][j] && g_map[i][j] != ' ')
			j++;
		sub = ft_substr(g_map[i], start, j - start);
		check_elem_and_value(g_map[i], sub, j, list);
		i++;
		k++;
		free(sub);
		if (k >= 6)
			break;
	}
	while (g_map[i] && (!ft_strcmp(g_map[i], "") || line_of_white_spaces(g_map[i])))
		i++;
	pars_map(list, g_map + i);
	free(g_map);
}

int	*return_dim(char **map)
{
	int	row;
	int	col;
	int	*dim;

	row = 0;
	dim = NULL;
	dim = malloc(8);
	while (map[row])
	{
		col = 0;
		while (map[row][col])
		{
			if (map[row][col] == 'N' || map[row][col] == 'S'
				|| map[row][col] == 'E' || map[row][col] == 'W')
			{
				dim[0] = row;
				dim[1] = col;
				return (dim);
			}
			col++;
		}
		row++;
	}
	return (dim);
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
}

void	free_list(t_list *list)
{
	free_2d_tab(list->map);
	free(list->NO);
	free(list->WE);
	free(list->EA);
	free(list->SO);
	free(list);
}

t_list	*parsing(int argc, char **argv)
{
	t_list *list;

	check_number_of_args(argc);
	check_extension(argv);
	list = create_and_initialize_list();
	fill_struct(argv, list);
	continue_filling_struct(list);
	return(list);
}
