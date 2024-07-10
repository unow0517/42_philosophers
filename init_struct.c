/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 11:47:58 by yowoo             #+#    #+#             */
/*   Updated: 2024/07/10 12:10:06 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_struct(t_program *program, int argc, char **argv)
{
    program->n_philo = ft_atoi(argv[1]);
    program->t_die = ft_atoi(argv[2]);
    program->t_eat = ft_atoi(argv[3]);
    program->t_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        program->eat_exit = ft_atoi(argv[5]);
}