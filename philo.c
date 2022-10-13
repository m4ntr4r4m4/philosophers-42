/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 19:13:41 by ahammoud          #+#    #+#             */
/*   Updated: 2022/10/10 14:06:34 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_takefork(t_var *var, int id)
{
	int	x;

	x = id % var->nf;
	pthread_mutex_lock(&var->fork[id - 1]);
	if (var->philo[id - 1].rightfork)
	{
		pthread_mutex_lock(&var->fork[x]);
		if (var->philo[x].rightfork && !var->philo[x].leftfork)
		{
			var->philo[x].rightfork = 0;
			var->philo[id - 1].leftfork = 1;
		}
	}
	if (var->philo[id - 1].leftfork && var->philo[id - 1].rightfork)
	{
		ft_print(var, id, 2);
		return (SUCCESS);
	}
	return (FAILURE);
}

int	ft_id(t_var *var)
{
	int	id;

	pthread_mutex_lock(&var->mutex);
	id = var->i++ + 1;
	pthread_mutex_unlock(&var->mutex);
	if (var->nf < 2)
		ft_print(var, id, 1);
	return (id);
}

void	*ft_create(void *arg)
{
	t_var	*var;
	int		id;
	int		eaten;
	long	lastmeal;

	var = arg;
	eaten = var->nteat;
	id = ft_id(var);
	lastmeal = var->origin;
	pthread_mutex_lock(&var->dead);
	while (var->death && eaten != 0)
	{
		pthread_mutex_unlock(&var->dead);
		check_starvation(var, lastmeal, id);
		if (ft_takefork(var, id))
		{
			lastmeal = ft_eat(var, id);
			check_starvation(var, lastmeal, id);
			ft_sleep(var, id);
			eaten--;
		}
		pthread_mutex_lock(&var->dead);
	}
	pthread_mutex_unlock(&var->dead);
	return (0);
}

void	begin(t_var var)
{
	int	i;

	var.i = 0;
	i = -1;
	var.origin = ft_time();
	while (++i < var.nf)
	{
		if (pthread_create(&var.philo[i].id, NULL, &ft_create, &var) != 0)
		{
			printf("\nERROR\n");
			return ;
		}
	}
	i = -1;
	while (++i < var.nf)
		pthread_join(var.philo[i].id, NULL);
	free(var.philo);
}

int	main(int ac, char **av)
{
	t_var	var;

	if (ac > 4 && ac <= 6)
	{
		if (!check_error(ac, av))
			exit(0);
		var = ft_init(ac, av);
		begin(var);
	}
	return (SUCCESS);
}
