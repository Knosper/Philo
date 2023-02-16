/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:27:34 by jjesberg          #+#    #+#             */
/*   Updated: 2023/02/16 02:05:15 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

int	init_mutex(t_data *data)
{
	int	i;

	if (pthread_mutex_init(&data->meal_mutex, NULL))
		return (PTHREAD_ERROR);
	if (pthread_mutex_init(&data->death_lock, NULL))
		return (PTHREAD_ERROR);
	i = 0;
	while (i < data->party_size)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (PTHREAD_ERROR);
		i++;
	}	
	return (0);
}

int	init_data_helper(t_data *data)
{
	data->fork_rdy = malloc(sizeof(bool) * (data->party_size));
	if (!data->fork_rdy)
		return (1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->party_size);
	if (!data->forks)
	{
		free(data->fork_rdy);
		return (1);
	}
	data->thread = malloc(sizeof(pthread_t) * data->party_size);
	if (!data->thread)
	{
		free(data->fork_rdy);
		free(data->forks);
		return (1);
	}
	data->fork_rdy = ft_memset(data->fork_rdy, true, data->party_size);
	data->_error = init_mutex(data);
	if (data->_error != 0)
		return (1);
	get_time(&data->start_time);
	return (0);
}

t_data	*init_data(char **argv, int argc)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->_error = MALLOC_ERROR;
	data->party_size = ft_atoi(argv[0]);
	data->die_t = ft_atoi(argv[1]);
	data->eat_t = ft_atoi(argv[2]);
	data->sleep_t = ft_atoi(argv[3]);
	if (argc >= 6)
		data->max_m = ft_atoi(argv[4]);
	else
		data->max_m = 0;
	data->is_dead = false;
	data->start_time = 0;
	data->finished = 0;
	if (init_data_helper(data))
	{
		p_error(data->_error);
		free(data);
		return (NULL);
	}
	return (data);
}
