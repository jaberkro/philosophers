/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/12 14:18:41 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/07/12 14:41:56 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	print_message(t_data *data, int id, char *activity)
{
	unsigned long	time_stamp;

	pthread_mutex_lock(&data->print);
	time_stamp = (get_time() - data->start_time);
	pthread_mutex_lock(&data->eat_check);
	if (data->done)
	{
		pthread_mutex_unlock(&data->print);
		pthread_mutex_unlock(&data->eat_check);
		return (0);
	}
	pthread_mutex_unlock(&data->eat_check);
	printf("%lu %d %s\x1B[0m", time_stamp, id, activity);
	pthread_mutex_unlock(&data->print);
	return (1);
}

int	print_return(char *message, int value)
{
	printf("%s\n", message);
	return (value);
}
