/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 18:49:54 by itan              #+#    #+#             */
/*   Updated: 2022/09/04 18:55:02 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush02.h"

char	*get_word(char **a_key, char **a_value, char *key)
{
	int	i;

	i = 0;
	while (a_key[i] != 0)
	{
		if (ft_strcmp(a_key[i], key) == 0)
			return (a_value[i]);
		i++;
	}
	return (0);
}

char	*dict_get_digit_from_word(char **a_key, char **a_value, char *value)
{
	int i;

	i = 0;
	while (a_value[i] != 0)
	{
		if (ft_strcmp(a_value[i], value) == 0)
			return (a_key[i]);
		i++;
	}
	return (0);
}