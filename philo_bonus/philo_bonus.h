/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Auto Generated                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: AUTO                                    #+#    #+#             */
/*   Updated: AUTO                                    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <signal.h>

typedef struct s_var
{
   int      n_philo;
   long     time_to_die;
   long     time_to_eat;
   long     time_to_sleep;
   int      must_eat;
   pid_t    *pids;
   sem_t    *forks;
   sem_t    *print;
   sem_t    *meal_check;
   long     start_time;
}            t_var;

typedef struct s_philo
{
   int      id;
   long     last_meal;
   int      eat_count;
   t_var    *var;
}            t_philo;

long   get_time(void);
void   ft_usleep(long time_ms);
void   print_action(t_var *var, int id, char *str);
void   *monitor_death(void *arg);
void   life_cycle(t_philo *philo);
int    parse_args(int ac, char **av, t_var *var);
void   init_semaphores(t_var *var);
void   cleanup(t_var *var);

int    print_error(void);
void   spawn_philos(t_var *var);
void   wait_for_children(t_var *var);
void   perform_actions(t_philo *philo);

int    ft_atoi(const char *str);
int    is_numeric(const char *str);

#endif