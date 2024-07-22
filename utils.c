/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:30:38 by yowoo             #+#    #+#             */
/*   Updated: 2024/07/22 19:49:47 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	sign;
	int	res;

	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	res = 0;
	while (*str != '\0')
	{
		if (*str >= 48 && *str <= 57)
			res = res * 10 + (*str - 48);
		else if (!(*str >= 48 && *str <= 57))
			return (sign * res);
		str++;
	}
	return (sign * res);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	get_timestamp(struct timeval current)
{
	return ((int)(get_current_time() - \
	(current.tv_sec * 1000 + current.tv_usec / 1000)));
}

int	clean(int end_mutex, t_philo *philo, t_round round, int end_threads)
{
	int	i;

	if (end_threads == -1)
		end_threads = 0;
	else
		printf("Error occured 2\n");
	printf("Cleaning\n");
	if (end_threads > 0)
	{
		round.terminate = 1;
		i = -1;
		while (++i < end_threads)
			pthread_join(philo[i].thread, NULL);
	}
	if (end_mutex == -2)
		return (0);
	i = -1;
	while (++i < end_mutex)
		pthread_mutex_destroy(&(round.forks[i]));
	pthread_mutex_destroy(&(round.print_m));
	free(round.forks);
	free(philo);
	return (0);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(50);
	return (0);
}
