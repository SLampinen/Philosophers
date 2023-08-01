/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:11:55 by slampine          #+#    #+#             */
/*   Updated: 2023/08/01 11:55:32 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_monitor(t_data *data, t_philo **philo)
{
	if (philos_are_alive(data, philo) == 0)
		return (0);
	if (philos_work(data, philo) == 0)
	{
		printf("Done\n");
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
			printf("%lu philo %i died, last ate %lu\n", \
			sim_time(data->begin), i + 1, philo[i]->last_ate - data->begin);
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
