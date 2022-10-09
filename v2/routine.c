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
	ft_print(var, id, lastmeal,3);
	ft_time_sleep(var->teat);
	pthread_mutex_lock(&var->rfork);
	if (!var->philo[id % var->nf].rightfork && var->philo[id - 1].leftfork)
	{
		var->philo[id % var->nf].rightfork = 1;
		var->philo[id - 1].leftfork = 0;
	}
	pthread_mutex_unlock(&var->rfork);
	return (lastmeal);
}

long	ft_takefork(t_var *var, int id, long lm, bool *e)
{
	pthread_mutex_lock(&var->rfork);
	if (var->philo[id - 1].rightfork && \
			var->philo[id % var->nf].rightfork \
			&& !var->philo[id % var->nf].leftfork)
	{
		var->philo[id % var->nf].rightfork = 0;
		if (!var->philo[id - 1].leftfork && var->philo[id - 1].rightfork)
		{
			var->philo[id - 1].leftfork = 1;
			ft_print(var, id, ft_time(),2);
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
		ft_print(var, id, ft_time(),4);
		ft_time_sleep(var->teat);
		*e = true;
		slept = true;
	}
	if (slept)
		ft_print(var, id, ft_time(),5);
}
