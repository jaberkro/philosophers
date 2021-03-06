/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/26 11:04:08 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/07/12 16:08:14 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <unistd.h>

unsigned long	get_time(void)
{
	unsigned long	current_time;
	struct timeval	time_struct;

	if (gettimeofday(&time_struct, NULL) < 0)
		return (0);
	current_time = time_struct.tv_sec * 1000 + time_struct.tv_usec / 1000;
	return (current_time);
}

void	update_eat_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->eat_dead);
	philo->eat_time = get_time();
	philo->eaten++;
	pthread_mutex_unlock(&philo->data->eat_dead);
}

int	casualty(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->eat_dead);
	if (philo->data->done)
	{
		pthread_mutex_unlock(&philo->data->eat_dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->eat_dead);
	return (0);
}

void	beauty_sleep(t_philo *philo, unsigned long sleep_time)
{
	unsigned long	start_time;

	start_time = get_time();
	while (get_time() - start_time < sleep_time && !casualty(philo))
		usleep(100);
}

int	die_check(t_philo *philo)
{
	unsigned long	current_time;

	pthread_mutex_lock(&philo->data->eat_dead);
	current_time = get_time();
	if (current_time - philo->eat_time > philo->data->time_to_die && \
	(philo->eaten < philo->data->times_must_eat || \
	philo->data->times_must_eat == 0))
	{
		pthread_mutex_unlock(&philo->data->eat_dead);
		if (!print_message(philo->data, philo->id, "\x1B[31mdied\n"))
			return (1);
		pthread_mutex_lock(&philo->data->eat_dead);
		philo->data->done = 1;
		pthread_mutex_unlock(&philo->data->eat_dead);
		if (philo->data->philosophers == 1)
			pthread_mutex_unlock(&philo->data->sporks[0]);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->eat_dead);
	return (0);
}
