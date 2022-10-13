/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 17:23:13 by ahammoud          #+#    #+#             */
/*   Updated: 2022/10/13 16:43:54 by ahammoud         ###   ########.fr       */
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

void	check_starvation(t_var *var, long lastmeal, int id)
{
	long	tdeath;

	tdeath = ft_time();
	if ((tdeath - lastmeal) / 1000 > var->td / 1000)
		ft_print(var, id, 1);
}

void	ft_free(t_var *var)
{
	free(var->philo);
	free(var->fork);
}

void	leaks(void)
{
	system("leaks -q philo\n");
}
