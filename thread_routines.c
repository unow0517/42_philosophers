/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:36:39 by yowoo             #+#    #+#             */
/*   Updated: 2024/07/10 15:58:57 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_routine(void *philo)
{
	t_philo	*philo_s;
	int		fork1;
	int		fork2;

	philo_s = (t_philo *)philo;
	fork1 = philo_s->id + (philo_s->id % 2 == 1);
	fork2 = philo_s->id + (philo_s->id % 2 == 0);
	if (philo_s->id == philo_s->round->n_philo - 1)
	{
		if (fork1 == philo_s->round->n_philo)
			fork1 = 0;
		else if (fork2 == philo_s->round->n_philo)
			fork2 = 0;
	}
	while (!philo_s->round->terminate && !philo_s->round->is_error)
	{
		loop_routine(philo_s, fork1, fork2);
		if (philo_s->round->n_philo == 1)
			break ;
	}
	return (NULL);
}

static void	*loop_routine(t_philo *philo_s, int fork1, int fork2)
{
	if (pthread_mutex_lock(&(philo_s->info->forks[fork1])) != 0)
		return (philo_s->info->is_error = 1, NULL);
	print_log('f', philo_s);
	if (philo_s->info->phil_n == 1)
		return (pthread_mutex_unlock(&(philo_s->info->forks[fork1])), NULL);
	if (pthread_mutex_lock(&(philo_s->info->forks[fork2])) != 0)
	{
		pthread_mutex_unlock(&(philo_s->info->forks[fork1]));
		return (philo_s->info->is_error = 2, NULL);
	}
	print_log('e', philo_s);
	if (gettimeofday(&(philo_s->last_eat), NULL) != 0)
	{
		pthread_mutex_unlock(&(philo_s->info->forks[fork2]));
		pthread_mutex_unlock(&(philo_s->info->forks[fork1]));
		return (philo_s->info->is_error = 3, NULL);
	}
	ft_usleep(philo_s->info->eat_t);
	pthread_mutex_unlock(&(philo_s->info->forks[fork2]));
	pthread_mutex_unlock(&(philo_s->info->forks[fork1]));
	philo_s->eaten_n++;
	print_log('s', philo_s);
	ft_usleep(philo_s->info->sleep_t);
	print_log('t', philo_s);
	return (NULL);
}

