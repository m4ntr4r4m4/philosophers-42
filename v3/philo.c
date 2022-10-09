/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 19:13:41 by ahammoud          #+#    #+#             */
/*   Updated: 2022/10/09 16:55:02 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



long	ft_takefork(t_var *var, int id)
{

	pthread_mutex_lock(&var->fork[id - 1]);
	if (var->philo[id - 1].rightfork)
	{
		pthread_mutex_lock(&var->fork[(id % var->nf)]);
		if (var->philo[id % var->nf].rightfork && !var->philo[id % var->nf].leftfork)
		{
			var->philo[id % var->nf].rightfork = 0;
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


void	*ft_create(void *arg)
{
	t_var	*var;
	int	id;
	long	lastmeal;

	var = arg;
	pthread_mutex_lock(&var->mutex);
	id = var->i++ + 1;  
	pthread_mutex_unlock(&var->mutex);
	lastmeal = var->origin;
	pthread_mutex_lock(&var->dead);
	while(var->death)
	{
		pthread_mutex_unlock(&var->dead);
		check_starvation(var, lastmeal, id);
		if (ft_takefork(var, id))
		{
			lastmeal = ft_eat(var, id);
			check_starvation(var, lastmeal, id);
			ft_sleep(var, id, lastmeal);
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
