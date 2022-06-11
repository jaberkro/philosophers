/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/23 18:08:37 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/06/11 15:51:53 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_fork(t_philo *philo, int right)
{
	pthread_mutex_lock(&philo->data->forks[philo->left + right]);
	if (!print_message(philo->data, philo->id, "has taken a fork\n"))
	{
		pthread_mutex_unlock(&philo->data->forks[philo->left]);
		if (right)
			pthread_mutex_unlock(&philo->data->forks[philo->right]);
		return (0);
	}
	return (1);
}

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

int	eat_spaghetti(t_philo	*philo)
{
	if (!take_fork(philo, 0))
		return (0);
	if (!take_fork(philo, 1))
		return (0);
	pthread_mutex_lock(&philo->data->eat_check);
	philo->eat_time = get_time();
	philo->eaten++;
	pthread_mutex_unlock(&philo->data->eat_check);
	if (!print_message(philo->data, philo->id, "is eating\n"))
	{
		pthread_mutex_unlock(&philo->data->forks[philo->left]);
		pthread_mutex_unlock(&philo->data->forks[philo->right]);
		return (0);
	}
	beauty_sleep(philo->eat_time, philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->data->forks[philo->left]);
	pthread_mutex_unlock(&philo->data->forks[philo->right]);
	return (1);
}

static	void	*thread(void *vargp)
{
	t_philo		*philo;

	philo = (t_philo *)vargp;
	if (philo->id % 2 == 0)
		beauty_sleep(philo->data->start_time, 50); // used to be 200
	while (philo->eaten < philo->data->times_must_eat)
	{
		if (eat_spaghetti(philo) == 0)
			return (NULL);
		if (sleep_and_think(philo) == 0)
			return (NULL);
	}
	return (NULL);
}

static void	create_threads(t_data *data, t_philo **philos)
{
	unsigned long	i;
	pthread_t		die_thread_id;

	i = 0;
	data->start_time = get_time();
	while (i < data->philosophers)
	{
		pthread_create(&(*philos)[i].thread_id, NULL, thread, &(*philos)[i]);
		i++;
	}
	pthread_create(&die_thread_id, NULL, die_thread, &(*philos));
	if (casualty((*philos)[0].data))
		return ;
	while (i > 0 && !casualty((*philos)[0].data)) // used to be i - 1
	{
		pthread_join((*philos)[i - 1].thread_id, NULL);
		i--;
	}
	if ((*philos)[0].data->philosophers > 1)
		(*philos)[0].data->done = 1;
	pthread_join(die_thread_id, NULL);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philos;

	if (!error_check(argc, argv))
		return (1);
	if (!parsing(argc, argv, &data, &philos))
		return (1);
	create_threads(&data, &philos);
	return (0);
}

// is 020 valid input?
// and what about +20?
// "" can be given as input as well now, better not?

//Works until +- 20 philosophers, above that the program slows down bit by bit.
//Possible approach: One thread extra that prints all messages that are qued (in a linked list for example).
//Now there is a beauty_sleep function.
//Removed some mutexes but realized I might need them, because now segfaults can happen again.
//main problem now is that with much philosophers, the philosopher dies at the same time it starts eating.