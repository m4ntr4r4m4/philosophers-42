/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Auto Generated                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: AUTO                                    #+#    #+#             */
/*   Updated: AUTO                                    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	perform_actions(t_philo *philo)
{
   t_var   *var;

   var = philo->var;
   sem_wait(var->forks);
   print_action(var, philo->id, "has taken a fork");
   sem_wait(var->forks);
   print_action(var, philo->id, "has taken a fork");
   sem_wait(var->meal_check);
   philo->last_meal = get_time();
   sem_post(var->meal_check);
   print_action(var, philo->id, "is eating");
   ft_usleep(var->time_to_eat);
   philo->eat_count++;
   sem_post(var->forks);
   sem_post(var->forks);
   if (var->must_eat > 0 && philo->eat_count >= var->must_eat)
       exit(0);
   print_action(var, philo->id, "is sleeping");
   ft_usleep(var->time_to_sleep);
   print_action(var, philo->id, "is thinking");
}