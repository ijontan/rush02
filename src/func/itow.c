

int	power(int nb, int pw)
{
	int	value;

	value = nb;
	while (--pw > 0)
		value *= nb;
	return (value);
}

void	itow(char *nb)
{
	int		nod;
	int		cd;
	char	*ones;
	char	*tens;
	char	*ftens;
	char	*digits;

	nod = 0;
	while (nb[nod])
		nod++;
	cd = nod;
	while (cd > 0)
	{
		if (nb[nod - cd] != 0)
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
