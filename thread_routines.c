/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:36:39 by yowoo             #+#    #+#             */
/*   Updated: 2024/07/15 20:30:17 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//EACH FORK IS PROTECTED WITH MUTEX
static void	*loop_routine(t_philo *philo)
{
	// printf("entered loop routine\n");
	//LOCK THE FORK1, OR IS ERROR -1
	//LOCk= GET THE PERMISSION TO THE CRITICAL SECTION
	if (pthread_mutex_lock(&(philo->round->forks[philo->fork1])) != 0)
		return (philo->round->is_error = 1, NULL);
	//PRINT FORK IS TAKEN BY ID
	// printf("right before printlog in looproutine f\n");
	print_log('f', philo);
	//IF PHILO IS 1, UNLOCK THE MUTEX FORK
	if (philo->round->n_philo == 1)
		return (pthread_mutex_unlock(&(philo->round->forks[philo->fork1])), NULL);
	//LOCK THE FORK2, OR IS ERROR -2
	if (pthread_mutex_lock(&(philo->round->forks[philo->fork2])) != 0)
	{
		pthread_mutex_unlock(&(philo->round->forks[philo->fork1]));
		return (philo->round->is_error = 2, NULL);
	}
	//PRINT FORK2 IS TAKEN
	print_log('e', philo);
	//BOTH FORKS ARE TAKEN AND UPDATE LAST_EAT, OR UNLOCK FORKS AND ERROR -3
	if (gettimeofday(&(philo->last_eat), NULL) != 0)
	{
		//NOW UNLOCK FORK1 AND FORK2
		pthread_mutex_unlock(&(philo->round->forks[philo->fork2]));
		pthread_mutex_unlock(&(philo->round->forks[philo->fork1]));
		return (philo->round->is_error = 3, NULL);
	}
	//USLEEP FOR TIME TO EAT
	// printf("t_eat %d\n", philo->round->t_eat);
	ft_usleep(philo->round->t_eat);
	// printf("now print s\n");
	//EATING DONE, UNLOCK THE FORKS
	// printf("fork2 %d\n", philo->fork2);
	pthread_mutex_unlock(&(philo->round->forks[philo->fork2]));
	pthread_mutex_unlock(&(philo->round->forks[philo->fork1]));
	// printf("now print after unlock s\n");

	//INCREASING COUNT EAT
	// printf("cnt eat %d\n", philo->cnt_eat);
	philo->cnt_eat++;
	// printf("cnt eat after %d\n", philo->cnt_eat);

	//THEN GO SLEEP FOR T_SLEEP
	print_log('s', philo);
	// printf("printlogs\n");
	ft_usleep(philo->round->t_sleep);
	print_log('t', philo);
	return (NULL);
}

//TAKE FORK OF INDEX I, I+1
void	*thread_routine(void *philo)
{
	t_philo	*philo_s;

	philo_s = (t_philo *)philo;
	
	// printf("thread_routine ID %d\n", philo_s->id);
	// printf("thread_routine STATE %d\n", philo_s->state);
	// printf("terminate %d\n", philo_s->round->terminate);
	// printf("is_error %d\n", philo_s->round->is_error);
	philo_s->fork1 = philo_s->id + (philo_s->id % 2 == 1);
	philo_s->fork2 = philo_s->id + (philo_s->id % 2 == 0);
	// printf("fork1 %d\n", philo_s->fork1);
	// printf("fork2 %d\n", philo_s->fork2);

	//IF LAST PHILO
	if (philo_s->id == philo_s->round->n_philo - 1)
	{
		//IF LAST PHILO GET UNEXISTING FORK, THEN FORK = 0;
		if (philo_s->fork1 == philo_s->round->n_philo)
			philo_s->fork1 = 0;
		else if (philo_s->fork2 == philo_s->round->n_philo)
			philo_s->fork2 = 0;
	}
	// printf("hello\n");
	// printf("n_philo %d\n", philo_s->round->n_philo);

	//IF NO TERMINATE OR ERROR, RUN LOOP ROUTINE
	while (!philo_s->round->terminate && !philo_s->round->is_error)
	{
		// printf("one step before loop_routine \n");

		loop_routine(philo_s);
		//IF ONLY ONE PHILO, BREAK;
		if (philo_s->round->n_philo == 1)
			break ;
	}
	return (NULL);
}

static void	print_str(char str, long stamp, t_philo *philo_s)
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

	//LOCK MUTEX TO PROTECT THIS FUNCTION, OR -4
	// printf("heyyy\n");
	// printf("mutexlock %d\n", pthread_mutex_lock(&(philo_s->round->print_m)));
	// printf("heyyaaaa\n");
	if (pthread_mutex_lock(&(philo_s->round->print_m)) != 0)
	{
		philo_s->round->is_error = 4;
		return ;
	}
	//GET THE CURRENT TIME
	stamp = get_timestamp(philo_s->round->current);
	// printf("STAMP %d\n", stamp);
	//GET_TIMESTAMP DOESN'T RETURN -1 THO?
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
	// printf("right before print str\n");
	
	// printf("str %c\n", str);
	// printf("stamp %d\n", stamp);

	print_str(str, stamp, philo_s);
	//IF STR IS A(ALL) OR D(DIE), UNLOCK MUTEX AND RETURN
	// printf("terminate changed in print_log\n");
	terminate = (str == 'a') || (str == 'd');
	if (pthread_mutex_unlock(&(philo_s->round->print_m)) != 0)
		philo_s->round->is_error = 6;
}
