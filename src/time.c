/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 20:10:12 by jjesberg          #+#    #+#             */
/*   Updated: 2023/02/13 20:12:22 by jjesberg         ###   ########.fr       */
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

int	ft_usleep(int waiting_time, t_philo *philo)
{
	int	wake_up_time;
	int	time_left;

	wake_up_time = waiting_time + check_time(philo->d);
	time_left = waiting_time;
	while (time_left > 0)
	{
		if (is_dead(philo) && (philo->d->max_m == 0 \
		|| check_meal(philo) < philo->d->party_size))
			return (1);
		if (time_left >= 5)
			usleep(5000);
		else
			usleep(time_left);
		time_left = wake_up_time - check_time(philo->d);
	}
	if (is_dead(philo) && (philo->d->max_m == 0 \
	|| check_meal(philo) < philo->d->party_size))
		return (1);
	return (0);
}
