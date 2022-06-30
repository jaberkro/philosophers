/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat_sleep.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/30 12:13:51 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/06/30 12:18:54 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sleep_and_think(t_philo	*philo)
{
	unsigned long	sleep_time;

	sleep_time = philo->data->time_to_sleep;
	if (!print_message(philo->data, philo->id, "is sleeping\n"))
		return (0);
	beauty_sleep(philo->eat_time + philo->data->time_to_eat, sleep_time);
	if (!print_message(philo->data, philo->id, "is thinking\n"))
		return (0);
	return (1);
}

static int	release_sporks(t_philo *philo, int sporkLeft, int sporkRight)
{
	pthread_mutex_unlock(&philo->data->sporks[sporkLeft]);
	if (sporkRight != -1)
		pthread_mutex_unlock(&philo->data->sporks[sporkRight]);
	return (0);
}

static int	take_spork(t_philo *philo, int spork)
{
	pthread_mutex_lock(&philo->data->sporks[spork]);
	if (!print_message(philo->data, philo->id, "has taken a fork\n"))
		return (0);
	return (1);
}

int	eat_spaghetti(t_philo	*philo)
{
	if (!take_spork(philo, philo->left))
		return (release_sporks(philo, philo->left, -1));
	if (!take_spork(philo, philo->right))
		return (release_sporks(philo, philo->left, philo->right));
	update_eat_time(philo);
	if (!print_message(philo->data, philo->id, "is eating\n"))
		return (release_sporks(philo, philo->left, philo->right));
	beauty_sleep(philo->eat_time, philo->data->time_to_eat);
	release_sporks(philo, philo->left, philo->right);
	return (1);
}
