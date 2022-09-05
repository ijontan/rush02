/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush02.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 14:43:16 by jngerng           #+#    #+#             */
/*   Updated: 2022/09/04 19:07:00 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUSH02_H
# define RUSH02_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_map
{
	char	**a_d;
	char	**a_w;
}			t_map;

void		ft_putchar(char a);
void		ft_putstr(char *str);
int			ft_in_str(char c, char *str);
int			ft_str_is_numeric(char *str);
int			ft_strlen_char(char *str, char sep);
int			ft_strlen(char *str);
char		*ft_dup_while_num(char *str);
char		*ft_dup_while_printable(char *str);
int			ft_strcmp(char *s1, char *s2);
void		ft_error(void);
void		ft_dict_error(void);
void		dict_free_2d_array(char **array);
void		dict_get_largest_len_row(char *file, int *maxstrlen, int *maxrow);
char		*cr8_1d_arr(unsigned int len);
char		**cr8_2d_arr(unsigned int row);
char		**dic_value(char *file, int row, unsigned int len, unsigned int r);
char		**dic_key(char *file, int row, unsigned int len, unsigned int r);
char		*get_word(char **a_key, char **a_value, char *key);
char		*d_tenn(int n);
char		*d_n(int n);
char		*d_teen(int n);
char		*d_tyn(int n);
int			region_has_value(char *nb, int cd, int nod);
int			check_only_zero(char *nb);
void		print_first_region(t_map map, char *nb, int cd, int nod);
void		print_second_region(t_map map, char *nb, int cd, int nod);
void		print_third_region(t_map map, char *nb, int cd, int nod);
void		str_to_word(t_map map, char *nb);
void		t_printwords(char *file, char *str);

#endif