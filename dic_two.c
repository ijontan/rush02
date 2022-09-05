/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dic_two.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 18:49:10 by itan              #+#    #+#             */
/*   Updated: 2022/09/04 19:08:29 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush02.h"

char	*cr8_1d_arr(unsigned int len)
{
	char	*bf;

	bf = (char *)malloc(sizeof(char) * (len + 1));
	if (!(bf))
		ft_error();
	bf[len] = '\0';
	return (bf);
}

char	**cr8_2d_arr(unsigned int row)
{
	char	**a_output;

	a_output = (char **)malloc(sizeof(char *) * (row + 1));
	if (!(a_output))
		ft_error();
	a_output[row] = 0;
	return (a_output);
}

char	**dic_value(char *file, int row, unsigned int len, unsigned int r)
{
	char			**a_output;
	char			*bf;
	int				fd;
	unsigned int	i;

	a_output = cr8_2d_arr(row);
	bf = cr8_1d_arr(len);
	i = 0;
	fd = open(file, O_RDONLY);
	read(fd, bf, len);
	while (*(bf + i) != '\0')
	{
		while (*(bf + i) != '\0' && !ft_in_str(*(bf + i), ":"))
			i++;
		i++;
		while (*(bf + i) != '\0' && (*(bf + i) <= 32 || *(bf + i) > 126))
			i++;
		a_output[r++] = ft_dup_while_printable(bf + i);
		while (*(bf + i) != '\0' && !ft_in_str(*(bf + i), "\n"))
			i++;
	}
	close(fd);
	free(bf);
	return (a_output);
}

char	**dic_key(char *file, int row, unsigned int len, unsigned int r)
{
	char			**a_output;
	char			*bf;
	int				fd;
	unsigned int	i;

	a_output = cr8_2d_arr(row);
	bf = cr8_1d_arr(len);
	i = 0;
	fd = open(file, O_RDONLY);
	read(fd, bf, len);
	while (*(bf + i) != '\0')
	{
		while (*(bf + i) != '\0' && !ft_in_str(*(bf + i), "0123456789"))
			i++;
		a_output[r++] = ft_dup_while_num(bf + i);
		while (*(bf + i) != '\0' && !ft_in_str(*(bf + i), "\n"))
			i++;
	}
	close(fd);
	free(bf);
	return (a_output);
}
