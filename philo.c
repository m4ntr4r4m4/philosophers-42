/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 19:13:41 by ahammoud          #+#    #+#             */
/*   Updated: 2022/09/02 12:37:12 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void*	ft_create(void *arg)
{
	struct	timeval start;
    struct	timezone tz;
	int		philo;
	long		lastmeal = 0;
	long		tdeath = 1;

	t_var *var = arg;
	philo = var->i + 1;
	var->i++;
	if (var->nf % var->i == 0 )
		usleep(200 * 1000);
	while (var->death)
	{
		gettimeofday(&start,&tz);
		printf("%ld%04d philo %d is Thinking\n", start.tv_sec , (start.tv_usec) / 1000 , philo);
	
		//// create eating routine
		if ((tdeath - lastmeal) > 0 && var->death)
		{
			if (var->forks > 1)
			{
				pthread_mutex_lock(&var->mutex);
				var->forks -= 2;
				pthread_mutex_unlock(&var->mutex);
				gettimeofday(&start,&tz);
				if (var->death)
					printf("%ld%04d philo %d is eating\n",start.tv_sec , (start.tv_usec) / 1000 , philo);
				usleep(var->teat);
				pthread_mutex_lock(&var->mutex);
				var->forks += 2;
				pthread_mutex_unlock(&var->mutex);
				gettimeofday(&start,&tz);
				lastmeal = (var->teat / 1000) + (start.tv_sec * 1000) + (start.tv_usec / 1000);
				tdeath = ((var->td) / 1000) + (start.tv_sec * 1000) + (start.tv_usec / 1000);
				printf("last meal %ld\n\n tdeath %ld\n\n", lastmeal, tdeath);
			
		
	
		//// create sleeping routine
				pthread_mutex_lock(&var->mutex);
				gettimeofday(&start,&tz);
				if (var->death)
					printf("%ld%04d philo %d is sleeping\n", start.tv_sec , (start.tv_usec) / 1000 , philo);
				usleep(var->tsleep);
				pthread_mutex_unlock(&var->mutex);
			}
			else
			{
				pthread_mutex_lock(&var->mutex);
				var->death = 0;
				pthread_mutex_unlock(&var->mutex);

				gettimeofday(&start,&tz);
				printf("%ld%04d philo %d died\n",start.tv_sec , (start.tv_usec) / 1000 , philo);
				exit(0);
			}
		}
		else
		{
			pthread_mutex_lock(&var->mutex);
			var->death = 0;
			pthread_mutex_unlock(&var->mutex);
			gettimeofday(&start,&tz);
			printf("%ld%04d philo %d died\n",start.tv_sec , (start.tv_usec) / 1000 , philo);
			exit(0);
		}
	}
	return (0);
}

void	begin(t_var var)
{
	pthread_t	*philo;
	int	i;

	printf("this is number of philos = %d\n\n", var.nf);
	philo = malloc(sizeof(pthread_t) * var.nf);
	var.i = 0;
	i = 0;
	pthread_mutex_init(&var.mutex, NULL);
	while (i < var.nf)
	{
		if (pthread_create(&philo[i], NULL, &ft_create, &var) != 0)
			return ;
		i++;
	}
	i = 0;
	while (i < var.nf)
	{
		pthread_join(philo[i], NULL);
		i++;
	}

	pthread_mutex_destroy(&var.mutex);
	var.nf = 0;
	free(philo);
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
