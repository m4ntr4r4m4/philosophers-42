/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 20:34:51 by ahammoud          #+#    #+#             */
/*   Updated: 2022/08/08 20:35:04 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_escape(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	return (i);
}

long	ft_atoi(const char *str)
{
	long		x;
	long		i;
	long		sign;
	long		t;

	i = ft_escape(str);
	sign = 1;
	x = 0;
	t = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		x = (x * 10) + str[i++] - 48;
		t = x * sign;
	}
	if (t < -2147483648 || str[i] != '\0')
		return (LONG_MIN);
	if (t > 2147483647)
		return (LONG_MAX);
	return (t);
}
