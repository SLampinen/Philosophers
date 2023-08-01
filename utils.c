/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:05:20 by slampine          #+#    #+#             */
/*   Updated: 2023/08/01 15:16:51 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free(t_philo **philo, t_data *data)
{
	unsigned int	i;

	i = 0;
	free(philo[0]->chopstick);
	while (i < data->num_of_philos)
	{
		free(philo[i]);
		i++;
	}
	free(data);
	free(philo);
}

long	ft_atol(char *str)
{
	int		sign;
	long	res;
	int		index;

	res = 0;
	sign = 1;
	index = 0;
	while (str[index] == 32 || (str[index] <= 13 && str[index] >= 9))
		index++;
	if (str[index] == '-')
		sign = -1;
	if (str[index] == '-' || str[index] == '+')
		index++;
	while (str[index] >= '0' && str[index] <= '9')
	{
		res = res * 10 + (str[index] - '0');
		index++;
	}
	return (res * sign);
}

void	ft_destroy_mutex(t_philo **philo)
{
	unsigned int	i;

	i = 0;
	if (philo != NULL)
	{
		while (i < philo[0]->data->num_of_philos)
		{
			pthread_mutex_destroy(philo[i]->chopstick);
			i++;
		}
	}
}
