/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 19:13:41 by ahammoud          #+#    #+#             */
/*   Updated: 2022/08/30 16:33:59 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void*	ft_create(void *arg)
{
	t_var *var = arg;
	var->i++;
	printf("this is death %d\n", var->death);
	while (var->death)
	{
		printf("this is philo  %d\n", var->i);
		sleep(1);
		printf("philo %d is eating\n", var->i);
		sleep(1);
		printf("philo %d is sleeping\n", var->i);
	}
	return (0);
}

void	begin(t_var var)
{
	pthread_t	*philo;
	int	i;

	printf("this is nf = %d\n", var.nf);
	philo = malloc(sizeof(pthread_t) * var.nf);
	var.i = 0;
	i = 0;
	while (i < var.nf)
	{
		if (pthread_create(&philo[var.i], NULL, &ft_create, &var) != 0)
			return ;
		i++;	
	}
	i = 0;
	while (i < var.nf)
	{
		pthread_join(philo[var.i], NULL);
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
