/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 19:33:32 by yowoo             #+#    #+#             */
/*   Updated: 2024/07/12 19:23:39 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
	t_round		round;
	t_philo		*philo;
	int			i;
	
	//CHECK IF THE INPUTS ARE VALID
    if (is_inpt_ok(argc, argv))
	{	
		init_struct(&round, argc, argv);
		//MALLOC NUMBER OF PHILOS
		philo = (t_philo *)malloc(sizeof(t_philo) * round.n_philo);
		init_philos(philo, round);
	}
	else
		return (-1);
	i = 0;
	//FOR ALL PHILOS, INIT LAST_EAT, CREATE THREAD AND DO ROUTINE. CLEAN IF ERROR
	while (i < round.n_philo)
	{	
		if ((gettimeofday(&(philo[i].last_eat), NULL) != 0) || ((pthread_create(&(philo[i].thread), NULL, thread_routine, (void *)&(philo[i])) != 0)))
			return (clean(round.n_philo, philo, round, i));
		i++;
	}
	
	
	
	
	return (0);
}



//eating-> sleeping -> thinking
// # phils = # forks