/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esirnio <esirnio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 16:34:55 by esirnio           #+#    #+#             */
/*   Updated: 2022/03/17 14:27:30 by esirnio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	map_size(char *file, int *c, int *r)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(file, O_RDONLY);
	*c = 0;
	*r = 0;
	i = 0;
	while (get_next_line(fd, &line))
	{
		if (*c == 0)
		{
			while (line[i])
			{
				if (line[i] == ' ' || (i != 0 && line [i - 1] != ' '))
				{
					i++;
					continue ;
				}
				i++;
				(*c)++;
			}
		}
		(*r)++;
		free(line);
	}
	close(fd);
}

void	read_file(char *file, t_fdf *data)
{
	int		fd;
	char	*line;
	char	**split;
	int		i;
	int		j;

	fd = open(file, O_RDONLY);
	data->arr = (int *)malloc(sizeof(int) * data->amount_points);
	ft_bzero(data->arr, (sizeof(int) * data->amount_points));
	i = 0;
	j = 0;
	while (get_next_line(fd, &line))
	{
		split = ft_strsplit(line, ' ');
		free(line);
		while (split[j])
		{
			data->arr[i] = ft_atoi(split[j]);
			i++;
			j++;
		}
		j = 0;
	}
	ft_free_array(split);
	close(fd);
}
