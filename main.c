/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 19:33:32 by yowoo             #+#    #+#             */
/*   Updated: 2024/07/15 20:09:44 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
	t_round		round;
	t_philo		*philo;
	int			i;
	//THREAD TO MONITOR
	pthread_t	mon_thread;
	
	philo = 0;
	//CHECK IF THE INPUTS ARE VALID
    if (is_inpt_ok(argc, argv))
	{	
		init_struct(&round, argc, argv);
		//MALLOC NUMBER OF PHILOS
		philo = (t_philo *)malloc(sizeof(t_philo) * round.n_philo);
		init_philos(&philo, &round);
		// printf("%dth terminate after initphilo %d\n", 3, philo[3].round->terminate);
		// printf("%dth is_error after initphilo %d\n", 3, philo[3].round->is_error);
	}
	else
		return (-1);

		
	i = 0;
	//FOR ALL PHILOS, INIT LAST_EAT, CREATE THREAD AND DO ROUTINE. CLEAN IF ERROR
	while (i < round.n_philo)
	{	
		// printf("main %dth terminate %d\n", i, (philo)[i].round->terminate);
		// printf("main %dth is_error %d\n", i, (philo)[i].round->is_error);
		if ((gettimeofday(&(philo[i].last_eat), NULL) != 0) || ((pthread_create(&(philo[i].thread), NULL, thread_routine, (void *)&(philo[i])) != 0)))
			return (clean(round.n_philo, philo, round, i));
		// printf("i: %d\n", i);
		i++;
	}
	//MONITOR IF PHILO HAS DIED OR ATE ENOUGH
	if (pthread_create(&mon_thread, NULL, monitor_death_eat, (void *)(philo)) != 0)
		return (clean(round.n_philo, philo, round, round.n_philo));
	i = -1;
	//WAIT TILL EACH PHILO THREAD FINISH AND JOIN
	while (++i< round.n_philo)
	{
		// printf("threadjoin in main %d\n", philo[i].id);
		pthread_join(philo[i].thread, NULL);
	}
	pthread_join(mon_thread, NULL);
	if(round.is_error)
		printf("\nError Occured 1: %d\n", round.is_error);
	clean(round.n_philo, philo, round, -1);

	
	return (0);
}



//eating-> sleeping -> thinking
// # phils = # forks