/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Auto Generated                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: AUTO                                    #+#    #+#             */
/*   Updated: AUTO                                    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_atoi(const char *str)
{
   int     i;
   int     sign;
   long    res;

   i = 0;
   res = 0;
   sign = 1;
   while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
       i++;
   if (str[i] == '-' || str[i] == '+')
   {
       if (str[i] == '-')
           sign = -1;
       i++;
   }
   while (str[i] >= '0' && str[i] <= '9')
   {
       res = res * 10 + (str[i] - '0');
       i++;
   }
   return ((int)(res * sign));
}

int	is_numeric(const char *str)
{
   int i;

   if (!str || !*str)
       return (0);
   i = 0;
   while (str[i])
   {
       if (str[i] < '0' || str[i] > '9')
           return (0);
       i++;
   }
   return (1);
}