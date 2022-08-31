/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 19:13:41 by ahammoud          #+#    #+#             */
/*   Updated: 2022/08/31 17:13:50 by ahammoud         ###   ########.fr       */
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

	var.nf = ft_atoi(av[1]);
	var.td = ft_atoi(av[2]) * 1000;
	var.teat = ft_atoi(av[3]) * 1000;
	var.tsleep = ft_atoi(av[4]) * 1000;
	var.forks = var.nf;
	var.death = 1;
	if (ac > 5)
		var.nteat = ft_atoi(av[5]);
	return (var);
}
