/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonstan <hkonstan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 20:50:31 by hkonstan          #+#    #+#             */
/*   Updated: 2026/02/19 20:50:55 by hkonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time(long start_time)
{
	struct timeval	t;
	long			c_time;
	long			sim_time;

	gettimeofday(&t, NULL);
	c_time = t.tv_sec * 1000 + t.tv_usec / 1000;
	sim_time = c_time - start_time;
	return (sim_time);
}