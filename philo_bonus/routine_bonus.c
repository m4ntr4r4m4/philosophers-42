/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Auto Generated                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: AUTO                                    #+#    #+#             */
/*   Updated: AUTO                                    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	get_time(void)
{
   struct timeval tv;

   gettimeofday(&tv, NULL);
   return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(long time_ms)
{
   long start;

   start = get_time();
   while (get_time() - start < time_ms)
       usleep(100);
}

void	print_action(t_var *var, int id, char *str)
{
   sem_wait(var->print);
   printf("%ld %d %s\n", get_time() - var->start_time, id, str);
   sem_post(var->print);
}

void	*monitor_death(void *arg)
{
   t_philo *philo = (t_philo *)arg;
   t_var   *var = philo->var;

   while (1)
   {
       sem_wait(var->meal_check);
       if (get_time() - philo->last_meal > var->time_to_die)
       {
           print_action(var, philo->id, "died");
           exit(1);
       }
       sem_post(var->meal_check);
       usleep(1000);
   }
   return (NULL);
}

void	life_cycle(t_philo *philo)
{
   pthread_t th;

   philo->last_meal = get_time();
   if (pthread_create(&th, NULL, monitor_death, philo) != 0)
       return;
   pthread_detach(th);
   while (1)
       perform_actions(philo);
}