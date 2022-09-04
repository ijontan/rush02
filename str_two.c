/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_two.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 18:45:00 by itan              #+#    #+#             */
/*   Updated: 2022/09/04 18:54:41 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush02.h"

int	ft_strlen_char(char *str, char sep)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != sep)
		i++;
	return (i);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_dup_while_num(char *str)
{
	int		len;
	char	*output;
	int		i;

	len = 0;
	while (ft_in_str(str[len], "0123456789"))
		len++;
	output = (char *)malloc(sizeof(char) * (len + 1));
	if (!(output))
		return (NULL);
	output[len] = '\0';
	i = 0;
	while (i < len)
	{
		output[i] = str[i];
		i++;
	}
	return (output);
}

char	*ft_dup_while_printable(char *str)
{
	int		len;
	char	*output;
	int		i;

	len = 0;
	while (str[len] >= 32 && str[len] <= 126)
		len++;
	output = (char *)malloc(sizeof(char) * (len + 1));
	if (!(output))
		return (NULL);
	output[len] = '\0';
	i = 0;
	while (i < len)
	{
		output[i] = str[i];
		i++;
	}
	return (output);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}
