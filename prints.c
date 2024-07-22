/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 19:45:48 by yowoo             #+#    #+#             */
/*   Updated: 2024/07/22 19:46:36 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_str(char str, long stamp, t_philo *philo_s)
{
	if (str == 'f')
		printf("%ld %d has taken a fork\n", stamp, philo_s->id);
	else if (str == 'e')
		printf("%ld %d has taken second fork\n%ld %d is eating\n" \
		, stamp, philo_s->id, stamp, philo_s->id);
	else if (str == 's')
		printf("%ld %d is sleeping\n", stamp, philo_s->id);
	else if (str == 't')
		printf("%ld %d is thinking\n", stamp, philo_s->id);
	else if (str == 'd')
		printf("%ld %d died\nEND\n", stamp, philo_s->id);
	else if (str == 'a')
		printf("%ld Everybody ate %d number of times\nEND\n", \
		stamp, philo_s->round->n_must_eat);
}

void	print_log(char str, t_philo *philo_s)
{
	static int	terminate = 0;
	int			stamp;

	if (pthread_mutex_lock(&(philo_s->round->print_m)) != 0)
	{
		philo_s->round->is_error = 4;
		return ;
	}
	stamp = get_timestamp(philo_s->round->current);
	if (stamp == -1)
	{
		philo_s->round->is_error = 5;
		pthread_mutex_unlock(&(philo_s->round->print_m));
		return ;
	}
	if (terminate)
	{
		pthread_mutex_unlock(&(philo_s->round->print_m));
		return ;
	}
	print_str(str, stamp, philo_s);
	terminate = (str == 'a') || (str == 'd');
	if (pthread_mutex_unlock(&(philo_s->round->print_m)) != 0)
		philo_s->round->is_error = 6;
}
