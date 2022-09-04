#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_map
{
	char	**a_d;
	char	**a_w;
}			t_map;
/*********************** BASIC STRING FUNCTIONS ***********************/
void	ft_putchar(char a)
{
	write(1, &a, 1);
}

void	ft_putstr(char *str)
{
	while (*str != '\0')
	{
		ft_putchar(*str);
		str++;
	}
}

int	ft_in_str(char c, char *str)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

int	ft_str_is_numeric(char *str)
{
	if (*str == '\0')
		return (1);
	while (*str)
	{
		if (!(*str >= 48 && *str <= 57))
			return (0);
		str++;
	}
	return (1);
}

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

/*********************** OPERATIONS FUNCTIONS ***********************/

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

/*********************** DICTIONARY STORAGE FUNCTIONS ***********************/
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

/*********************** DICTIONARY VALUE FUNCTIONS ***********************/
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

/* char	*dict_get_digit_from_word(char **a_key, char **a_value, char *value)
{
	int		i;
	char	*output;

	i = 0;
	while (a_value[i] != 0)
	{
		if (ft_strcmp(a_value[i], value) == 0)
			return (a_key[i]);
		i++;
	}
	return (0);
} */
/*********************** NUMBER PROCESSING FUNCTION ***********************/
char	*d_tenn(int n)
{
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
	int	region_position;

	region_position = ((cd - 1) / 3) * 3 + 1;
	while (region_position < (cd / 3 + 1) * 3 + 1)
	{
		if (nb[nod - region_position] <= '9' && nb[nod
			- region_position] >= '1')
			return (1);
		region_position++;
	}
	return (0);
}
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

/*********************** MAIN PRINTWORDS FUNCTION ***********************/
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
