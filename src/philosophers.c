/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonstan <hkonstan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 12:32:05 by hariskon          #+#    #+#             */
/*   Updated: 2026/02/19 21:45:58 by hkonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*print(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->eat_mutex);
		philo->last_eat_time = get_time(philo->total->time);
		philo->times_eaten++;
		pthread_mutex_lock(&philo->total->print_mutex);
			if (philo->total->state == DEAD)
				break;
			else
				printf("philo %i ate %i time at %li.\n", philo->id, philo->times_eaten, get_time(philo->total->time));
		pthread_mutex_unlock(&philo->total->print_mutex);
		usleep(10000);
		if (philo->times_eaten > 5)
			return (NULL);
		pthread_mutex_unlock(&philo->eat_mutex);
	}
	return (NULL);
}

void	*fail_check(void *arg)
{
	t_total	*total;
	int 	i;
	long	time;
	
	total = (t_total *)arg;
	i = 0;
	while (i < total->num_philosophers)
	{
		time = get_time(total->time);
		pthread_mutex_lock(&total->philosophers[i].eat_mutex);
		if (time - total->philosophers->last_eat_time > total->time_to_die)
		{
			pthread_mutex_lock(&total->print_mutex);
			total->state = DEAD;
			pthread_mutex_unlock(&total->print_mutex);
			usleep(1000);
		}	
		pthread_mutex_unlock(&total->philosophers[i].eat_mutex);
		i++;
	}
	return (NULL);
}

static int	start_sim(t_total *total)
{
	int				i;
	struct timeval	t;
	long			time;

	gettimeofday(&t, NULL);
	time = t.tv_sec * 1000 + t.tv_usec / 1000;
	total->time = time;
	i = 0;
	while (i < total->num_philosophers)
	{
		total->philosophers[i].last_eat_time = time;
		if (pthread_create(&total->philosophers[i].thread, NULL, print, &total->philosophers[i]))
			return (write(2, "pthread_init fail 1 in init_philos", 34), 0);
		i++;
	}
	if (pthread_create(&total->monitor, NULL, fail_check, &total))
			return (write(2, "pthread_init fail 2 in init_philos", 34), 0);
	return (1);
}

static int	end_sim(t_total *total)
{
	int	i;
	
	i = 0;
	while (i < total->num_philosophers)
	{
		if (pthread_join(total->philosophers[i].thread, NULL))
			return (write(2, "pthread_join fail 1 in init_philos", 34), 0);
		i++;
	}
	if (pthread_join(total->monitor, NULL))
			return (write(2, "pthread_join fail 2 in init_philos", 34), 0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_total		total;
	
	printf("Hello, Matrix!\n");
	if (!check_input(argc, argv))
		return (1);
	if (!initialize(&total, argv))
		return (1);
	if (!start_sim(&total))
		return (1);
	if (!end_sim(&total))
		return (1);
	printf("Bye, Matrix!\n");
	return (0);
}
