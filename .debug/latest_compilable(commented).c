/*
EASILY COMPILABLE VERSION TO RUN DEBUGGING ON & TO EXPLAIN TO TEAMMATES.
*/

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
typedef struct s_map
{
	char	**a_digits;
	char	**a_words;
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

/*char	*ft_dup_until_char(char *str, char c)
{
	int 	len;
	char	*output;
	int		i;

	//Get length, how far are we copying
	len = ft_strlen_char(str, c);

	//Dedicate a heap memory - malloc for this array
	output = (char *)malloc(sizeof(char) * (len + 1));
	if (!(output))
		return (NULL);
	output[len] = '\0'; //Terminate string at last digit

	//Now, store what we have
	i = 0;
	while (i < len)
	{
		output[i] = str[i];
		i++;
	}
	
	//Return our string
	return (output);
}*/

char	*ft_dup_while_num(char *str)
{
	int 	len;
	char	*output;
	int		i;

	//Get length, how far are we copying
	len = 0;
	while (ft_in_str(str[len], "0123456789"))
		len++;

	//Dedicate a heap memory - malloc for this array
	output = (char *)malloc(sizeof(char) * (len + 1));
	if (!(output))
		return (NULL);
	output[len] = '\0'; //Terminate string at last digit

	//Now, store what we have
	i = 0;
	while (i < len)
	{
		output[i] = str[i];
		i++;
	}
	
	//Return our string
	return (output);
}

char	*ft_dup_while_printable(char *str)
{
	int 	len;
	char	*output;
	int		i;

	//Get length, how far are we copying
	len = 0;
	while (str[len] >= 32 && str[len] <= 126)
		len++;

	//Dedicate a heap memory - malloc for this array
	output = (char *)malloc(sizeof(char) * (len + 1));
	if (!(output))
		return (NULL);
	output[len] = '\0'; //Terminate string at last digit

	//Now, store what we have
	i = 0;
	while (i < len)
	{
		output[i] = str[i];
		i++;
	}
	
	//Return our string
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

/* 
//IF RUN INTO ERROR DURING COMPILATION TIME - CAN USE THIS TO CREATE BLANK STRING
//WHERE I RETURNED NULL, WHEN NEED A STRING
char *empty_freeable_string(void)
{
	char *string;

	string = (char *)malloc(sizeof(char));
	if (!string)
		return (NULL);
	string[0] = 0;
	return (string);
}
//NEED TO REMEMBER TO FREE THOUGH. HMM
*/

/*********************** OPERATIONS FUNCTIONS ***********************/

void	ft_error(void)
{
	ft_putstr("Error\n");  //Requested by pdf, write Error when it crash
	exit(1);  //This is a built in function to terminate, and throw 1 to show that it has error
}

void	ft_dict_error(void)  //PDF says another set of 'Dict Error'
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
	int i;

	i = 0;
	while (ft_strcmp(str[i],"\0") != 0)
	{
		i++;
	}
	return (i);
}

/*********************** DICTIONARY STORAGE FUNCTIONS ***********************/
void dict_free_2d_array(char **array)
{
	unsigned int i;

	i = 0;
	while (ft_strcmp(array[i],"\0") != 0)
	{
		// printf("%d Attempt free %p - %s\n", i, &array[i], array[i]);
		free(array[i]);
		i++;
	} 
	// printf("%d Attempt free null %p - %s\n", i, &array[i], "null itself");
	free(array[i]);
	// printf("Attempt free 2D array itself %p - %s\n", array, "2D array itself");
	free(array);
}

void	dict_get_largest_len_row(char *file, int *maxstrlen, int *maxrow)
{
	int		fd;
	char 	buffer;
	int 	len;
	int		row;

	//Attempt to read file
	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_dict_error();
	row = 0;  //Get max rows/input from dictionary
	len = 0;  //Get max length of either left/right
	
	//Read will loop through things char by char, while still got data = 1; if reached end = 0;
	while (read(fd, &buffer, 1))
	{
		len++;  //Save down how many extra characters there are
		if (buffer == '\n')  //Progress rows if there's line break
			row++;
	}
	*maxstrlen = len;

	//See if the whole dict ended with or without nextline '\n'
	if (buffer == '\n')
		*maxrow = row;  //If we're at next line - means it terminated with \n
	else 
		*maxrow = row + 1;  // + 1 because last row no \n
	//Before exiting, we close file
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

char	**dict_store_array_value(char *file, int row, unsigned int len)
{
	char			**a_output;
	char			*bf;
	int				fd;
	unsigned int	i;
	unsigned int	r;

	a_output = cr8_2d_arr(row);
	bf = cr8_1d_arr(len);
	i = 0;
	r = 0;
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


char	**dict_store_array_key(char *file, int row, unsigned int len)
{
	char			**a_output;
	char			*bf;
	int				fd;
	unsigned int	i;
	unsigned int	r;

	a_output = cr8_2d_arr(row);
	bf = cr8_1d_arr(len);
	i = 0;
	r = 0;
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
char *dict_get_word_from_digit(char **a_key, char **a_value, char *key)
{
	int i;

	i = 0;
	while (a_key[i] != 0)
	{
		if (ft_strcmp(a_key[i], key) == 0)
			return (a_value[i]);
		i++;
	}
	return (0); //If nothing is found
}

char *dict_get_digit_from_word(char **a_key, char **a_value, char *value)
{
	int i;

	i = 0;
	while (a_value[i] != 0)
	{
		if (ft_strcmp(a_value[i], value) == 0)
			return (a_key[i]);
		i++;
	}
	return (0); //If nothing is found
}

/*********************** NUMBER PROCESSING FUNCTION ***********************/
char	*get_10n_via_digit(int n)
{
	char	*output;

	if (n <= 0) //If no zeros to create
		return (0);
	else if (n == 1) //If only one digit
		return ("1");
	else
	{
		//If got more than one...
		output = (char *)malloc(sizeof(char) * (n + 1));
		if (!(output))
			return (NULL);
		output[n] = '\0'; //terminate the string
		output[0] = '1';  //Start with 1
		n--;              //Move to previous digit
		while (n > 0)
		{
			output[n] = '0';
			n--;
		}
		//After adding all digits, we return output
		return (output);
	}
}
char	*get_n_via_digit(int n)
{
	char	*output;

	output = (char *)malloc(sizeof(char) * (2));
	if (n < 0) //If no zeros to create
		return (0);
	output[0] = n + 48;
	output[1] = '\0';
	return (output);
}

char	*get_teenn_via_digit(int n)
{
	char	*output;

	output = (char *)malloc(sizeof(char) * (3));
	if (n > 0 && n < 10) //If no zeros to create
	{
		output[0] = '1';
		output[1] = (n % 10) + 48;
		output[2] = '\0';
	}
	return (output);
}
char	*get_tyn_via_digit(int n)
{
	char	*output;

	output = (char *)malloc(sizeof(char) * (3));
	if (n > 0 && n < 10) //If no zeros to create
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
	//starting position of the rigion checking
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
			ft_putstr(dict_get_word_from_digit(map.a_digits,
												map.a_words,
												get_teenn_via_digit(nb[nod - cd]
														- 48)));
		if (nb[nod - cd - 1] != '0' && nb[nod - cd - 2] != '0')
			ft_putchar(' ');
		if (cd / 3 > 0)
			ft_putstr(dict_get_word_from_digit(map.a_digits,
												map.a_words,
												get_10n_via_digit(cd)));
		if (nb[nod - cd - 1] != '0')
			ft_putchar(' ');
	}
}
void	print_second_region(t_map map, char *nb, int cd, int nod)
{
	if (cd % 3 == 2 && nb[nod - cd] != '0' && !(nb[nod - cd] == '1' && nb[nod
			- cd + 1] != '0'))
	{
		ft_putstr(dict_get_word_from_digit(map.a_digits, map.a_words,
					get_tyn_via_digit(nb[nod - cd] - 48)));
		if (nb[nod - cd + 1] != '0')
			ft_putchar(' ');
	}
}
void	print_third_region(t_map map, char *nb, int cd, int nod)
{
	if (cd % 3 == 0 && nb[nod - cd] != '0')
	{
		ft_putchar(' ');
		ft_putstr(dict_get_word_from_digit(map.a_digits, map.a_words, "100"));
		ft_putchar(' ');
		if (nb[nod - cd + 1] != '0' || nb[nod - cd + 2] != '0')
			ft_putstr("and ");
	}
}

void	str_to_word(t_map map, char *nb)
{
	int cd;  //currnt digits
	int nod; //total number of digits
	//(nod - cd) will be the index of current digit checking
	nod = ft_strlen(nb); //counting number of digits
	if (nod > 39)
		ft_error();
	if (check_only_zero(nb))
	{
		ft_putstr(dict_get_word_from_digit(map.a_digits, map.a_words, "0"));
		return ;
	}
	cd = nod; //starts from the biggest digit
	while (cd > 0 && nb[nod - cd] != 0)
	{
		// print basic number "one", "two" etc..
		// dont print if second number in the region is 1
		// dont print if currest digit is second number
		if (!(cd % 3 == 1 && nb[nod - cd - 1] == '1'))
			if (cd % 3 != 2 && nb[nod - cd] != '0')
				ft_putstr(dict_get_word_from_digit(map.a_digits, map.a_words,
							get_n_via_digit(nb[nod - cd] - 48)));
		//if current region has value
		if (region_has_value(nb, cd, nod))
		{
			print_first_region(map, nb, cd, nod);
			//only when current number is the first digit in the region
			//only when current number is the second digit in the region
			print_second_region(map, nb, cd, nod);
			//only when current number is the third digit in the region
			print_third_region(map, nb, cd, nod);
		}
		cd--;
	}
}

/*********************** MAIN PRINTWORDS FUNCTION ***********************/
void	t_printwords(char *file, char *str)
{
	int		maxstrlen;
	int		maxrow;
	
	t_map	map;

	//Loop through words by words,
	//	get largest width (strlen) & height (rows) available
	dict_get_largest_len_row(file, &maxstrlen, &maxrow);
	//Store the set of variables into our 2D array
	map.a_digits = dict_store_array_key(file, maxrow, maxstrlen);
	//last digit = 1 means key [left side]
	map.a_words = dict_store_array_value(file, maxrow, maxstrlen);
	//last digit = 0 means value [right side]
	//Process what we've stored to be printed out as words
	str_to_word(map, str);
	//Free up all the 2D arrays
	dict_free_2d_array(map.a_digits);
	dict_free_2d_array(map.a_words);
}

int	main(int argc, char **argv)
{
	// argc = 2;
	// argv[1] = "4321";
	//Throw error when num of arguments inaccurate
	if (!(argc == 2 || argc == 3))
		ft_error();
	//Next, we attempt to get the file name
	if (argc == 3)
	{
		//Otherwise, load in custom file name
		t_printwords(argv[1], argv[2]);
	}
	else if (argc == 2)
	{
		//If no custom file name, we use the default one
		t_printwords("numbers.dict", argv[1]);
	}
	return (0);
}
