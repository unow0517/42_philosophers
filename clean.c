/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 09:41:38 by yowoo             #+#    #+#             */
/*   Updated: 2024/07/11 09:42:11 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	clean(int end_mutex, t_philo *philo, t_round round, int end_threads)
{
	int	i;

	if (end_threads == -1)
		end_threads = 0;
	else
		printf("Error occured 2\n");
	printf("Cleaning\n");
	if (end_threads > 0)
	{
		round.terminate = 1;
		i = -1;
		while (++i < end_threads)
			pthread_join(philo[i].thread, NULL);
	}
	if (end_mutex == -2)
		return (0);
	i = -1;
	while (++i < end_mutex)
		pthread_mutex_destroy(&(round.forks[i]));
	pthread_mutex_destroy(&(round.print_m));
	free(round.forks);
	free(philo);
	return (0);
}