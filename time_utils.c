/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 10:47:40 by slampine          #+#    #+#             */
/*   Updated: 2023/08/02 16:18:03 by slampine         ###   ########.fr       */
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
	while (time)
	{
		usleep(50);
		usleep(50);
		time--;
	}
}
