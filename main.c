/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:15:01 by slampine          #+#    #+#             */
/*   Updated: 2023/07/26 14:48:16 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long long ft_abs_time(void)
{
	struct timeval cur_time;
	long long s;
	long u;
	gettimeofday(&cur_time, NULL);
	s = (unsigned long long)cur_time.tv_sec * 1000;
	u = cur_time.tv_usec / 1000;
	printf("tv.sec is %lu\n",cur_time.tv_sec);
	printf("s is %llu, u is %lu, s + u is %llu\n",s,u,s+u);
	return (s + u);
}
void *routine(void *data)
{
	t_philo *self;
	self = (t_philo *)data;
	int i = 3;
	while (i)
	{
		printf("My id is %i\n",self->id);
		printf("Works\n");
		printf("Last ate at %lu",self->last_ate);
		i--;
	}
	return(0);
}
void init_data(t_data *data, char **argv)
{
	data->begin = ft_abs_time();
	data->num_of_pihlos = atoi(argv[1]);
	data->time_die = atoi(argv[2]);
	data->time_eat = atoi(argv[3]);
	data->time_sleep = atoi(argv[4]);
}
int init_philo(t_philo **philo, t_data *data)
{
	int i;
	i = 0;
	while (i < data->num_of_pihlos)
	{
		printf("Philo is at address %p\n",philo);
		philo[i] = malloc(sizeof(t_philo));
		philo[i]->id = i + 1;
		philo[i]->last_ate = data->begin;
		philo[i]->meals_to_eat = -1;
		philo[i]->lfork = i + 1;
		philo[i]->rfork = i + 2;
		if (i + 2 > data->num_of_pihlos)
			philo[i]->rfork = 1;
		philo[i]->data = data;
		printf("Philo %i was created at %p, ate last at %llu\n",philo[i]->id, philo[i], philo[i]->last_ate);
		printf("Has access to forks lfork %i and rfork %i\n",philo[i]->lfork,philo[i]->rfork);
		i++;
	}
	printf("init philo ended, %i\n",philo[0]->id);
	return (1);
}

int ft_init(t_data **data, t_philo ***philo, char **argv)
{
	*data = (t_data *)malloc(sizeof(t_data));
	if (*data == NULL)
		return (0);
	init_data(*data, argv);
	printf("Data is initialised\n");
	printf("Num is %i, began at %llu\n",(*data)->num_of_pihlos,(*data)->begin);
	*philo = (t_philo **)malloc(sizeof(*philo) * (*data)->num_of_pihlos);
	init_philo(*philo, *data);
	printf("Init_philo worked %i\n",(*philo)[0]->id);
	return (1);

}

void start_philos(t_data *data, t_philo **philo)
{
	int i;
	pthread_t *thr;

	i = 0;
	thr = malloc(sizeof(pthread_t) * data->num_of_pihlos);
	printf("Staring philos at philo address %p, %i\n",philo ,data->num_of_pihlos);
	while (i < data->num_of_pihlos)
	{
		printf("starting philo num %d\n",philo[i]->id);
		//pthread_create(thr[i], 0, routine, philo[i]);
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
int main(int argc, char **argv)
{
	t_data *data;
	t_philo **philo;
	int i;

	data = NULL;
	philo = NULL;
	i = 0;
	if (argc == 5)
		ft_init(&data, &philo, argv);
	printf("Philo is at address %p\n",philo);
	if (argc == 6)
		set_meals(philo, argv);
	if (argc < 5 )
		return(0);
	start_philos(data, philo);
	while(1)
	{
	sleep(1);
	printf("TIK\n");
	}
}