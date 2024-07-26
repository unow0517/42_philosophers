/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 19:33:32 by yowoo             #+#    #+#             */
/*   Updated: 2024/07/26 20:39:41 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_and_clean(t_round round, t_philo *philo, pthread_t thread)
{
	int	i;

	i = -1;
	while (++i < round.n_philo)
		pthread_join(philo[i].thread, NULL);
	pthread_join(thread, NULL);
	if (round.is_error)
		printf("\nError Occured 1: %d\n", round.is_error);
	clean(round.n_philo, philo, round, -1);
}

int	main(int argc, char **argv)
{
	t_round		round;
	t_philo		*philo;
	int			i;
	pthread_t	thread;

	philo = 0;
	if (is_inpt_ok(argc, argv))
	{
		init_struct(&round, argc, argv);
		philo = (t_philo *)malloc(sizeof(t_philo) * round.n_philo);
		init_philos(&philo, &round);
	}
	else
		return (-1);
	i = 0;
	while (i < round.n_philo)
	{
		if (init_philo(philo, i))
			return (clean(round.n_philo, philo, round, i));
		i++;
	}
	if (pthread_create(&thread, NULL, monitor_death_eat, (void *)(philo)) != 0)
		return (clean(round.n_philo, philo, round, round.n_philo));
	join_and_clean(round, philo, thread);
	return (0);
}
