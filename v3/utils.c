/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 17:10:06 by ahammoud          #+#    #+#             */
/*   Updated: 2022/10/09 17:23:47 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_var	ft_init(int ac,	char **av)
{
	t_var	var;

	var.i = -1;
	var.nf = ft_atoi(av[1]);
	var.td = ft_atoi(av[2]) * 1000;
	var.teat = ft_atoi(av[3]) * 1000;
	var.tsleep = ft_atoi(av[4]) * 1000;
	var.death = 1;
	var.nteat = -1;
	pthread_mutex_init(&var.dead, NULL);
	pthread_mutex_init(&var.mutex, NULL);
	pthread_mutex_init(&var.print, NULL);
	var.philo = malloc(sizeof(t_philo) * var.nf);
	var.fork = malloc(sizeof(pthread_mutex_t) * var.nf);
	ft_philo_init(&var);
	if (ac > 5)
		var.nteat = ft_atoi(av[5]);
	return (var);
}

void	ft_philo_init(t_var *var)
{
	int	i;

	i = -1;
	while (++i < var->nf)
	{
		var->philo[i].eaten = var->nteat;
		var->philo[i].rightfork = 1;
		var->philo[i].leftfork = 0;
		var->philo[i].var = (struct t_var *)var;
		pthread_mutex_init(&var->fork[i], NULL);
	}
}

void	ft_print_dead(t_var *var, int id, long now)
{
	pthread_mutex_lock(&var->dead);
	var->death = 0;
	printf("%ld philo %d died\n", (now - var->origin) / 1000, id);
	pthread_mutex_unlock(&var->dead);
	exit(0);
}

void	ft_print(t_var *var, int id, int i)
{
	long	now;

	pthread_mutex_lock(&var->print);
	now = ft_time();
	if (i == 1)
		ft_print_dead(var, id, now);
	else if (i == 2)
	{
		printf("%ld philo %d has taken a fork\n", \
				(now - var->origin) / 1000, id);
		printf("%ld philo %d has taken a fork\n", \
				(now - var->origin) / 1000, id);
	}
	else if (i == 3)
		printf("%ld philo %d is eating\n", (now - var->origin) / 1000, id);
	else if (i == 4)
		printf("%ld philo %d is sleeping\n", (now - var->origin) / 1000, id);
	else if (i == 5)
		printf("%ld philo %d is thinking\n", (now - var->origin) / 1000, id);
	pthread_mutex_unlock(&var->print);
}
