/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:11:55 by slampine          #+#    #+#             */
/*   Updated: 2023/08/08 13:26:55 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_monitor(t_data *data, t_philo **philo)
{
	unsigned int	i;

	i = 0;
	if (philos_are_alive(data, philo) == 0)
	{
		data->status = 0;
		ft_msleep(50);
		while (i < data->num_of_philos)
		{
			pthread_mutex_unlock(&philo[i]->chopstick[philo[i]->lchopstick]);
			pthread_mutex_unlock(&philo[i]->chopstick[philo[i]->rchopstick]);
			i++;
		}
		return (0);
	}
	if (philos_work(data, philo) == 0)
	{
		data->status = 0;
		printf("All have eaten enough, philosophy is now complete\n");
		return (0);
	}
	return (1);
}

int	philos_are_alive(t_data *data, t_philo **philo)
{
	unsigned int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		if (ft_abs_time() > philo[i]->last_ate + data->time_die)
		{
			pthread_mutex_lock(philo[i]->data->dead);
			printf("%lu %i died\n", \
			sim_time(data->begin), i + 1);
			return (0);
		}
		i++;
	}
	return (1);
}

int	philos_work(t_data *data, t_philo **philo)
{
	unsigned int	i;
	unsigned int	done;

	i = 0;
	done = 0;
	while (i < data->num_of_philos)
	{
		if (philo[i]->done == 1)
			done++;
		i++;
	}
	if (done == data->num_of_philos)
		return (0);
	return (1);
}
