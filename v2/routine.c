/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 18:38:49 by ahammoud          #+#    #+#             */
/*   Updated: 2022/09/13 17:33:35 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_eat(t_var *var, int id)
{
	long	lastmeal;

	lastmeal = ft_time();
	ft_print(var, id, 3);
	usleep(var->teat);
	if (!var->philo[id % var->nf].rightfork)
	{
		var->philo[id % var->nf].rightfork = 1;
		if (var->philo[id - 1].leftfork)
			var->philo[id - 1].leftfork = 0;
	}
	return (lastmeal);
}

long	ft_takefork(t_var *var, int id, long lm, bool *e)
{
	pthread_mutex_lock(&var->rfork);
	check_starvation(var, lm, id);
	if (var->philo[id - 1].rightfork && \
			var->philo[id % var->nf].rightfork \
			&& !var->philo[id % var->nf].leftfork)
	{
		ft_print(var, id, 2);
		var->philo[id % var->nf].rightfork = 0;
		if (!var->philo[id - 1].leftfork && var->philo[id - 1].rightfork)
		{
			var->philo[id - 1].leftfork = 1;
			ft_print(var, id, 2);
		}
		if (var->philo[id - 1].rightfork && var->philo[id - 1].leftfork)
		{
			pthread_mutex_unlock(&var->rfork);
			*e = true;
			return (1);
		}
	}
	else
		pthread_mutex_unlock(&var->rfork);
	return (0);
}

void	ft_sleep(t_var *var, int id, bool *e, long lastmeal)
{
	bool	slept;

	slept = false;
	if (*e)
	{
		check_starvation(var, lastmeal, id);
		ft_print(var, id, 4);
		*e = true;
		usleep(var->tsleep);
		slept = true;
		check_starvation(var, lastmeal, id);
	}
	if (slept)
		ft_print(var, id, 5);
}
