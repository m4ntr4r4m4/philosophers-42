/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 19:13:41 by ahammoud          #+#    #+#             */
/*   Updated: 2022/09/08 04:07:12 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_time()
{
	struct	timeval	start;
	long	now;
	
	gettimeofday(&start, NULL);
	now = ( start.tv_sec * 1000) + ( start.tv_usec / 1000);
	return (now);
}

void	ft_death(t_var *var, int philo)
{
	long	now;

	pthread_mutex_lock(&var->dead);
	var->death = 0;
	now = ft_time();
	printf("%ld philo %d died\n",now , philo);
	pthread_mutex_unlock(&var->dead);
	exit(0);
}

long	ft_eat(t_var *var, int id)
{
	long	lastmeal = 0;

	pthread_mutex_lock(&var->ate);
	printf("%ld philo %d is eating\n", ft_time(), id);
	usleep(var->teat);
	lastmeal = ft_time();
//	printf("\neating philo %d this rigt fork %d this is left fork %d\n" ,id, var->philo[id - 1].rightfork, var->philo[id - 1].leftfork);




	if(!var->philo[id % var->nf].rightfork)
	{
		var->philo[id % var->nf].rightfork = 1;
		if (var->philo[id - 1].leftfork)
		{
			var->philo[id - 1].leftfork = 0;
			printf("philo %d has drop a fork\n", id);
		}
	}
	pthread_mutex_unlock(&var->ate);
//	printf("this is last meal %ld\n", lastmeal);
//	printf("\nafter eating philo %d this rigt fork %d this is left fork %d\n" ,id, var->philo[id - 1].rightfork, var->philo[id - 1].leftfork);
	return (lastmeal);
}

long	ft_takefork(t_var *var, int id, bool *e)
{
	long	lastmeal = 0;

	pthread_mutex_lock(&var->rfork);
//	printf(" ///////////// PHILO %d //////////////////// Philo + 1: %d\n", id , (id + 1 )% var->nf);
	if(var->philo[id - 1].rightfork && var->philo[id % var->nf].rightfork && !var->philo[id % var->nf].leftfork)
	{
		var->philo[id % var->nf].rightfork = 0;
		if (!var->philo[id - 1].leftfork && var->philo[id - 1].rightfork)
		{
			var->philo[id - 1].leftfork = 1;
			printf("%ld philo %d has taken a fork\n", ft_time(), id);
		}
//	printf("\nphilo %d this rigt fork %d this is left fork %d\n" ,(id ) % var->nf, var->philo[id - 1].rightfork, var->philo[id - 1].leftfork);
//	printf("\nphilo  %d this rigt fork %d this is left fork %d\n" ,(id + 1) % var->nf, var->philo[id % var->nf].rightfork, var->philo[id % var->nf].leftfork);
//	printf("\nphilo  %d this rigt fork %d this is left fork %d\n" ,(id + 2)% var->nf, var->philo[(id + 1) % var->nf].rightfork, var->philo[(id + 1) % var->nf].leftfork);
//	printf("\nphilo  %d this rigt fork %d this is left fork %d\n" ,(id + 3)% var->nf, var->philo[(id + 2) % var->nf].rightfork, var->philo[(id + 2) % var->nf].leftfork);
//
		if (var->philo[id - 1].rightfork && var->philo[id - 1].leftfork)
		{
			pthread_mutex_unlock(&var->rfork);
			lastmeal = ft_eat(var, id);
//			printf("this is last meal %ld\n", lastmeal);
			*e = true;
		}

	}
	else
		pthread_mutex_unlock(&var->rfork);


//		printf("this is last meal %ld\n", lastmeal);
	return (lastmeal);
}

void	ft_sleep(t_var *var, int id, bool *e)
{
	bool slept;

	slept = false;
	if (*e)
	{
		printf("%ld philo %d is sleeping\n", ft_time() , id);
		*e = true;
		usleep(var->tsleep);
		slept = true;
	}
	if (slept)
		printf("%ld philo %d is thinking\n", ft_time() , id);
}

void*	ft_create(void *arg)
{
	t_var	*var = arg;
	int		id;
	bool	e;
	long	lastmeal = ft_time();
	long	tdeath;

	pthread_mutex_lock(&var->mutex);
	id = var->i++ + 1;
	var->philo[id - 1].rightfork = 1;
	var->philo[id - 1].leftfork = 0;
	pthread_mutex_init(&var->rfork, NULL);
	pthread_mutex_init(&var->lfork, NULL);
	printf("philo %d created\n", id);
	pthread_mutex_unlock(&var->mutex);


	usleep(1500);
	e = false;
	

	//eating
	pthread_mutex_lock(&var->lfork);
	while(var->death)
	{
		pthread_mutex_unlock(&var->lfork);
		lastmeal = ft_takefork(var, id, &e);
//		printf("this is last meal %ld\n", lastmeal);

		ft_sleep(var, id, &e);
//		tdeath = ft_time();
	//	printf("this tdeath %ld\nthis is lastmeal %ld\n", tdeath, lastmeal);
//		if (tdeath - lastmeal > var->td && lastmeal != 0)
//			ft_death(var, id);

		tdeath = ft_time();
		tdeath += var->tsleep / 1000;
		if (lastmeal != 0)
		{
			printf("PHILO %d %ld this tdeath %ld\nthis is lastmeal %ld\n", id, tdeath - lastmeal , tdeath, lastmeal);

			if (tdeath - lastmeal > var->td / 1000)
				ft_death(var, id);
		}
		e = false;
		pthread_mutex_lock(&var->lfork);
	}
	pthread_mutex_unlock(&var->lfork);
	return (0);
}

void	begin(t_var var)
{
	int	i;

	printf("this is number of philos = %d\n\n", var.nf);
	var.i = 0;
	i = 0;
	pthread_mutex_init(&var.mutex, NULL);
	pthread_mutex_init(&var.ate, NULL);
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
