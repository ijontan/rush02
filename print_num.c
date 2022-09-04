/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 18:52:26 by itan              #+#    #+#             */
/*   Updated: 2022/09/04 18:54:47 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush02.h"

int	check_only_zero(char *nb)
{
	while (*nb)
		if (*nb++ != '0')
			return (0);
	return (1);
}
void	print_first_region(t_map map, char *nb, int cd, int nod)
{
	if (cd % 3 == 1)
	{
		if (nb[nod - cd - 1] == '1')
			ft_putstr(get_word(map.a_d, map.a_w, d_teen(nb[nod - cd] - 48)));
		if (nb[nod - cd - 1] != '0' && nb[nod - cd - 2] != '0')
			ft_putchar(' ');
		if (cd / 3 > 0)
			ft_putstr(get_word(map.a_d, map.a_w, d_tenn(cd)));
		if (nb[nod - cd - 1] != '0')
			ft_putchar(' ');
	}
}
void	print_second_region(t_map map, char *nb, int cd, int nod)
{
	if (cd % 3 == 2 && nb[nod - cd] != '0')
	{
		if (!(nb[nod - cd] == '1' && nb[nod - cd + 1] != '0'))
		{
			ft_putstr(get_word(map.a_d, map.a_w, d_tyn(nb[nod - cd] - 48)));
			if (nb[nod - cd + 1] != '0')
				ft_putchar(' ');
		}
	}
}
void	print_third_region(t_map map, char *nb, int cd, int nod)
{
	if (cd % 3 == 0 && nb[nod - cd] != '0')
	{
		ft_putchar(' ');
		ft_putstr(get_word(map.a_d, map.a_w, "100"));
		ft_putchar(' ');
		if (nb[nod - cd + 1] != '0' || nb[nod - cd + 2] != '0')
			ft_putstr("and ");
	}
}

void	str_to_word(t_map map, char *nb)
{
	int	cd;
	int	nod;

	nod = ft_strlen(nb);
	if (nod > 39)
		ft_error();
	if (check_only_zero(nb))
	{
		ft_putstr(get_word(map.a_d, map.a_w, "0"));
		return ;
	}
	cd = nod;
	while (cd > 0 && nb[nod - cd] != 0)
	{
		if (!(cd % 3 == 1 && nb[nod - cd - 1] == '1'))
			if (cd % 3 != 2 && nb[nod - cd] != '0')
				ft_putstr(get_word(map.a_d, map.a_w, d_n(nb[nod - cd] - 48)));
		if (region_has_value(nb, cd, nod))
		{
			print_first_region(map, nb, cd, nod);
			print_second_region(map, nb, cd, nod);
			print_third_region(map, nb, cd, nod);
		}
		cd--;
	}
}
