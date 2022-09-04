/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dic_one.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 18:48:17 by itan              #+#    #+#             */
/*   Updated: 2022/09/04 18:55:11 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush02.h"

void	dict_free_2d_array(char **array)
{
	unsigned int	i;

	i = 0;
	while (ft_strcmp(array[i], "\0") != 0)
	{
		free(array[i]);
		i++;
	}
	free(array[i]);
	free(array);
}

void	dict_get_largest_len_row(char *file, int *maxstrlen, int *maxrow)
{
	int		fd;
	char	buffer;
	int		len;
	int		row;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_dict_error();
	row = 0;
	len = 0;
	while (read(fd, &buffer, 1))
	{
		len++;
		if (buffer == '\n')
			row++;
	}
	*maxstrlen = len;
	if (buffer == '\n')
		*maxrow = row;
	else
		*maxrow = row + 1;
	close(fd);
}
