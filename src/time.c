/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/26 11:04:08 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/06/11 15:35:22 by jaberkro      ########   odam.nl         */
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

void	beauty_sleep(unsigned long start, unsigned long sleep)
{
	while (get_time() < start + sleep)
		usleep(10);
}

// void	beauty_sleep(t_philo *philo)
// {
// 	unsigned long	to_sleep;
// 	unsigned long	starting_time;

// 	starting_time = philo->eat_time + philo->data->time_to_eat - philo->data->start_time;
// 	to_sleep = philo->data->time_to_sleep;
// 	while (42)
// 	{
// 		if (get_time() - philo->data->start_time >= starting_time + to_sleep)
// 			return ;
// 		usleep(10);
// 	}
// }

// void	fancy_eat(t_philo *philo)
// {
// 	unsigned long	to_eat;
// 	unsigned long	starting_time;

// 	starting_time = get_time();
// 	to_eat = philo->data->time_to_eat;
// 	while (42)
// 	{
// 		if (get_time() >= starting_time + to_eat)
// 			return ;
// 		usleep(10);
// 	}
// }
