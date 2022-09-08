/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 19:13:41 by ahammoud          #+#    #+#             */
/*   Updated: 2022/09/08 18:34:22 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isnumeric(char *str)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
		if (str[i] < 48 || str[i] > 57)
			return (FAILURE);
	return (SUCCESS);
}

int	check_error(int ac, char **av)
{
	int	i;

	i = 0;
	while (++i < ac)
		if (!ft_isnumeric(av[i]))
			return (FAILURE);
	return (SUCCESS);
}

t_var	ft_init(int ac,	char **av)
{
	t_var	var;

	var.i = -1;
	var.nf = ft_atoi(av[1]);
	var.td = ft_atoi(av[2]) * 1000;
	var.teat = ft_atoi(av[3]) * 1000;
	var.tsleep = ft_atoi(av[4]) * 1000;
	var.forks = var.nf;
	var.death = 1;
	pthread_mutex_init(&var.dead, NULL);
	var.philo = malloc(sizeof(t_philo) * var.nf);
	if (ac > 5)
		var.nteat = ft_atoi(av[5]);
	return (var);
}

long	ft_time(void)
{
	struct timeval	start;
	long			now;

	gettimeofday(&start, NULL);
	now = (start.tv_sec * 1000) + (start.tv_usec / 1000);
	return (now);
}

void	ft_print(t_var *var, int id, int i)
{
	long	now;

	pthread_mutex_lock(&var->dead);
	now = ft_time();
	if (i == 1)
	{
		var->death = 0;
		printf("%ld philo %d died\n", now, id);
		exit(0);
	}
	else if (i == 2)
		printf("%ld philo %d has taken a fork\n", now, id);
	else if (i == 3)
		printf("%ld philo %d is eating\n", now, id);
	else if (i == 4)
		printf("%ld philo %d is sleeping\n", now, id);
	else if (i == 5)
		printf("%ld philo %d is thinking\n", now, id);
	pthread_mutex_unlock(&var->dead);
}
