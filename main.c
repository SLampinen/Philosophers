/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:15:01 by slampine          #+#    #+#             */
/*   Updated: 2023/08/01 15:13:06 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_eat(t_philo *self)
{
	if (self->id % 2)
	{
		pthread_mutex_lock(&self->chopstick[self->lchopstick]);
		printf("%lu philo %i has taken a fork\n", \
		sim_time(self->data->begin), self->id);
		if (self->rchopstick == self->lchopstick)
			return (0);
		pthread_mutex_lock(&self->chopstick[self->rchopstick]);
	}
	else
	{
		pthread_mutex_lock(&self->chopstick[self->rchopstick]);
		printf("%lu philo %i has taken a fork\n", \
		sim_time(self->data->begin), self->id);
		if (self->rchopstick == self->lchopstick)
			return (0);
		pthread_mutex_lock(&self->chopstick[self->lchopstick]);
	}
	printf("%lu philo %i has taken a fork\n", \
	sim_time(self->data->begin), self->id);
	printf("%lu philo %i is eating\n", \
	sim_time(self->data->begin), self->id);
	self->last_ate = ft_abs_time();
	ft_msleep(self->data->time_eat);
	return (1);
}

void	ft_finish_eating(t_philo *self)
{
	pthread_mutex_unlock(&self->chopstick[self->lchopstick]);
	pthread_mutex_unlock(&self->chopstick[self->rchopstick]);
	printf("%lu philo %i is sleeping\n", sim_time(self->data->begin), self->id);
	if (self->meals_to_eat > 0)
		self->meals_to_eat--;
	if (self->meals_to_eat == 0)
		self->done = 1;
	ft_msleep(self->data->time_sleep);
	printf("%lu philo %i is thinking\n", sim_time(self->data->begin), self->id);
}

void	*routine(void *data)
{
	t_philo	*self;

	self = (t_philo *)data;
	if (self->id % 2)
	{
		printf("%lu philo %i is thinking\n", \
		sim_time(self->data->begin), self->id);
		ft_msleep(1);
	}
	while (1)
	{
		if (ft_eat(self))
			ft_finish_eating(self);
		else
			break ;
	}
	return (NULL);
}

pthread_t	*start_philos(t_data *data, t_philo **philo)
{
	unsigned int	i;
	pthread_t		*thr;

	i = 0;
	thr = malloc(sizeof(pthread_t) * data->num_of_philos);
	if (thr == NULL)
		return (0);
	while (i < data->num_of_philos)
	{
		pthread_create(&thr[i], 0, routine, philo[i]);
		i++;
	}
	return (thr);
}

int	main(int argc, char **argv)
{
	t_data		*data;
	pthread_t	*thr;
	t_philo		**philo;

	data = NULL;
	philo = NULL;
	if (argc >= 5)
	{
		if (ft_init(&data, &philo, argv) == 0)
		{
			printf("Malloc error\n");
			return (0);
		}
	}
	if (argc == 6)
		set_meals(&philo, argv);
	thr = start_philos(data, philo);
	if (thr == NULL)
		{
			ft_destroy_mutex(philo);
			ft_free(philo, data);
			return (0);
		}
	while (ft_monitor(data, philo))
	{}
	free(thr);
	ft_destroy_mutex(philo);
	ft_free(philo, data);
	return (0);
}
