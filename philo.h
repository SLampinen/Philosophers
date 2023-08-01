/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:18:15 by slampine          #+#    #+#             */
/*   Updated: 2023/08/01 14:42:04 by slampine         ###   ########.fr       */
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
	unsigned long	begin;
	unsigned int	num_of_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				status;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_to_eat;
	unsigned long	last_ate;
	int				rchopstick;
	int				lchopstick;
	int				done;
	pthread_mutex_t	*chopstick;
	t_data			*data;
}	t_philo;

unsigned long	ft_abs_time(void);
unsigned long	sim_time(unsigned long begin);
void			ft_msleep(int time);
long			ft_atol(char *str);
void			ft_free(t_philo **philo, t_data *data);
void			set_meals(t_philo ***philo, char **argv);
int				ft_init(t_data **data, t_philo ***philo, char **argv);
void			init_data(t_data *data, char **argv);
int				init_philo(t_philo **philo, t_data *data);
int				ft_monitor(t_data *data, t_philo **philo);
int				philos_are_alive(t_data *data, t_philo **philo);
int				philos_work(t_data *data, t_philo **philo);
void			ft_destroy_mutex(t_philo **philo);
#endif
