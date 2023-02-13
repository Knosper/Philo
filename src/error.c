/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:59:59 by jjesberg          #+#    #+#             */
/*   Updated: 2023/02/13 20:37:09 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

int	p_error(int error)
{
	if (error == ARGC_ERROR)
		printf("Error args![philos][to_die][to_eat][to_sleep][max_meals]\n");
	else if (error == NEGATIV_ARG_ERROR)
		printf("Error args should be bigger then zero!\n");
	else if (error == NAN_ERROR)
		printf("Error only numbers are allowed!\n");
	else if (error == MALLOC_ERROR)
		printf("Error malloc!\n");
	else if (error == PTHREAD_ERROR)
		printf("Error init pthread!\n");
	else
		printf("new error\n");
	return (error);
}
