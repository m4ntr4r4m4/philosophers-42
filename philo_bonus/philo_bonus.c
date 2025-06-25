/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Auto Generated                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: AUTO                                    #+#    #+#             */
/*   Updated: AUTO                                    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	parse_args(int ac, char **av, t_var *var)
{
   int i;

   if (ac < 5 || ac > 6)
       return (0);
   i = 1;
   while (i < ac)
   {
       if (!is_numeric(av[i]))
           return (0);
       i++;
   }
   var->n_philo = ft_atoi(av[1]);
   var->time_to_die = ft_atoi(av[2]);
   var->time_to_eat = ft_atoi(av[3]);
   var->time_to_sleep = ft_atoi(av[4]);
   var->must_eat = -1;
   if (ac == 6)
       var->must_eat = ft_atoi(av[5]);
   return (1);
}

void	init_semaphores(t_var *var)
{
   sem_unlink("/forks");
   sem_unlink("/print");
   sem_unlink("/meal_check");
   var->forks = sem_open("/forks", O_CREAT, 0644, var->n_philo);
   var->print = sem_open("/print", O_CREAT, 0644, 1);
   var->meal_check = sem_open("/meal_check", O_CREAT, 0644, 1);
   var->pids = malloc(sizeof(pid_t) * var->n_philo);
   var->start_time = get_time();
}

void	cleanup(t_var *var)
{
   sem_close(var->forks);
   sem_close(var->print);
   sem_close(var->meal_check);
   sem_unlink("/forks");
   sem_unlink("/print");
   sem_unlink("/meal_check");
   free(var->pids);
}

int	main(int ac, char **av)
{
   t_var   var;

   if (!parse_args(ac, av, &var))
       return (print_error());
   init_semaphores(&var);
   spawn_philos(&var);
   wait_for_children(&var);
   cleanup(&var);
   return (0);
}