/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariskon <hariskon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 12:30:33 by hariskon          #+#    #+#             */
/*   Updated: 2026/02/18 14:48:02 by hariskon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_philo
{
    int             id;
    int             times_eaten;
    long long       last_eat_time;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    pthread_mutex_t *eat_mutex;
    pthread_t       *monitor;
}	t_philo;

typedef struct s_total
{
    int				num_philosophers;
    long long		time_to_die;
    long long		time_to_eat;
    long long		time_to_sleep;
    int				num_meals;
    t_philo     	*philosophers;
    pthread_t       *threads;
    pthread_mutex_t *forks;
    pthread_mutex_t print_mutex;
    pthread_t       monitor;
}	t_total;

#endif