/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/23 18:08:37 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/07/12 14:44:56 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

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

static	void	*philo_thread(void *vargp)
{
	t_philo		*philo;

	philo = (t_philo *)vargp;
	if (philo->id % 2 == 0)
		beauty_sleep(philo, philo->data->time_to_eat / 2);
	while (philo->eaten < philo->data->times_must_eat)
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
		if (!pthread_create(&(*philos)[i].tid, NULL, philo_thread, &(*philos)[i]))
			return (0);
		i++;
	}
	if (!pthread_create(&data->die_tid, NULL, die_thread, &(*philos)))
		return (0);
	return (1);
}

static int	join_threads(t_data *data, t_philo **philos)
{
	unsigned long	i;

	i = 0;
	while (i < data->philosophers)
	{
		if (!pthread_join((*philos)[i].tid, NULL))
			return (0);
		i--;
	}
	pthread_mutex_lock(&(*philos)[0].data->eat_check);
	if ((*philos)[0].data->philosophers > 1 && (*philos)[0].data->done == 0)
		(*philos)[0].data->done = 1;
	pthread_mutex_unlock(&(*philos)[0].data->eat_check);
	if (!pthread_join((*philos)[i].data->die_tid, NULL))
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
		print_return("Error: Creating threads failed", 1);
	if (!join_threads(&data, &philos))
		print_return ("Error: Joining threads failed", 1);
	destroy_mutexes(&data);
	free(data.sporks);
	free(philos);
	return (0);
}
