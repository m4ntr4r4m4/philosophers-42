/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 19:14:10 by ahammoud          #+#    #+#             */
/*   Updated: 2022/08/31 18:56:19 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define SUCCESS	1
# define FAILURE	0

typedef struct s_var{
	int	i;
	int	nf;
	int	td;
	int	teat;
	int	tsleep;
	int	nteat;
	int	death;
	int	forks;
	pthread_mutex_t	mutex0;
	pthread_mutex_t	mutex1;
	pthread_mutex_t	mutex2;
}	t_var;

int		ft_isnumeric(char *str);
t_var	ft_init(int ac,	char **av);
int		check_error(int ac, char **av);
long	ft_atoi(const char *str);

#endif