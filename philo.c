/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 19:13:41 by ahammoud          #+#    #+#             */
/*   Updated: 2022/09/05 15:07:12 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_death(t_var *var, int philo)
{
	struct	timeval start;

	pthread_mutex_lock(&var->mutex);
	var->death = 0;
	gettimeofday(&start, NULL);
	printf("%ld%04d philo %d died\n",start.tv_sec , (start.tv_usec) / 1000 , philo);
	pthread_mutex_unlock(&var->mutex);
	exit(0);
}

void*	ft_create(void *arg)
{
//	struct	timeval start;
//    struct	timezone tz;
	t_var	*var = arg;
	int	id;

	pthread_mutex_lock(&var->mutex);
	id = var->i++ + 1;
	printf("\nthis is id %d\n", id);
	pthread_mutex_unlock(&var->mutex);
	pthread_mutex_lock(&var->mutex);
	var->philo[id % var->nf].rightfork = 0;
	var->philo[id - 1].leftfork = 1;
	printf("\n this is philo n + 1 right fork %d\n", var->philo[id % var->nf].rightfork);
	printf("\n this is philo n left fork %d\n", var->philo[id - 1].leftfork);
	pthread_mutex_unlock(&var->mutex);




	return (0);
}

void	begin(t_var var)
{
	int	i;

	printf("this is number of philos = %d\n\n", var.nf);
	var.i = 0;
	i = 0;
	pthread_mutex_init(&var.mutex, NULL);
	while (i < var.nf)
	{
		if (pthread_create(&var.philo[i].id, NULL, &ft_create, &var) != 0)
		{
			printf("\nERROR\n");
			return ;
		}
		i++;
	}
	i = 0;
	while (i < var.nf)
	{
		pthread_join(var.philo[i].id, NULL);
		i++;
	}

	pthread_mutex_destroy(&var.mutex);
	var.nf = 0;
//	free(var.philo);
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
