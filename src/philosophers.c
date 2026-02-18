/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariskon <hariskon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 12:32:05 by hariskon          #+#    #+#             */
/*   Updated: 2026/02/18 14:13:45 by hariskon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_number(char *str)
{
	int			i;
	long long	num;

	i = 0;
	num = 0;
	while (str[i])
		num = num * 10 + (str[i++] - '0');
	if (num > 2147483647 || num == 0)
		return (0);
	return (num);
}

static int	check_input(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
	{
		printf("Wrong amount of arguments!\n");
		return (0);
	}
	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (printf("Wrong argument: %s\n", argv[i]), 0);
			j++;
		}
		if (check_number(argv[i]))
			return (printf("Argument out of range: %s\n", argv[i]), 0);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_total	total;
	
	if (!check_input(argc, argv))
		return (1);
	if (!initialize(&total, argc, argv))
		return (1);
	printf("Hello, World!\n");
	return (0);
}
