/*
EASILY COMPILABLE VERSION TO RUN DEBUGGING ON & TO EXPLAIN TO TEAMMATES.
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

char	*ft_dup_until_char(char *str, char c)
{
	int		len;
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
//IF RUN INTO ERROR DURING COMPILATION TIME
	- CAN USE THIS TO CREATE BLANK STRING
//WHERE I RETURNED NULL, WHEN NEED A STRING
char	*empty_freeable_string(void)
{
	char	*string;

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
	ft_putstr("Error\n"); //Requested by pdf, write Error when it crash
	exit(1);              //This is a built in function to terminate,
							//		and throw 1 to show that it has error
}

void	ft_dev_error(char *str)
{
	ft_putstr(str);
	exit(1);
}

/*********************** DICTIONARY STORAGE FUNCTIONS ***********************/
void	dict_free_2d_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != 0)
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

	//Attempt to read file
	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error();
	row = 0; //Get max rows/input from dictionary
	len = 0; //Get max length of either left/right
	//Read will loop through things char by char,
	//	while still got data = 1; if reached end = 0;
	while (read(fd, &buffer, 1))
	{
		len++;              //Save down how many extra characters there are
		if (buffer == '\n') //Progress rows if there's line break
			row++;
	}
	*maxstrlen = len;
	//See if the whole dict ended with or without nextline '\n'
	if (buffer == '\n')
		*maxrow = row; //If we're at next line - means it terminated with \n
	else
		*maxrow = row + 1; // + 1 because last row no \n
	//Before exiting, we close file
	close(fd);
}

char	**dict_store_array(char *file, int maxrow, unsigned int maxstrlen,
		int storekey)
{
	char	**a_output;
	int		fd;
	char	buffer[maxstrlen + 1];

	//This is for temporary storage as we loop through array
	unsigned int i;   //For char by char
	unsigned int row; //For row
	//Create an allocation with the largest size for the 2D array [top > bottom]
	a_output = (char **)malloc(sizeof(char *) * (maxrow + 1));
	if (!(a_output))
		return (NULL);
	a_output[maxrow] = 0; //Add null terminator
	//Clean up our stack's memory for buffer
	i = 0;
	while (i < maxstrlen)
	{
		buffer[i] = 0;
		i++;
	}
	buffer[i] = 0; //Set null terminator
	//Now, loop through dictionary to read file
	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error();
	i = 0; //Restart main array space
	row = 0;
	if (!read(fd, buffer, maxstrlen)) //Read whole text into array
		ft_error();                   //If cannot read file
	while (*(buffer + i) != '\0')
	{
		while (*(buffer + i) != '\0' && !ft_in_str(*(buffer + i), "0123456789"))
			//Loop until reach number
			i++;
		if (storekey == 1)
		{
			a_output[row] = ft_dup_until_char(buffer + i, ':');
			row++; //Progress row forward
		}
		while (*(buffer + i) != '\0' && !ft_in_str(*(buffer + i), ":"))
			//Loop until reach :
			i++;
		i++; //Skip the : itself
		i++; //Skip the ' ' right after
		if (storekey == 0)
		{
			a_output[row] = ft_dup_until_char(buffer + i, '\n');
			row++; //Progress row forward
		}
		while (*(buffer + i) != '\0' && !ft_in_str(*(buffer + i), "\n"))
			//Loop until endline
			i++;
	}
	//Before exiting, we close file
	close(fd);
	//Return the 2D array we attempted to store
	return (a_output);
}

/*********************** DICTIONARY VALUE FUNCTIONS ***********************/
char	*dict_get_word_from_digit(char **a_key, char **a_value, char *key)
{
	int	i;

	i = 0;
	while (a_key[i] != 0)
	{
		if (ft_strcmp(a_key[i], key) == 0)
			return (a_value[i]);
		i++;
	}
	return (0); //If nothing is found
}

char	*dict_get_digit_from_word(char **a_key, char **a_value, char *value)
{
	int	i;

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
	if (n <= 0) //If no zeros to create
		return (0);
	output[0] = n + 48;
	return (output);
}

char	*get_teenn_via_digit(int n)
{
	char	*output;

	output = (char *)malloc(sizeof(char) * (3));
	if (n > 10 && n < 20) //If no zeros to create
	{
		output[0] = '1';
		output[1] = (n % 10) + 48;
	}
	return (output);
}
char	*get_tyn_via_digit(int n)
{
	char	*output;

	output = (char *)malloc(sizeof(char) * (3));
	if (n > 10 && n < 20) //If no zeros to create
	{
		output[1] = '0';
		output[0] = (n % 10) + 48;
	}
	return (output);
}
int	region_has_value(char *nb, int cd)
{
	int	region_position;

	region_position = cd / 3 * 3; //starting position of the rigion checking
	while (region_position < cd / 3 * 3 + 3)
	{
		if (nb[region_position] <= '9' && nb[region_position] >= '1')
			return (1);
		region_position++;
	}
	return (0);
}
void	str_to_word(char **a_digits, char **a_words, char *nb)
{
	int	nod;
	int	cd;

	//int o=0;
	nod = 0;
	while (nb[nod])
		nod++;
	cd = nod;
	while (cd > 0)
	{
		if (nb[nod - cd] != 0)
			if (!(cd % 3 == 1 && nb[nod - cd - 1] == '1'))
				if (nb[nod - cd - 1] != '1')
					ft_putstr(dict_get_word_from_digit(a_digits, a_words,
								get_n_via_digit(nb[nod - cd] - 48)));
		if (region_has_value(nb, cd) && cd != 1)
		{
			ft_putchar(' ');
			if (cd % 3 == 1)
			{
				if (nb[nod - cd - 1] == '1')
					ft_putstr(dict_get_word_from_digit(a_digits, a_words,
								get_teenn_via_digit(nb[nod - cd] - 48)));
				ft_putchar(' ');
				ft_putstr(dict_get_word_from_digit(a_digits, a_words,
							get_10n_via_digit(cd)));
			}
			else if (cd % 3 == 2 && nb[nod - cd] != '1')
				ft_putstr(dict_get_word_from_digit(a_digits, a_words,
							get_tyn_via_digit(nb[nod - cd] - 48)));
			else
			{
				ft_putstr(dict_get_word_from_digit(a_digits, a_words, "100"));
				ft_putstr(" and");
			}
			ft_putchar(' ');
		}
		cd--;
	}
}

/*********************** MAIN PRINTWORDS FUNCTION ***********************/
void	t_printwords(char *file, char *str)
{
	int		maxstrlen;
	int		maxrow;
	char	**a_digits;
	char	**a_words;

	//Loop through words by words,
	//	get largest width (strlen) & height (rows) available
	dict_get_largest_len_row(file, &maxstrlen, &maxrow);
	//Store the set of variables into our 2D array
	a_digits = dict_store_array(file, maxrow, maxstrlen, 1);
	//last digit = 1 means key [left side]
	a_words = dict_store_array(file, maxrow, maxstrlen, 0);
	//last digit = 0 means value [right side]
	//Process what we've stored to be printed out as words
	str_to_word(a_digits, a_words, str);
	//Free up all the 2D arrays
	dict_free_2d_array(a_digits);
	dict_free_2d_array(a_words);
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
