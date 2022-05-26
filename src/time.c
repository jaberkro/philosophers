/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/26 11:04:08 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/05/26 14:50:43 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_time(void)
{
	unsigned long	current_time;
	struct timeval	time_struct;

	if (gettimeofday(&time_struct, NULL) < 0)
		return (0);
	current_time = time_struct.tv_sec * 1000 + time_struct.tv_usec / 1000;
	return (current_time);
}
