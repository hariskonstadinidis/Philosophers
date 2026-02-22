/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariskon <hariskon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 12:30:33 by hariskon          #+#    #+#             */
/*   Updated: 2026/02/22 19:29:39 by hariskon         ###   ########.fr       */
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
	ALIVE,
	FED,
	FORK,
	EAT,
	SLEEP,
	THINK
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
	long long		time;
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

void		free_all(t_total *total);

int			check_number(char *str);
int			check_input(int argc, char **argv);

void		ft_usleep(t_philo *philo, long long duration);
int			check_state(t_state state);
int			check_fed(t_total *total, int *fed_count, int i);

int			initialize(t_total *total, char **argv);
long long	get_time(long start_time);

int			get_forks(t_philo *philo);
void		change_state(t_total *total, int i);

int			end_sim(t_total *total);
int			start_sim(t_total *total);
int			print_message(t_philo *philo, t_state status);

#endif