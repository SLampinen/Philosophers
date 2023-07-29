/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:15:01 by slampine          #+#    #+#             */
/*   Updated: 2023/07/28 14:36:56 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long long ft_abs_time(void)
{
	struct timeval cur_time;
	unsigned long long s;
	unsigned long  long u;
	gettimeofday(&cur_time, NULL);
	s = cur_time.tv_sec * 1000;
	u = cur_time.tv_usec / 1000;
	return (s + u);
}
unsigned long long sim_time(unsigned long long begin)
{
	return(ft_abs_time() - begin);
}
void ft_msleep(int time)
{
	usleep(time * 1000);
}
void ft_eat(t_philo *self)
{
	if (self->id % 2)
	{
		printf("%llu philo %i Attempts to take lfork\n",sim_time(self->data->begin),self->id);
		fflush(stdout);
		pthread_mutex_lock(&self->chopstick[self->lchopstick]);
		printf("%llu philo %i has taken a left fork\n",sim_time(self->data->begin),self->id);
		fflush(stdout);
		if (self->rchopstick == self->lchopstick)
			exit(0) ;
		printf("%llu philo %i Attempts to take rfork\n",sim_time(self->data->begin),self->id);
		fflush(stdout);
		pthread_mutex_lock(&self->chopstick[self->rchopstick]);
		printf("%llu philo %i has taken a right fork\n",sim_time(self->data->begin),self->id);
		fflush(stdout);
		printf("%llu philo %i is eating\n",ft_abs_time() - self->data->begin, self->id);
		fflush(stdout);
	}
	else
	{
		printf("%llu philo %i Attempts to take rfork\n",sim_time(self->data->begin),self->id);
		fflush(stdout);
		pthread_mutex_lock(&self->chopstick[self->rchopstick]);
		printf("%llu philo %i has taken a right fork\n",sim_time(self->data->begin),self->id);
		fflush(stdout);
		if (self->rchopstick == self->lchopstick)
			exit(0) ;
		printf("%llu philo %i Attempts to take lfork\n",sim_time(self->data->begin),self->id);
		fflush(stdout);
		pthread_mutex_lock(&self->chopstick[self->lchopstick]);
		printf("%llu philo %i has taken a left fork\n",sim_time(self->data->begin),self->id);
		fflush(stdout);
		printf("%llu philo %i is eating\n",ft_abs_time() - self->data->begin, self->id);
		fflush(stdout);
	}
		ft_msleep(self->data->time_eat);
}
void ft_finish_eating(t_philo *self)
{
	pthread_mutex_unlock(&self->chopstick[self->lchopstick]);
	pthread_mutex_unlock(&self->chopstick[self->rchopstick]);
	printf("%llu philo %i is sleeping\n",sim_time(self->data->begin),self->id);
	fflush(stdout);
	self->last_ate = ft_abs_time();
	ft_msleep(self->data->time_sleep);
	printf("%llu philo %i is thinking\n",sim_time(self->data->begin),self->id);
	fflush(stdout);
}
void *routine(void *data)
{
	t_philo *self;
	self = (t_philo *)data;
	if (self->id % 2)
	{
		printf("%llu philo %i is thinking\n",sim_time(self->data->begin),self->id);
		fflush(stdout);
		ft_msleep(1);
	}
	while (1)
	{
		if (ft_abs_time() > self->last_ate + self->data->time_die && self->died == 0)
		{
			printf("%llu philo %i has died, last ate at %llu\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++\n",sim_time(self->data->begin),self->id, self->last_ate - self->data->begin);
			self->died = 1;
		}
		if (self->died == 0)
		{
			ft_eat(self);
			if (self->meals_to_eat > 0)
				self->meals_to_eat--;
			ft_finish_eating(self);
		}
	}
}
void init_data(t_data *data, char **argv)
{
	data->begin = ft_abs_time();
	data->num_of_philos = atoi(argv[1]);
	data->time_die = atoi(argv[2]);
	data->time_eat = atoi(argv[3]);
	data->time_sleep = atoi(argv[4]);
}
int init_philo(t_philo **philo, t_data *data)
{
	unsigned int i;
	pthread_mutex_t *chopstick;
	
	i = 0;
	chopstick = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
	if (chopstick == NULL)
		return (0);
	while (i < data->num_of_philos)
	{
		pthread_mutex_init(&chopstick[i],NULL);
		i++;
	}
	i = 0;
	while (i < data->num_of_philos)
	{
		//printf("Philo is at address %p\n",philo);
		philo[i] = malloc(sizeof(t_philo));
		philo[i]->id = i + 1;
		philo[i]->last_ate = data->begin;
		philo[i]->meals_to_eat = -1;
		philo[i]->lchopstick = i + 1;
		philo[i]->rchopstick = i + 2;
		if (i + 2 > data->num_of_philos)
			philo[i]->rchopstick = 1;
		philo[i]->died = 0;
		philo[i]->chopstick = chopstick;
		philo[i]->data = data;
		//printf("Philo %i was created at %p, ate last at %lu\n",philo[i]->id, philo[i], philo[i]->last_ate);
		printf("Philo %i has access to forks lfork %i and rfork %i\n",i+1 ,philo[i]->lchopstick,philo[i]->rchopstick);
		i++;
	}
	//printf("init philo ended, %i\n",philo[0]->id);
	return (1);
}

int ft_init(t_data **data, t_philo ***philo, char **argv)
{
	*data = (t_data *)malloc(sizeof(t_data));
	if (*data == NULL)
		return (0);
	init_data(*data, argv);
	//printf("Data is initialised\n");
	//printf("Num is %i, began at %lu\n",(*data)->num_of_philos,(*data)->begin);
	printf("%i philos exists, need to eat every %i ms, will eat %i ms, then sleep %ims\n",(*data)->num_of_philos, (*data)->time_die, (*data)->time_eat, (*data)->time_sleep);
	*philo = (t_philo **)malloc(sizeof(philo) * (*data)->num_of_philos);
	init_philo(*philo, *data);
	//printf("Init_philo worked\n");
	return (1);

}

void start_philos(t_data *data, t_philo **philo)
{
	unsigned int i;
	pthread_t *thr;

	i = 0;
	thr = malloc(sizeof(pthread_t) * data->num_of_philos);
	while (i < data->num_of_philos)
	{
		pthread_create(&thr[i], 0, routine, philo[i]);
		i++;
	}
}
void set_meals(t_philo **philo, char **argv)
{
	int i;

	i = 0;
	while (i < atoi(argv[1]))
	{
		(*philo)[i].meals_to_eat = atoi(argv[5]);
		i++;
	}
}
int philos_are_alive(t_data *data, t_philo **philo)
{
	unsigned int i;
	
	i = 0;
	while (i < data->num_of_philos)
	{
		if (philo[i]->died == 1)
			return (0);
		i++;
	}
	return (1);
}
int main(int argc, char **argv)
{
	t_data *data;
	t_philo **philo;

	data = NULL;
	philo = NULL;
	if (argc == 5)
		ft_init(&data, &philo, argv);
	if (argc == 6)
		set_meals(philo, argv);
		if (argc < 5)
		return (0);
	start_philos(data, philo);
	while(philos_are_alive(data, philo))
	{
	}
	fflush(stdout);
	return (0);
}