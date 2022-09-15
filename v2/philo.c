/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 19:13:41 by ahammoud          #+#    #+#             */
/*   Updated: 2022/09/13 17:43:02 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_create(void *arg)
{
	t_var	*var;
	int		id;
	bool	e;
	long	lastmeal;
	
	var = arg;
	pthread_mutex_lock(&var->mutex);
	id = var->i++ +1;
	pthread_mutex_unlock(&var->mutex);
	lastmeal = var->origin;
	e = false;
	pthread_mutex_lock(&var->dead);
	while (var->death && var->philo[id - 1].eaten != 0)
	{
		pthread_mutex_unlock(&var->dead);
		check_starvation(var, lastmeal, id);
		if (ft_takefork(var, id, lastmeal, &e))
			lastmeal = ft_eat(var, id);
		if (e)
		{
			ft_sleep(var, id, &e, lastmeal);
			var->philo[id - 1].eaten--;
		}
		check_starvation(var, lastmeal, id);
		e = false;
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
	pthread_mutex_destroy(&var.mutex);
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
	free(var.philo);
	return (SUCCESS);
}
