/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:36:39 by yowoo             #+#    #+#             */
/*   Updated: 2024/07/22 19:46:51 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	ft_usleep(philo->round->t_eat);
	pthread_mutex_unlock(&(philo->round->forks[philo->fork2]));
	pthread_mutex_unlock(&(philo->round->forks[philo->fork1]));
	philo->cnt_eat++;
	print_log('s', philo);
	ft_usleep(philo->round->t_sleep);
	print_log('t', philo);
}

static void	*loop_routine(t_philo *philo)
{
	if (pthread_mutex_lock(&(philo->round->forks[philo->fork1])) != 0)
		return (philo->round->is_error = 1, NULL);
	print_log('f', philo);
	if (philo->round->n_philo == 1)
		return (pthread_mutex_unlock(&(philo->round->forks[philo->fork1])), \
		NULL);
	if (pthread_mutex_lock(&(philo->round->forks[philo->fork2])) != 0)
	{
		pthread_mutex_unlock(&(philo->round->forks[philo->fork1]));
		return (philo->round->is_error = 2, NULL);
	}
	print_log('e', philo);
	if (gettimeofday(&(philo->last_eat), NULL) != 0)
	{
		pthread_mutex_unlock(&(philo->round->forks[philo->fork2]));
		pthread_mutex_unlock(&(philo->round->forks[philo->fork1]));
		return (philo->round->is_error = 3, NULL);
	}
	eating(philo);
	return (NULL);
}

void	*thread_routine(void *philo)
{
	t_philo	*philo_s;

	philo_s = (t_philo *)philo;
	philo_s->fork1 = philo_s->id + (philo_s->id % 2 == 1);
	philo_s->fork2 = philo_s->id + (philo_s->id % 2 == 0);
	if (philo_s->id == philo_s->round->n_philo - 1)
	{
		if (philo_s->fork1 == philo_s->round->n_philo)
			philo_s->fork1 = 0;
		else if (philo_s->fork2 == philo_s->round->n_philo)
			philo_s->fork2 = 0;
	}
	while (!philo_s->round->terminate && !philo_s->round->is_error)
	{
		loop_routine(philo_s);
		if (philo_s->round->n_philo == 1)
			break ;
	}
	return (NULL);
}

int	init_philo(t_philo *philo, int i)
{
	if ((gettimeofday(&(philo[i].last_eat), NULL) != 0) || \
		((pthread_create(&(philo[i].thread), NULL, thread_routine, \
		(void *)&(philo[i])) != 0)))
		return (1);
	else
		return (0);
}
