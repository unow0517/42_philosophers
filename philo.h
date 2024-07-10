/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 19:41:27 by yowoo             #+#    #+#             */
/*   Updated: 2024/07/10 11:53:39 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <stdio.h>


typedef struct s_program
{
    int n_philo;
    int t_die;
    int t_eat;
    int t_sleep;
    int eat_exit;
    
} t_program;

enum e_state
{
    THINK,
    EAT,
    SLEEP
};

typedef struct s_philo
{
    int id;
    enum e_state state;
    
} t_philo;

//UTILS.C
int	ft_atoi(const char *str);

//CHECK_INPUT.C
//static int	is_int(char *str)
int is_inpt_ok(int argc, char **argv);

//INIT_STRUCT.C
void init_struct(t_program *program, int argc, char **argv);