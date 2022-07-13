/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/23 18:08:37 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/07/13 17:15:22 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

static void	*die_thread(void *vargp)
{
	t_philo			**philos;
	unsigned long	i;

	philos = vargp;
	while (42)
	{
		i = 0;
		while (i < (*philos)[0].data->philosophers)
		{
			if (die_check(&(*philos)[i]) == 1)
				return (NULL);
			i++;
		}
		if (casualty(&(*philos)[0]))
			return (NULL);
		usleep(100);
	}
}

static	void	*loop(void *vargp)
{
	t_philo			*philo;
	unsigned long	sleep_time;

	philo = (t_philo *)vargp;
	sleep_time = philo->data->time_to_eat / 2;
	if (sleep_time > 200)
		sleep_time = 200;
	if (philo->id % 2 == 0)
		beauty_sleep(philo, sleep_time);
	while (philo_still_eating(philo))
	{
		if (eat_spaghetti(philo) == 0)
			return (NULL);
		if (sleep_and_think(philo) == 0)
			return (NULL);
	}
	return (NULL);
}

static int	create_threads(t_data *data, t_philo **philos)
{
	unsigned long	i;

	i = 0;
	data->start_time = get_time();
	while (i < data->philosophers)
	{
		if (pthread_create(&(*philos)[i].tid, NULL, loop, &(*philos)[i]) != 0)
			return (0);
		i++;
	}
	if (pthread_create(&data->die_tid, NULL, die_thread, &(*philos)) != 0)
		return (0);
	return (1);
}

static int	join_threads(t_data *data, t_philo **philos)
{
	unsigned long	i;

	i = 0;
	while (i < data->philosophers)
	{
		if (pthread_join((*philos)[i].tid, NULL) != 0)
			return (0);
		i++;
	}
	pthread_mutex_lock(&(*philos)[0].data->eat_dead);
	if ((*philos)[0].data->done == 0)
		(*philos)[0].data->done = 1;
	pthread_mutex_unlock(&(*philos)[0].data->eat_dead);
	if (pthread_join((*philos)[0].data->die_tid, NULL) != 0)
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_philo		*philos;

	if (!error_check(argc, argv))
		return (1);
	if (!parsing(argc, argv, &data, &philos))
		return (1);
	if (!create_threads(&data, &philos))
		return (print_return("Error: Creating threads failed", 1));
	if (!join_threads(&data, &philos))
		return (print_return("Error: Joining threads failed", 1));
	destroy_mutexes(&data);
	free(data.sporks);
	free(philos);
	return (0);
}
