/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/23 18:08:37 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/07/05 18:03:48 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (philo->id % 2 == 1)
		beauty_sleep(philo->data->time_to_eat / 2);
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
		pthread_create(&(*philos)[i].tid, NULL, philo_thread, &(*philos)[i]);
		i++;
	}
	pthread_create(&die_thread_id, NULL, die_thread, &(*philos));
	while (i > 0)
	{
		pthread_join((*philos)[i - 1].tid, NULL);
		i--;
	}
	pthread_mutex_lock(&(*philos)[0].data->eat_check);
	if ((*philos)[0].data->philosophers > 1 && (*philos)[0].data->done == 0)
		(*philos)[0].data->done = 1;
	pthread_mutex_unlock(&(*philos)[0].data->eat_check);
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
	destroy_mutexes(&data);
	free(data.sporks);
	free(philos);
	return (0);
}
