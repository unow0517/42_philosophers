/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 19:41:27 by yowoo             #+#    #+#             */
/*   Updated: 2024/07/10 15:44:52 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
    int             eat_exit;
    struct timeval  begin;
    int             terminate;
    int             is_error;
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
} t_philo;

//UTILS.C
int	ft_atoi(const char *str);

//CHECK_INPUT.C
//static int	is_int(char *str)
int is_inpt_ok(int argc, char **argv);

//INITS.C
void init_struct(t_round *round, int argc, char **argv);
void init_philos(t_philo *philo, t_round round);

//THREAD_ROUTINES.C
void	*thread_routine(void *philo);
