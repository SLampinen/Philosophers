/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 10:47:40 by slampine          #+#    #+#             */
/*   Updated: 2023/08/08 13:30:33 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	ft_abs_time(void)
{
	struct timeval	cur_time;
	unsigned long	s;
	unsigned long	u;

	gettimeofday(&cur_time, NULL);
	s = cur_time.tv_sec * 1000;
	u = cur_time.tv_usec / 1000;
	return (s + u);
}

unsigned long	sim_time(unsigned long begin)
{
	return ((ft_abs_time()) - begin);
}

void	ft_msleep(int time)
{
	unsigned long	st_time;

	st_time = ft_abs_time();
	while (st_time + (time) > ft_abs_time())
	{
		usleep(500);
	}
}
