/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:01:16 by slampine          #+#    #+#             */
/*   Updated: 2023/08/01 15:11:37 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_meals(t_philo ***philo, char **argv)
{
	int	i;

	i = 0;
	while (i < ft_atol(argv[1]))
	{
		(*philo)[i]->meals_to_eat = ft_atol(argv[5]);
		i++;
	}
}

int	ft_init(t_data **data, t_philo ***philo, char **argv)
{
	unsigned int	i;

	i = 0;
	*data = (t_data *)malloc(sizeof(t_data));
	if (*data == NULL)
		return (0);
	init_data(*data, argv);
	*philo = (t_philo **)malloc(sizeof(philo) * (*data)->num_of_philos);
	if (**philo == NULL)
	{
		free(*data);
		return (0);
	}
	if (init_philo(*philo, *data) == 0)
	{
		while (philo[i] != NULL)
		{
			free(philo[i]);
			i++;
		}
		free(*data);
		return (0);
	}
	return (1);
}

void	init_data(t_data *data, char **argv)
{
	data->begin = ft_abs_time();
	data->num_of_philos = ft_atol(argv[1]);
	data->time_die = ft_atol(argv[2]);
	data->time_eat = ft_atol(argv[3]);
	data->time_sleep = ft_atol(argv[4]);
}

int	init_mutexes(t_philo **philo, t_data *data)
{
	unsigned int	i;
	pthread_mutex_t	*chopstick;

	i = 0;
	chopstick = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
	if (chopstick == NULL)
	{
		while (i < data->num_of_philos)
		{
			free(philo[i]);
			i++;
		}
		free(philo);
		free(data);
		return (0);
	}
	while (i < data->num_of_philos)
	{
		pthread_mutex_init(&chopstick[i], NULL);
		philo[i]->chopstick = chopstick;
		i++;
	}
	return (1);
}

int	init_philo(t_philo **philo, t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		philo[i] = malloc(sizeof(t_philo));
		if (philo[i] == NULL)
			return (0);
		philo[i]->id = i + 1;
		philo[i]->last_ate = data->begin;
		philo[i]->meals_to_eat = -1;
		philo[i]->lchopstick = i + 1;
		philo[i]->rchopstick = i + 2;
		if (i + 2 > data->num_of_philos)
			philo[i]->rchopstick = 1;
		philo[i]->done = 0;
		philo[i]->data = data;
		i++;
	}
	if (init_mutexes(philo, data) == 0)
		return (0);
	return (1);
}
