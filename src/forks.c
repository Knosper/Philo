/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 20:16:46 by jjesberg          #+#    #+#             */
/*   Updated: 2023/02/13 20:47:01 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

static void	drop(pthread_mutex_t *fork, t_philo *philo, int index)
{
	pthread_mutex_lock(fork);
	philo->d->fork_rdy[index] = true;
	pthread_mutex_unlock(fork);
}

void	drop_forks(pthread_mutex_t *fork_l, \
pthread_mutex_t *fork_r, t_philo *philo)
{
	drop(fork_l, philo, philo->id);
	drop(fork_r, philo, (philo->id + 1) % philo->d->party_size);
}

bool	take_fork(bool status, pthread_mutex_t *fork, t_philo *philo, int index)
{
	if (pthread_mutex_lock(fork) == 0)
	{
		if (philo->d->fork_rdy[index])
		{
			philo->d->fork_rdy[index] = false;
			printf("%i %i has taken a fork\n", \
			check_time(philo->d), philo->id + 1);
			status = true;
		}
	}
	pthread_mutex_unlock(fork);
	return (status);
}

int	take_forks(t_philo *philo, pthread_mutex_t *l_fork, pthread_mutex_t *r_fork)
{
	int	left;
	int	right;
	int	dead;

	left = 0;
	right = 0;
	dead = is_dead(philo);
	while (!dead && (!left || !right))
	{
		left = take_fork(left, l_fork, philo, philo->id);
		right = take_fork(right, r_fork, philo, \
		(philo->id + 1) % philo->d->party_size);
		dead = is_dead(philo);
	}
	if (dead && (left || right))
	{
		if (left)
			drop(l_fork, philo, philo->id);
		if (right)
			drop(r_fork, philo, (philo->id + 1) % philo->d->party_size);
	}
	return (dead);
}
