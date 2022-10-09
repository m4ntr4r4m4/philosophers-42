/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 15:45:30 by ahammoud          #+#    #+#             */
/*   Updated: 2022/10/09 17:26:27 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_time(void)
{
	struct timeval	start;

	if (gettimeofday(&start, NULL))
		return (0);
	return ((start.tv_sec * 1000000) + (start.tv_usec));
}

void	ft_time_sleep(int time)
{
	long	now;

	now = ft_time();
	while (true)
	{
		if (ft_time() - now >= time)
			break ;
		usleep(100);
	}
}

void	ft_sleep(t_var *var, int id, long lastmeal)
{
	ft_print(var, id, 4);
	ft_time_sleep(var->teat);
	ft_print(var, id, 5);
}

void	ft_dropfork(t_var *var, int id)
{
	int	x;

	x = id % var->nf;
	if (var->philo[id - 1].leftfork)
	{
		if (!var->philo[x].rightfork && !var->philo[x].leftfork)
		{
			var->philo[x].rightfork = 1;
			var->philo[id - 1].leftfork = 0;
		}
		pthread_mutex_unlock(&var->fork[x]);
	}
	pthread_mutex_unlock(&var->fork[id - 1]);
}

long	ft_eat(t_var *var, int id)
{
	long	lastmeal;

	lastmeal = ft_time();
	ft_print(var, id, 3);
	ft_time_sleep(var->teat);
	ft_dropfork(var, id);
	return (lastmeal);
}
