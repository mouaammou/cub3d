/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rennacir <rennacir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:04:50 by rennacir          #+#    #+#             */
/*   Updated: 2023/09/26 15:26:04 by rennacir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	lens1;
	int		i;
	int		j;
	char	*str;

	if (!s1)
		s1 = ft_strdup("");
	i = 0;
	j = 0;
	lens1 = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(lens1 + 1);
	if (!str)
		return (NULL);
	while (s1[j])
		str[i++] = s1[j++];
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	free(s2);
	return (str);
}

char	*ft_strdup(char *s1)
{
	size_t	len;
	char	*s;
	char	*t;
	size_t	i;

	i = 0;
	len = ft_strlen(s1);
	s = malloc(len + 1);
	if (!s)
		return (NULL);
	t = s;
	while (i < len)
	{
		*s = *s1;
		s++;
		s1++;
		i++;
	}
	*s = '\0';
	return (t);
}
