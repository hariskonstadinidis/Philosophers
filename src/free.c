/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariskon <hariskon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 14:13:08 by hkonstan          #+#    #+#             */
/*   Updated: 2026/02/22 19:36:16 by hariskon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_all(t_total *total)
{
	int	i;

	i = 0;
	while (i < total->num_philosophers)
	{
		pthread_mutex_destroy(&total->philosophers[i].eat_mutex);
		i++;
	}
	free(total->philosophers);
	i = 0;
	while (i < total->num_philosophers)
		pthread_mutex_destroy(&total->forks[i++]);
	pthread_mutex_destroy(&total->print_mutex);
	free(total->forks);
}
