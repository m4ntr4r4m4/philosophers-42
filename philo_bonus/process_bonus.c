/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Auto Generated                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: AUTO                                    #+#    #+#             */
/*   Updated: AUTO                                    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	print_error(void)
{
   printf("Error\n");
   return (1);
}

void	spawn_philos(t_var *var)
{
   int   i;

   i = 0;
   while (i < var->n_philo)
   {
       var->pids[i] = fork();
       if (var->pids[i] < 0)
           exit(1);
       if (var->pids[i] == 0)
       {
           t_philo philo;
           philo.id = i + 1;
           philo.eat_count = 0;
           philo.var = var;
           life_cycle(&philo);
       }
       i++;
   }
}

void	wait_for_children(t_var *var)
{
   int   i;
   int   status;

   i = 0;
   while (i < var->n_philo)
   {
       waitpid(-1, &status, 0);
       if (WEXITSTATUS(status) != 0)
       {
           int   j;

           j = 0;
           while (j < var->n_philo)
               kill(var->pids[j++], SIGTERM);
           break;
       }
       i++;
   }
}