/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/28 16:46:52 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/06/03 12:58:50 by jaberkro      ########   odam.nl         */
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

void	sleep_think(t_philo *philo)
{
	print_message(philo->data, philo->id, "is sleeping\n");
	usleep(philo->data->time_to_sleep * 1000);
	philo->eaten++;
	print_message(philo->data, philo->id, "is thinking\n");
	if (philo->eaten != philo->data->times_must_eat)
		eat((void *)philo);
}

void	*eat(void *vargp)
{
	t_philo		*philo;
	int			right_fork;

	philo = (t_philo *)vargp;
	if (philo->id % 2 == 0 && philo->eaten == 0)
		usleep(20);
	right_fork = (philo->id) % philo->data->philosophers;
	pthread_mutex_lock(&philo->data->forks[philo->id - 1]);
	print_message(philo->data, philo->id, "has taken a fork\n");
	pthread_mutex_lock(&philo->data->forks[right_fork]);
	print_message(philo->data, philo->id, "has taken a fork\n");
	philo->eat_time = get_time();
	print_message(philo->data, philo->id, "is eating\n");
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->data->forks[philo->id - 1]);
	pthread_mutex_unlock(&philo->data->forks[right_fork]);
	sleep_think(philo);
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
		pthread_create(&(philos[i].thread_id), NULL, eat, (void *)&philos[i]);
		i++;
	}
	while (i > 0)
	{
		pthread_join(philos[i].thread_id, NULL);
		i--;
	}
	return ;
}

// need a thread that will check if someone dies
// need more accurate time stamps