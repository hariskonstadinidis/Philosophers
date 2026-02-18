/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariskon <hariskon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 13:45:34 by hariskon          #+#    #+#             */
/*   Updated: 2026/02/18 15:07:13 by hariskon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	get_values(char **argv, t_total *total)
{
	int	i;
	
	i = 0;
	while (argv[i])
	{
		if (i == 1)
			total->num_philosophers = check_number(argv[i]);
		else if (i == 2)
			total->time_to_die = check_number(argv[i]);
		else if (i == 3)
			total->time_to_eat = check_number(argv[i]);
		else if (i == 4)
			total->time_to_sleep = check_number(argv[i]);
		else if (i == 5)
			total->num_meals = check_number(argv[i]);
		i++;
	}
}

int	initialize(t_total *total, int argc, char **argv)
{
	int	i;

	i = 0;
	total = malloc(sizeof(t_total));
	if (!total)
		return (write(2, "mem alloc 1 in init fail", 24), 0);
	get_values(argv, total);
	total->philosophers = malloc(sizeof(pthread_t) * total->num_philosophers);
	if (!total->philosophers)
		return (write(2, "mem alloc 2 in init fail", 24), 0);
	total->forks = malloc(sizeof(pthread_mutex_t) * total->num_philosophers);
	if (!total->forks)		
		return (write(2, "mem alloc 3 in init fail", 24), 0);
	return (1);
}
