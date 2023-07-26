/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:18:15 by slampine          #+#    #+#             */
/*   Updated: 2023/07/26 14:38:04 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_data
{
	unsigned long long	begin;
	int				num_of_pihlos;
	int 			time_die;
	int 			time_eat;
	int 			time_sleep;
}t_data;

typedef struct s_philo
{
	int 					id;
	int 					meals_to_eat;
	unsigned long	long	last_ate;
	int						rfork;
	int						lfork;
	t_data					*data;
} t_philo;

unsigned long long ft_abs_time(void);

#endif