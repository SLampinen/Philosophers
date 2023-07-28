/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:18:15 by slampine          #+#    #+#             */
/*   Updated: 2023/07/28 14:02:11 by slampine         ###   ########.fr       */
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
	unsigned long 	begin;
	unsigned int	num_of_philos;
	int 			time_die;
	int 			time_eat;
	int 			time_sleep;
}t_data;

typedef struct s_philo
{
	int 			id;
	int 			meals_to_eat;
	unsigned long	last_ate;
	int				rchopstick;
	int				lchopstick;
	int				died;
	pthread_mutex_t	*chopstick;
	t_data			*data;
} t_philo;

unsigned long ft_abs_time(void);

#endif
