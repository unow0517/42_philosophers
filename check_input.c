/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 11:46:17 by yowoo             #+#    #+#             */
/*   Updated: 2024/07/10 12:14:04 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_int(char *str)
{
	int		i;
	long	temp;

	i = 0;
	if (str[i] == '-')
		return (0);
	if (str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	if (i > 11 || i == 0 || (i == 1 && (str[0] == '-' || str[0] == '+')))
		return (0);
	temp = ft_atoi(str);
	if (temp > 2147483647 || temp < -2147483648)
		return (0);
	return (1);
}

int is_inpt_ok(int argc, char **argv)
{
    int i;
    int cnt_wrong;
    
    if (argc != 5 && argc != 6)
	{
		write(1, "Wrong Number of Inputs\n", 23);
		return (0);
	}
    i = 1;
    cnt_wrong = 0;
    while (i < 5)
    {
        if (!is_int(argv[i]))
            cnt_wrong++;           
        i++;
    }
	if (argc == 6)
        if (!is_int(argv[5]))
			cnt_wrong++;
    if (cnt_wrong)
    {   
		write(1, "Wrong Type of Inputs\n", 22);
		return (0);    
    }
	return (1);
}
