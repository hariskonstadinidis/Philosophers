/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariskon <hariskon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 12:32:05 by hariskon          #+#    #+#             */
/*   Updated: 2026/02/22 00:13:17 by hariskon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	print_message(t_philo *philo, t_state status)
{
	long long	time;

	time = get_time(philo->total->time);
	pthread_mutex_lock(&philo->total->print_mutex);
	if (philo->total->state == DEAD)
	{
		pthread_mutex_unlock(&philo->total->print_mutex);
		return (0);
	}
	else if (philo->total->state == FED)
	{
		pthread_mutex_unlock(&philo->total->print_mutex);
		return (0);
	}
	else if (status == FORK)
		printf("%lli philosopher %i took a fork\n", time, philo->id + 1);
	else if (status == EAT)
		printf("%lli philosopher %i is eating\n", time, philo->id + 1);
	else if (status == SLEEP)
		printf("%lli philosopher %i is sleeping\n", time, philo->id + 1);
	else
		printf("%lli philosopher %i is thinking\n", time, philo->id + 1);
	pthread_mutex_unlock(&philo->total->print_mutex);
	return (1);
}

static int	get_forks(t_philo *philo)
{
	int	id;

	id = philo->id;
	if (id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		if (!print_message(philo, FORK))
			return (pthread_mutex_unlock(philo->left_fork), 0);
		pthread_mutex_lock(philo->right_fork);
		if (!print_message(philo, FORK))
			return (pthread_mutex_unlock(philo->right_fork), pthread_mutex_unlock(philo->left_fork), 0);
		pthread_mutex_lock(&philo->eat_mutex);
		philo->last_eat_time = get_time(philo->total->time) + philo->total->time;
		philo->times_eaten++;
		pthread_mutex_unlock(&philo->eat_mutex);
		if (!print_message(philo, EAT))
			return (pthread_mutex_unlock(philo->right_fork), pthread_mutex_unlock(philo->left_fork), 0);
		usleep(philo->total->time_to_eat * 1000);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		if (!print_message(philo, FORK))
			return (pthread_mutex_unlock(philo->right_fork), 0);
		pthread_mutex_lock(philo->left_fork);
		if (!print_message(philo, FORK))
			return (pthread_mutex_unlock(philo->left_fork), pthread_mutex_unlock(philo->right_fork), 0);
		pthread_mutex_lock(&philo->eat_mutex);
		philo->last_eat_time = get_time(philo->total->time) + philo->total->time;
		philo->times_eaten++;
		pthread_mutex_unlock(&philo->eat_mutex);
		if (!print_message(philo, EAT))
			return (pthread_mutex_unlock(philo->left_fork), pthread_mutex_unlock(philo->right_fork), 0);
		usleep(philo->total->time_to_eat * 1000);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	return (1);
}

static void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->total->print_mutex);
	pthread_mutex_unlock(&philo->total->print_mutex);
	if (philo->id % 2 != 0)
		usleep(250);
	while (1)
	{
		if (!get_forks(philo))
			return (NULL);
		if (!print_message (philo, SLEEP))
			return (NULL);
		usleep(philo->total->time_to_sleep * 1000);
		if (!print_message (philo, THINK))
			return (NULL);
	}
	return (NULL);
}

static int	check_fed(t_total *total, int *fed_count, int i)
{
	if (total->num_meals == -1)
		return (1);
	if (total->philosophers[i].times_eaten >= total->num_meals)
		(*fed_count)++;
	if (*fed_count >= total->num_philosophers)
	{
		pthread_mutex_lock(&total->print_mutex);
		total->state = FED;
		printf("%lli All philosophers are fed\n", get_time(total->time));
		pthread_mutex_unlock(&total->print_mutex);
		pthread_mutex_unlock(&total->philosophers[i].eat_mutex);
		return (0);
	}
	return (1);
}

static void	change_state(t_total *total, int i)
{
	pthread_mutex_lock(&total->print_mutex);
	total->state = DEAD;
	printf("%lli philosopher %i died from hunger at %lli\n", get_time(total->time), total->philosophers[i].id + 1, get_time(total->philosophers[i].last_eat_time));
	pthread_mutex_unlock(&total->print_mutex);
	pthread_mutex_unlock(&total->philosophers[i].eat_mutex);
}

void	*fail_check(void *arg)
{
	t_total		*total;
	int			i;
	int			fed_count;

	total = (t_total *)arg;
	i = 0;
	while (1)
	{
		if (i == 0)
			fed_count = 0;
		pthread_mutex_lock(&total->philosophers[i].eat_mutex);
		if (get_time(total->philosophers[i].last_eat_time) > total->time_to_die)
		{
			change_state(total, i);
			break ;
		}
		if (!check_fed(total, &fed_count, i))
			break ;
		pthread_mutex_unlock(&total->philosophers[i].eat_mutex);
		i++;
		if (i == total->num_philosophers)
			i = 0;
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
	pthread_mutex_lock(&total->print_mutex);
	while (i < total->num_philosophers)
	{
		total->philosophers[i].last_eat_time = time;
		if (pthread_create(&total->philosophers[i].thread, NULL, routine, &total->philosophers[i]))
			return (write(2, "pthread_init fail 1 in init_philos", 34), 0);
		i++;
	}
	if (pthread_create(&total->monitor, NULL, fail_check, total))
		return (write(2, "pthread_init fail 2 in init_philos", 34), 0);
	pthread_mutex_unlock(&total->print_mutex);
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
	// free_all(&total);
	printf("Bye, Matrix!\n");
	return (0);
}
