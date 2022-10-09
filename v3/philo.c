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

long	ft_takefork(t_var *var, int id)
{

	pthread_mutex_lock(&var->fork[id - 1]);
	printf("\ntakefor right \n");
	pthread_mutex_unlock(&var->fork[id - 1]);
	pthread_mutex_lock(&var->fork[(id % var->nf)]);
	printf("\ntakefor left\n");
	pthread_mutex_unlock(&var->fork[(id % var->nf)]);



	return (0);
}


void	*ft_create(void *arg)
{
	t_var	*var;
	t_philo *philo;
	int x;
	int	id;

	var = arg;
	pthread_mutex_lock(&var->mutex);
	id = var->i++ + 1;  
	pthread_mutex_unlock(&var->mutex);
	philo = var->philo;
	x = id % var->nf;
	while(1)
	{
		ft_takefork(var, id);
		break;
	}
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
