/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:29:51 by jjesberg          #+#    #+#             */
/*   Updated: 2023/02/13 21:11:14 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <pthread.h>
# include <errno.h>
# include <sys/time.h>

# define ARGC_ERROR			11
# define NEGATIV_ARG_ERROR	12
# define NAN_ERROR			13
# define MALLOC_ERROR		14
# define PTHREAD_ERROR		15

typedef struct s_data
{
	int				_error;
	int				finished;
	bool			is_dead;
	bool			*fork_rdy;
	int				start_time;
	int				party_size;
	int				die_t;
	int				eat_t;
	int				sleep_t;
	int				max_m;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	test_mutex;
	pthread_mutex_t	*forks;
	pthread_mutex_t	meal_mutex;
	pthread_t		*thread;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				meal_count;
	int				start_meal;
	int				deathline;
	t_data			*d;
}	t_philo;

//utils.c
int		ft_atoi(const char *str);
int		ft_isdigit(int n);
void	*ft_memset(void *s, int c, size_t len);

//time.c
int		ft_usleep(int waiting_time, t_philo *philo);
int		check_time(t_data *data);
void	get_time(int *time);

//error.c
int		p_error(int error);

//philo.c
int		start_philo(char **argv, int argc);

//init.c
t_data	*init_data(char **argv, int argc);

//routine.c
void	*routine(void *param);
bool	is_dead(t_philo *philo);
int		check_meal(t_philo *philo);

//forks.c
void	drop_forks(pthread_mutex_t *fork_l, \
pthread_mutex_t *fork_r, t_philo *philo);
bool	take_fork(bool status, pthread_mutex_t *fork, \
t_philo *philo, int index);
int		take_forks(t_philo *philo, \
pthread_mutex_t *l_fork, pthread_mutex_t *r_fork);

#endif