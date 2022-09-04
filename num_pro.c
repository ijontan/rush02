/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_pro.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 18:51:09 by itan              #+#    #+#             */
/*   Updated: 2022/09/04 18:54:58 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush02.h"

char	*d_tenn(int n)
{
	char	*output;

	if (n <= 0)
		return (0);
	else if (n == 1)
		return ("1");
	else
	{
		output = (char *)malloc(sizeof(char) * (n + 1));
		if (!(output))
			return (NULL);
		output[n] = '\0';
		output[0] = '1';
		n--;
		while (n > 0)
		{
			output[n] = '0';
			n--;
		}
		return (output);
	}
}
char	*d_n(int n)
{
	char	*output;

	output = (char *)malloc(sizeof(char) * (2));
	if (n < 0)
		return (0);
	output[0] = n + 48;
	output[1] = '\0';
	return (output);
}

char	*d_teen(int n)
{
	char	*output;

	output = (char *)malloc(sizeof(char) * (3));
	if (n > 0 && n < 10)
	{
		output[0] = '1';
		output[1] = (n % 10) + 48;
		output[2] = '\0';
	}
	return (output);
}
char	*d_tyn(int n)
{
	char	*output;

	output = (char *)malloc(sizeof(char) * (3));
	if (n > 0 && n < 10)
	{
		output[1] = '0';
		output[0] = n + 48;
		output[2] = '\0';
	}
	return (output);
}
int	region_has_value(char *nb, int cd, int nod)
{
	int	region_p;

	region_p = ((cd - 1) / 3) * 3 + 1;
	while (region_p < (cd / 3 + 1) * 3 + 1)
	{
		if (nb[nod - region_p] <= '9' && nb[nod - region_p] >= '1')
			return (1);
		region_p++;
	}
	return (0);
}
