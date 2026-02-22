/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariskon <hariskon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 13:45:34 by hariskon          #+#    #+#             */
/*   Updated: 2026/02/22 19:36:59 by hariskon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_forks(t_total *total)
{
	int	i;

	i = 0;
	while (i < total->num_philosophers)
	{
		if (pthread_mutex_init(&total->forks[i], NULL))
		{
			while (i >= 0)
				pthread_mutex_destroy((&total->forks[i--]));
			return (write(2, "mutex_init fail in forks", 24), 0);
		}
		i++;
	}
	return (1);
}

static int	init_philos(t_total *total)
{
	int	i;

	i = 0;
	while (i < total->num_philosophers)
	{
		total->philosophers[i].id = i;
		total->philosophers[i].times_eaten = 0;
		total->philosophers[i].last_eat_time = total->time;
		if (i == 0)
			total->philosophers[i].left_fork
				= &total->forks[total->num_philosophers - 1];
		else
			total->philosophers[i].left_fork = &total->forks[i - 1];
		total->philosophers[i].right_fork = &total->forks[i];
		if (pthread_mutex_init(&total->philosophers[i].eat_mutex, NULL))
		{
			while (i >= 0)
				pthread_mutex_destroy((&total->philosophers[i--].eat_mutex));
			return (write(2, "mutex_init fail in init_philos", 30), 0);
		}
		total->philosophers[i++].total = total;
	}
	return (1);
}

static int	init_total(char **argv, t_total *total)
{
	total->num_philosophers = check_number(argv[1]);
	total->time_to_die = check_number(argv[2]);
	total->time_to_eat = check_number(argv[3]);
	total->time_to_sleep = check_number(argv[4]);
	if (argv[5])
		total->num_meals = check_number(argv[5]);
	else
		total->num_meals = -1;
	total->state = ALIVE;
	if (pthread_mutex_init(&total->print_mutex, NULL))
		return (write(2, "mutex_init fail in init_total", 29), 0);
	return (1);
}

int	initialize(t_total *total, char **argv)
{
	if (!init_total(argv, total))
		return (write(2, "mem alloc 0 in init fail", 24), 0);
	total->forks = malloc(sizeof(pthread_mutex_t) * total->num_philosophers);
	if (!total->forks)
		return (write(2, "mem alloc 1 in init fail", 24), 0);
	if (!init_forks(total))
		return (write(2, "mem alloc 2 in init fail", 24), 0);
	total->philosophers = malloc(sizeof(t_philo) * total->num_philosophers);
	if (!total->philosophers)
		return (write(2, "mem alloc 3 in init fail", 24), 0);
	if (!init_philos(total))
		return (0);
	return (1);
}
