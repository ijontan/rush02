/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_one.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 18:47:11 by itan              #+#    #+#             */
/*   Updated: 2022/09/04 18:54:52 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush02.h"

void	ft_error(void)
{
	ft_putstr("Error\n");
	exit(1);
}

void	ft_dict_error(void)
{
	ft_putstr("Dict Error\n");
	exit(1);
}

void	ft_dev_error(char *str)
{
	ft_putstr(str);
	exit(1);
}

int	ft_2darray_len(char **str)
{
	int	i;

	i = 0;
	while (ft_strcmp(str[i], "\0") != 0)
	{
		i++;
	}
	return (i);
}
