/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariskon <hariskon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 20:50:31 by hkonstan          #+#    #+#             */
/*   Updated: 2026/02/23 13:19:26 by hariskon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	get_time(long long start_time)
{
	struct timeval	t;
	long long		c_time;
	long long		sim_time;

	gettimeofday(&t, NULL);
	c_time = t.tv_sec * 1000 + t.tv_usec / 1000;
	sim_time = c_time - start_time;
	return (sim_time);
}

int	check_state(t_state state)
{
	if (state == DEAD)
		return (0);
	else if (state == FED)
		return (0);
	else
		return (1);
}

void	ft_usleep(t_philo *philo, long long duration)
{
	long long	start;

	start = get_time(0);
	while (1)
	{
		if (start + duration < get_time(0))
			break ;
		pthread_mutex_lock(&philo->total->print_mutex);
		if (!check_state(philo->total->state))
		{
			pthread_mutex_unlock(&philo->total->print_mutex);
			break ;
		}
		else
			pthread_mutex_unlock(&philo->total->print_mutex);
		usleep(1000);
	}
}

void	change_state(t_total *total, int i)
{
	pthread_mutex_lock(&total->print_mutex);
	total->state = DEAD;
	printf("%lli %i died\n", get_time(total->time),
		total->philosophers[i].id + 1);
	pthread_mutex_unlock(&total->print_mutex);
	pthread_mutex_unlock(&total->philosophers[i].eat_mutex);
}
