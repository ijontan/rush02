

int	power(int nb, int pw)
{
	int	value;

	value = nb;
	while (--pw > 0)
		value *= nb;
	return (value);
}

void	itow(unsigned long long nb)
{
	int					nod;
	unsigned long long	temp;
	char				*ones;
	char				*tens;
	char				*ftens;
	char				*digits;

	nod = 0;
	temp = nb;
	while (temp > 0)
	{
		temp /= 10;
		nod++;
	}
	while (nod > 0)
	{
		if ((nb / power(10, nod)) != 0)
			ones[nb / power(10, nod)];
		if (region_has_value())
		{
			if (nod % 3 == 0)
			{
				digits[nod];
			}
			else
			{
				tens[nod % 3];
			}
		}
		nod--;
	}
}
