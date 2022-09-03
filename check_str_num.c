/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_str_num.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 20:06:23 by jngerng           #+#    #+#             */
/*   Updated: 2022/09/03 20:11:53 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// to check whether the argument to be converted is a valid number
// etc no space , alphabet ...

void	check_str_num(char *str)
{
	while(*str)
	{
		if(*str >= '0' && *str <= '9')
			str ++;
		else
			return (0);
	}
	return (1);
}
