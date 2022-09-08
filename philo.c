/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 19:13:41 by ahammoud          #+#    #+#             */
/*   Updated: 2022/09/08 18:45:56 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_philo_init(t_var *var)
{
	int	id;

	pthread_mutex_lock(&var->mutex);
	id = var->i++ + 1;
	var->philo[id - 1].rightfork = 1;
	var->philo[id - 1].leftfork = 0;
	pthread_mutex_init(&var->rfork, NULL);
	pthread_mutex_init(&var->lfork, NULL);
	pthread_mutex_unlock(&var->mutex);
	usleep(1500);
	return (id);
}

void	*ft_create(void *arg)
{
	t_var	*var;
	int		id;
	bool	e;
	long	lastmeal;
	long	tdeath;

	var = arg;
	lastmeal = ft_time();
	id = ft_philo_init(var);
	e = false;
	pthread_mutex_lock(&var->lfork);
	while (var->death)
	{
		pthread_mutex_unlock(&var->lfork);
		lastmeal = ft_takefork(var, id, &e);
		ft_sleep(var, id, &e);
		tdeath = ft_time() + var->tsleep / 1000;
		if (lastmeal != 0)
			if (tdeath - lastmeal > var->td / 1000)
				ft_print(var, id, 1);
		e = false;
		pthread_mutex_lock(&var->lfork);
	}
	pthread_mutex_unlock(&var->lfork);
	return (0);
}

void	begin(t_var var)
{
	int	i;

	var.i = 0;
	i = -1;
	pthread_mutex_init(&var.mutex, NULL);
	pthread_mutex_init(&var.ate, NULL);
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
