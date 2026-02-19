/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonstan <hkonstan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 12:30:33 by hariskon          #+#    #+#             */
/*   Updated: 2026/02/19 21:26:07 by hkonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_total	t_total;

typedef enum s_state
{
	DEAD,
	ALIVE
}	t_state;

typedef struct s_philo
{
	int				id;
	int				times_eaten;
	long long		last_eat_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	eat_mutex;
	t_total			*total;
	pthread_t		thread;
}	t_philo;

typedef struct s_total
{
	long			time;
	t_state			state;
	int				num_philosophers;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				num_meals;
	t_philo			*philosophers;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_t		monitor;
}	t_total;

int		check_number(char *str);
int		check_input(int argc, char **argv);
int		initialize(t_total *total, char **argv);
long	get_time(long start_time);

#endif