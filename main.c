/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:15:01 by slampine          #+#    #+#             */
/*   Updated: 2023/08/08 13:33:27 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_eat(t_philo *self)
{
	pthread_mutex_lock(&self->chopstick[self->lchopstick]);
	if (self->data->status == 0)
		return (0);
	ft_print(self, "has taken a fork");
	pthread_mutex_lock(&self->chopstick[self->rchopstick]);
	if (self->data->status == 0)
		return (0);
	ft_print(self, "has taken a fork");
	pthread_mutex_lock(self->data->dead);
	if (self->data->status == 0)
		return (0);
	ft_print(self, "is eating");
	pthread_mutex_unlock(self->data->dead);
	self->last_ate = ft_abs_time();
	ft_msleep(self->data->time_eat);
	return (1);
}

void	ft_finish_eating(t_philo *self)
{
	pthread_mutex_unlock(&self->chopstick[self->lchopstick]);
	pthread_mutex_unlock(&self->chopstick[self->rchopstick]);
	if (self->data->status == 0)
		return ;
	ft_print(self, "is sleeping");
	if (self->meals_to_eat > 0)
		self->meals_to_eat--;
	if (self->meals_to_eat == 0)
		self->done = 1;
	ft_msleep(self->data->time_sleep);
	if (self->data->status == 0)
		return ;
	ft_print(self, "is thinking");
}

void	*routine(void *data)
{
	t_philo	*self;

	self = (t_philo *)data;
	if (self->id % 2)
	{
		ft_print(self, "is thinking");
		ft_msleep(1);
	}
	while (self->status)
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
	{
		ft_destroy_mutex(philo);
		ft_free(philo, data);
		return (0);
	}
	while (i < data->num_of_philos)
	{
		pthread_create(&thr[i], 0, routine, philo[i]);
		i++;
	}
	return (thr);
}

int	main(int argc, char **argv)
{
	t_data			*data;
	pthread_t		*thr;
	t_philo			**philo;

	data = NULL;
	philo = NULL;
	if (argc < 5 || argc > 6)
		return (0);
	if (ft_init(&data, &philo, argv) == 0)
	{
		printf("Error\n");
		return (0);
	}
	if (argc == 6)
		if (set_meals(&philo, argv) == 0)
			return (0);
	thr = start_philos(data, philo);
	while (ft_monitor(data, philo))
	{
		usleep(50);
	}
	ft_end(philo, data, thr);
	return (0);
}
