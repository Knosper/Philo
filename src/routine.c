/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 01:08:15 by jjesberg          #+#    #+#             */
/*   Updated: 2023/02/16 02:38:03 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

bool	is_dead(t_philo *philo)
{
	if (check_time(philo->d) >= philo->deathline)
	{
		pthread_mutex_lock(&philo->d->death_lock);
		if (!philo->d->is_dead)
		{
			philo->d->is_dead = true;
			printf("%i %i died\n", check_time(philo->d), philo->id + 1);
		}
		pthread_mutex_unlock(&philo->d->death_lock);
		return (1);
	}
	pthread_mutex_lock(&philo->d->death_lock);
	if (philo->d->is_dead)
	{
		pthread_mutex_unlock(&philo->d->death_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->d->death_lock);
	return (0);
}

int	check_meal(t_philo *philo)
{
	int	ret;

	pthread_mutex_lock(&philo->d->meal_mutex);
	ret = philo->d->finished;
	pthread_mutex_unlock(&philo->d->meal_mutex);
	return (ret);
}

static void	count_meals(t_philo *philo)
{
	if (philo->meal_count >= philo->d->max_m)
	{
		pthread_mutex_lock(&philo->d->meal_mutex);
		philo->d->finished = philo->d->finished + 1;
		pthread_mutex_unlock(&philo->d->meal_mutex);
	}
}

static int	eat_meal(pthread_mutex_t *fork_l, \
pthread_mutex_t *fork_r, t_philo *philo)
{
	philo->start_meal = check_time(philo->d);
	philo->deathline = philo->start_meal + philo->d->die_t;
	printf("%d %d is eating\n", philo->start_meal, philo->id + 1);
	philo->meal_count = philo->meal_count + 1;
	count_meals(philo);
	if (ft_usleep(philo->d->eat_t, philo))
	{
		drop_forks(fork_l, fork_r, philo);
		return (1);
	}
	drop_forks(fork_l, fork_r, philo);
	return (0);
}

void	*routine(void *param)
{
	t_philo			*philo;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	int				sync;

	philo = (t_philo *)param;
	l_fork = &philo->d->forks[philo->id];
	r_fork = &philo->d->forks[((philo->id + 1) % philo->d->party_size)];
	sync = philo->id % 2;
	while (!is_dead(philo) && (check_meal(philo) < philo->d->party_size \
	|| philo->d->max_m == 0))
	{
		printf("%i %i is thinking\n", check_time(philo->d), philo->id + 1);
		if (sync)
			sync = ft_usleep(philo->d->eat_t, philo);
		if (sync || take_forks(philo, l_fork, r_fork))
			break ;
		if ((philo->meal_count >= philo->d->max_m && philo->d->max_m != 0) \
		|| eat_meal(l_fork, r_fork, philo))
			break ;
		printf("%i %i is sleeping\n", check_time(philo->d), philo->id + 1);
		if (ft_usleep(philo->d->sleep_t, philo))
			break ;
	}
	return (NULL);
}
