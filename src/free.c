/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonstan <hkonstan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 14:13:08 by hkonstan          #+#    #+#             */
/*   Updated: 2026/02/19 20:48:31 by hkonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int free_philo(t_total *total)
{
	int	i;

	i = 0;
	while (i < total->num_philosophers)
	{
		pthread_mutex_destroy(total->philosophers->)
		free(total->philosophers->)
	}
}