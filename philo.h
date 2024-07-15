/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 19:41:27 by yowoo             #+#    #+#             */
/*   Updated: 2024/07/15 20:29:40 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>

typedef struct s_round
{
    int             n_philo;
    int             t_die;
    int             t_eat;
    int             t_sleep;
    int             n_must_eat; //OPTIONAL ARGUMENT, -1 if not given
    struct timeval  begin;
    int             terminate;
    int             is_error;
	pthread_mutex_t	print_m; //TO PROTECT PRINT_STR
	pthread_mutex_t	*forks;
	struct timeval	current;
} t_round;

enum e_state
{
    THINK,
    EAT,
    SLEEP
};

typedef struct s_philo
{
    int             id;
    enum e_state    state;
    struct timeval  last_eat;
    pthread_t       thread;
    t_round         *round;
    int             cnt_eat;
    int             fork1;
    int             fork2;
} t_philo;

//CHECK_INPUT.C
//static        int	is_int(char *str)
int             is_inpt_ok(int argc, char **argv);

//INITS.C
void            init_struct(t_round *round, int argc, char **argv);
void            init_philos(t_philo **philo, t_round *round);

//MAIN.C
int main(int argc, char **argv);

//MONITOR.C
void	*monitor_death_eat(void *philo);

//THREAD_ROUTINES.C
//static void   *loop_routine(t_philo *philo);
void	        *thread_routine(void *philo);
//static void	print_str(char str, long stamp, t_philo *philo_s);
void	        print_log(char str, t_philo *philo_s);

//UTILS.C
int	            ft_atoi(const char *str);
size_t	        get_current_time(void);
int	            get_timestamp(struct timeval tv_in);
int             clean(int end_mutex, t_philo *philo, t_round round, int end_threads);
int             ft_usleep(size_t milliseconds);

#endif
