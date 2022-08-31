/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 19:13:41 by ahammoud          #+#    #+#             */
/*   Updated: 2022/08/31 18:54:09 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void*	ft_create(void *arg)
{
	struct timeval tv;
	struct timeval start;
    struct timezone tz;
	t_var *var = arg;
	int	philo;

	gettimeofday(&tv,&tz);
	philo = var->i + 1;
	var->i++;
	//printf("this is death %d\n", var->death);
	while (var->death)
	{
		gettimeofday(&start,&tz);
		printf("%ld%d philo %d is Thinking\n", start.tv_sec , (start.tv_usec) / 1000 , philo);
	
		//// create eating routine
		if (var->forks)
		{
			pthread_mutex_lock(&var->mutex);
			var->forks--;
			gettimeofday(&start,&tz);
			printf("%ld%d philo %d is eating\n",start.tv_sec , (start.tv_usec) / 1000 , philo);
			usleep(var->teat);
			var->forks++;
			pthread_mutex_unlock(&var->mutex);
		}
		//// create sleeping routine
		pthread_mutex_lock(&var->mutex);
		gettimeofday(&start,&tz);
		printf("%ld%d philo %d is sleeping\n", start.tv_sec , (start.tv_usec) / 1000 , philo);
		usleep(var->tsleep);
		pthread_mutex_unlock(&var->mutex);
	}
	gettimeofday(&start,&tz);
	if(!var->death)
		printf("%ld%d philo %d died\n",start.tv_sec , (start.tv_usec) / 1000 , philo);
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
