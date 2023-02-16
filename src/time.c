/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <j.jesberger@heilbronn.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 20:10:12 by jjesberg          #+#    #+#             */
/*   Updated: 2023/02/16 17:39:31 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

void	get_time(int *time)
{
	struct timeval	c_time;

	gettimeofday(&c_time, NULL);
	*time = c_time.tv_sec * 1000 + c_time.tv_usec / 1000;
}

int	check_time(t_data *data)
{
	int	time;

	time = 0;
	get_time(&time);
	return (time - data->start_time);
}

int	ft_usleep(int time, t_philo *philo)
{
	int	uptime;
	int	time_diff;

	uptime = time + check_time(philo->d);
	time_diff = time;
	while (time_diff > 0)
	{
		if (is_dead(philo) && (philo->d->max_m == 0 \
		|| check_meal(philo) < philo->d->party_size))
			return (1);
		if (time_diff >= 5)
			usleep(5000);
		else
			usleep(time_diff);
		time_diff = uptime - check_time(philo->d);
	}
	if (is_dead(philo) && (philo->d->max_m == 0 \
	|| check_meal(philo) < philo->d->party_size))
		return (1);
	return (0);
}
