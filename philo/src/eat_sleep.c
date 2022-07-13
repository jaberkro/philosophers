/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat_sleep.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/30 12:13:51 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/07/13 17:14:13 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sleep_and_think(t_philo	*philo)
{
	unsigned long	sleep_time;

	sleep_time = philo->data->time_to_sleep;
	if (!print_message(philo->data, philo->id, "\x1B[34mis sleeping\n"))
		return (0);
	beauty_sleep(philo, sleep_time);
	if (!print_message(philo->data, philo->id, "\x1B[32mis thinking\n"))
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
	if (!print_message(philo->data, philo->id, "\x1B[35mhas taken a fork\n"))
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
	if (!print_message(philo->data, philo->id, "\x1B[33mis eating\n"))
		return (release_sporks(philo, philo->left, philo->right));
	beauty_sleep(philo, philo->data->time_to_eat);
	release_sporks(philo, philo->left, philo->right);
	return (1);
}

int	philo_still_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->eat_dead);
	if (philo->eaten < philo->data->times_must_eat)
	{
		pthread_mutex_unlock(&philo->data->eat_dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->eat_dead);
	if (philo->data->times_must_eat == 0 && !casualty(philo))
	{
		return (1);
	}
	return (0);
}
