/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:51:32 by jjesberg          #+#    #+#             */
/*   Updated: 2023/02/16 02:59:33 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

static int	join_destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->party_size)
	{
		if (pthread_join(data->thread[i], NULL) != 0)
			return (1);
		i++;
	}
	i = 0;
	pthread_mutex_destroy(&data->meal_mutex);
	pthread_mutex_destroy(&data->death_lock);
	while (i < data->party_size)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	return (0);
}

static int	init_philo_helper(t_data *data, t_philo *philo)
{
	int		i;

	i = 0;
	while (i < data->party_size)
	{
		philo[i].d = data;
		philo[i].id = i;
		philo[i].start_meal = 0;
		philo[i].meal_count = 0;
		philo[i].deathline = data->die_t;
		pthread_mutex_lock(&data->death_lock);
		pthread_mutex_unlock(&data->death_lock);
		if (i == 2)
			return (1);
		if (pthread_create(&data->thread[i], NULL, &routine, &philo[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	init_philo(t_data *data)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * data->party_size);
	if (!philo)
		return (p_error(MALLOC_ERROR));
	if (init_philo_helper(data, philo))
	{
		free(philo);
		return (p_error(PTHREAD_ERROR));
	}
	if (join_destroy(data))
	{
		free(philo);
		return (p_error(PTHREAD_ERROR));
	}
	free(philo);
	return (0);
}

int	start_philo(char **argv, int argc)
{
	t_data	*data;
	int		ret;

	ret = 1;
	data = init_data(argv, argc);
	if (!data)
		return (ret);
	ret = init_philo(data);
	free(data->forks);
	free(data->fork_rdy);
	free(data->thread);
	free(data);
	return (ret);
}
