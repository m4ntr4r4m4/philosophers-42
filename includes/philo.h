/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 19:14:10 by ahammoud          #+#    #+#             */
/*   Updated: 2022/09/08 03:42:49 by ahammoud         ###   ########.fr       */
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
# include <stdbool.h>


# define SUCCESS	1
# define FAILURE	0

typedef struct s_philo{
	pthread_t		id;
	int				rightfork;
	int				leftfork;
	struct	t_var	*var;
}	t_philo;


typedef struct s_var{
	int	i;
	int	nf;
	int	td;
	int	teat;
	int	tsleep;
	int	nteat;
	int	death;
	int	forks;
	pthread_mutex_t	mutex;
	pthread_mutex_t	lfork;
	pthread_mutex_t	rfork;
	pthread_mutex_t	ate;
	pthread_mutex_t	dead;
	t_philo	*philo;
}	t_var;

long	ft_time();
long	ft_eat(t_var *var, int id);
long	ft_takefork(t_var *var, int id, bool *e);
void	ft_sleep(t_var *var, int id, bool *e);


void	*ft_creat(void *arg);
int		ft_isnumeric(char *str);
t_var	ft_init(int ac,	char **av);
int		check_error(int ac, char **av);
long	ft_atoi(const char *str);

#endif
