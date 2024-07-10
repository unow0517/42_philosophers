/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 19:33:32 by yowoo             #+#    #+#             */
/*   Updated: 2024/07/10 15:41:51 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	*thread_routine(void *philo)
// {
// 	t_philo	*philo_s;
// 	int		fork1;
// 	int		fork2;

// 	philo_s = (t_philo *)philo;
// 	fork1 = philo_s->id + (philo_s->id % 2 == 1);
// 	fork2 = philo_s->id + (philo_s->id % 2 == 0);
// 	if (philo_s->id == philo_s->info->phil_n - 1)
// 	{
// 		if (fork1 == philo_s->info->phil_n)
// 			fork1 = 0;
// 		else if (fork2 == philo_s->info->phil_n)
// 			fork2 = 0;
// 	}
// 	while (!philo_s->info->terminate && !philo_s->info->is_error)
// 	{
// 		loop_routine(philo_s, fork1, fork2);
// 		if (philo_s->info->phil_n == 1)
// 			break ;
// 	}
// 	return (NULL);
// }

int main(int argc, char **argv)
{
	t_round		round;
	t_philo		*philo;
	int			i;
	
    if (is_inpt_ok(argc, argv))
	{	
		init_struct(&round, argc, argv);
		philo = (t_philo *)malloc(sizeof(t_philo) * round.n_philo);
		init_philos(philo, round);
	}
	else
		return (-1);
	i = 0;
	while (i < round.n_philo)
		if ((gettimeofday(&(philo[i].last_eat), NULL) != 0) || \
		((pthread_create(&(philo[i].thread), NULL, thread_routine, \
		(void *)&(philo[i])) != 0)))
			return (clean(info_s.phil_n, philo, info_s, i));
	
	
	
	return (0);
}

//eating-> sleeping -> thinking
// # phils = # forks