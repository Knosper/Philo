/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:29:45 by jjesberg          #+#    #+#             */
/*   Updated: 2023/02/13 21:03:42 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

static int	check_str(char *argv, int *_error)
{
	int		j;

	j = 0;
	while (argv[j])
	{
		if (!ft_isdigit(argv[j]) && argv[j] != '-' && argv[j] != '+')
		{
			*_error = NAN_ERROR;
			return (1);
		}
		j++;
	}
	return (0);
}

static int	check_args(int argc, char **argv, int *_error)
{
	int		i;
	int		tmp;

	i = 1;
	while (i < argc)
	{
		if (check_str(argv[i], _error))
			return (1);
		tmp = ft_atoi(argv[i]);
		if (tmp <= 0)
		{
			*_error = NEGATIV_ARG_ERROR;
			return (1);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int		_error;

	_error = 0;
	if (argc < 5 || argc > 6)
		return (p_error(ARGC_ERROR));
	if (check_args(argc, argv, &_error))
		return (p_error(_error));
	if (start_philo(argv + 1, argc))
		return (1);
	return (0);
}
