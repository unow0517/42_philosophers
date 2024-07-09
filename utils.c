/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:30:38 by yowoo             #+#    #+#             */
/*   Updated: 2024/07/09 20:30:40 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
