/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/28 16:46:52 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/06/02 19:30:47 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_data *data, int id, char *activity)
{
	unsigned long	time_stamp;

	time_stamp = get_time() - data->start_time;
	pthread_mutex_lock(&data->print);
	printf("%lu %d %s", time_stamp, id, activity);
	pthread_mutex_unlock(&data->print);
	return ;
}

void	sleeping(t_philo *philo)
{
	print_message(philo->data, philo->id, "is sleeping\n");
	usleep(philo->data->time_to_sleep * 1000);
	philo->eaten++;
	print_message(philo->data, philo->id, "is thinking\n");
	if (philo->eaten != philo->data->times_must_eat)
		eating((void *)philo);
}

void	*eating(void *vargp)
{
	t_philo		*philo;

	philo = (t_philo *)vargp;
	if (philo->id % 2 == 0 && philo->eaten == 0)
		usleep(10);
	philo->eat_time = get_time();
	pthread_mutex_lock(&philo->data->forks[philo->id]);
	pthread_mutex_lock(&philo->data->forks[(philo->id + 1) % philo->data->philosophers]);
	print_message(philo->data, philo->id, "is eating\n");
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->data->forks[philo->id]);
	pthread_mutex_unlock(&philo->data->forks[(philo->id + 1) % philo->data->philosophers]);
	sleeping(philo);
	return (vargp);
}

void	make_threads(t_data *data)
{
	unsigned long	i;
	t_philo			*philos;

	i = 0;
	philos = malloc((data->philosophers + 1) * sizeof(t_philo));
	if (philos == NULL)
		printf("Error: Malloc failed\n");
	printf("Making threads...\n");
	while (i < data->philosophers)
	{
		philos[i].id = i + 1;
		philos[i].data = data;
		philos[i].eat_time = 0;
		philos[i].eaten = 0;
		pthread_create(&(philos[i].thread_id), NULL, eating, (void *)&philos[i]);
		//usleep (10);
		i++;
	}
	while (i > 0)
	{
		pthread_join(philos[i].thread_id, NULL);
		i--;
	}
	//usleep(100000000);
	return ;
}

// need a thread that will check if someone dies
// need more accurate time stamps
// 1 philo should not eat and just die