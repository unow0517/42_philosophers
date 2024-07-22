/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 11:47:58 by yowoo             #+#    #+#             */
/*   Updated: 2024/07/22 18:42:10 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_struct(t_round *round, int argc, char **argv)
{
	round->n_philo = ft_atoi(argv[1]);
	round->t_die = ft_atoi(argv[2]);
	round->t_eat = ft_atoi(argv[3]);
	round->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		round->n_must_eat = ft_atoi(argv[5]);
	}
	else
		round->n_must_eat = -1;
	gettimeofday(&(round->begin), NULL);
	round->forks = malloc(sizeof(pthread_mutex_t) * round->n_philo);
	round->terminate = 0;
	round->is_error = 0;
	pthread_mutex_init(&(round->print_m), NULL);
	gettimeofday(&(round->current), NULL);
}

void	init_philos(t_philo **philo, t_round *round)
{
	int	i;

	i = 0;
	while (i < round->n_philo)
	{
		(*philo)[i].id = i;
		(*philo)[i].round = round;
		(*philo)[i].state = THINK;
		i++;
	}
}
