/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 19:51:37 by yowoo             #+#    #+#             */
/*   Updated: 2024/07/15 20:26:35 by yowoo            ###   ########.fr       */
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
    //
	// printf("is_error in monitor %d\n", philo_s[0].round->is_error);

	while (!ate_enough && !is_dead && !philo_s[0].round->is_error)
	{
		i = -1;
        //IF OPTIONAL ARGUMENT IS GIVEN, THEN 1;
		ate_enough = philo_s[0].round->n_must_eat != -1;
        //IF N_MUST_EAT IS GIVEN, IF PHILO ATE LESS THEN N_MUST_EAT, THEN 0
        //HERE IT CHECKS IF PHILO ATE ENOUTH TO FINISH THE ROUND
		while (ate_enough && ++i < philo_s[0].round->n_philo)
			if (philo_s[i].cnt_eat < philo_s[0].round->n_must_eat)
				ate_enough = 0;
		i = 0;
        //CHECK EVERY PHILO STARVE MORE THAN T_DIE
		while (!is_dead && i < philo_s[0].round->n_philo)
			is_dead += get_timestamp(philo_s[i++].last_eat) > philo_s[0].round->t_die;
	}
    //PRINT_LOG A IF IS EATEN IS NOT 0, OR PRINT_LOG D(PHILO DIED)
	printf("is dead %d\n", is_dead);
	printf("ate_enough %d\n", ate_enough);
	if (is_dead > 0 || ate_enough)
		print_log('a' + 3 * (is_dead > 0), &philo_s[--i]);
	philo_s[0].round->terminate = 1;
	// printf("terminate to 1 in monitor\n");
	// printf("is_error in monitor before %d\n", philo[0].round->is_error);
	philo_s[0].round->is_error += is_dead == -1;
	// printf("is_error in monitor after %d\n", philo[0].round->is_error);

	
	return (NULL);
}