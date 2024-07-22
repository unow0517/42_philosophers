/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 19:51:37 by yowoo             #+#    #+#             */
/*   Updated: 2024/07/22 19:36:56 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_death_eat(void *philo)
{
	t_philo	*philo_s;
	int		i;
	int		ate_enough;
	int		is_dead;

	ate_enough = 0;
	is_dead = 0;
	philo_s = (t_philo *)philo;
	while (!ate_enough && !is_dead && !philo_s[0].round->is_error)
	{
		i = -1;
		ate_enough = philo_s[0].round->n_must_eat != -1;
		while (ate_enough && ++i < philo_s[0].round->n_philo)
			if (philo_s[i].cnt_eat < philo_s[0].round->n_must_eat)
				ate_enough = 0;
		i = 0;
		while (!is_dead && i < philo_s[0].round->n_philo)
			is_dead += get_timestamp(philo_s[i++].last_eat) > \
			philo_s[0].round->t_die;
	}
	if (is_dead > 0 || ate_enough)
		print_log('a' + 3 * (is_dead > 0), &philo_s[--i]);
	philo_s[0].round->terminate = 1;
	philo_s[0].round->is_error += is_dead == -1;
	return (NULL);
}
