/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 18:53:56 by itan              #+#    #+#             */
/*   Updated: 2022/09/04 18:54:12 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush02.h"

void	t_printwords(char *file, char *str)
{
	int				maxstrlen;
	int				maxrow;
	unsigned int	r;
	t_map			map;

	dict_get_largest_len_row(file, &maxstrlen, &maxrow);
	r = 0;
	map.a_d = dic_key(file, maxrow, maxstrlen, r);
	map.a_w = dic_value(file, maxrow, maxstrlen, r);
	str_to_word(map, str);
	dict_free_2d_array(map.a_d);
	dict_free_2d_array(map.a_w);
}

int	main(int argc, char **argv)
{
	if (!(argc == 2 || argc == 3))
		ft_error();
	if (argc == 3)
	{
		t_printwords(argv[1], argv[2]);
	}
	else if (argc == 2)
	{
		t_printwords("numbers.dict", argv[1]);
	}
	return (0);
}
