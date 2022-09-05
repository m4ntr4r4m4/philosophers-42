/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 19:13:41 by ahammoud          #+#    #+#             */
/*   Updated: 2022/09/05 18:20:38 by ahammoud         ###   ########.fr       */
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
	struct	timeval start;
	t_var	*var = arg;
	int	id;
	long	lastmeal;
	long	tdeath;

	pthread_mutex_lock(&var->mutex);
	id = var->i++ + 1;
	pthread_mutex_unlock(&var->mutex);
	
	//eating
	while(var->death)
	{
		pthread_mutex_lock(&var->mutex);
		gettimeofday(&start, NULL);
		if(var->philo[id % var->nf].rightfork)
			var->philo[id % var->nf].rightfork = 0;
		if (!var->philo[id - 1].leftfork)
			var->philo[id - 1].leftfork = 1;
		pthread_mutex_unlock(&var->mutex);

		if (var->philo[id - 1].rightfork && var->philo[id - 1].leftfork)
		{
			pthread_mutex_lock(&var->mutex);
			printf("%ld%04d philo %d is eating\n",start.tv_sec , (start.tv_usec) / 1000 , id);
			pthread_mutex_unlock(&var->mutex);

			usleep(var->teat);
			pthread_mutex_lock(&var->mutex);
			var->philo[id % var->nf].rightfork = 1;
			var->philo[id - 1].leftfork = 0;
			pthread_mutex_unlock(&var->mutex);

			lastmeal =  (start.tv_sec * 10000) + (start.tv_usec / 1000) + (var->teat / 1000);
			printf("\nphilo %d beegin eating  %ld - finish eating %ld\ntime to eat %d\n\n",id, lastmeal - (var->teat / 1000), lastmeal, var->teat / 1000);
	//		tdeath = ((var->teat) + (var->tsleep)) / 1000;
	//		lastmeal =  (start.tv_sec * 10000); 
	//sleeping
			pthread_mutex_lock(&var->mutex);
			printf("%ld%04d philo %d is sleeping\n", start.tv_sec , (start.tv_usec) / 1000 , id);
			usleep(var->tsleep);
			pthread_mutex_unlock(&var->mutex);
			/// check last meal
			gettimeofday(&start, NULL);
			tdeath = (start.tv_sec * 10000) + (start.tv_usec / 1000) - lastmeal;
			printf("this philo %d  this is lastmeal %ld time now %ld\n", id, lastmeal , tdeath);
			if (((var->td / 1000 ) - tdeath) < 0)
			{
				printf("*************** EROOOR ***************\n");
				ft_death(var, id);
				exit(0);
			}
			//
	//thinking
			pthread_mutex_lock(&var->mutex);
			printf("%ld%04d philo %d is Thinking\n", start.tv_sec , (start.tv_usec) / 1000 , id);
			pthread_mutex_unlock(&var->mutex);
			/// check last meal
			//


		}


	}



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
		usleep(2000);
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
