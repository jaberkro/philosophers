/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/28 16:46:52 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/06/03 20:09:21 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_data *data, int id, char *activity)
{
	unsigned long	time_stamp;

	time_stamp = (get_time() - data->start_time);
	pthread_mutex_lock(&data->print);
	printf("%lu %d %s", time_stamp, id, activity);
	pthread_mutex_unlock(&data->print);
	return ;
}

void	*die(void *vargp)
{
	t_philo			**philos;
	unsigned long	i;
	unsigned long	philosophers;
	unsigned long	current_time;

	philos = (t_philo **)vargp;
	philosophers = philos[0]->data->philosophers;
	while (42)
	{
		i = 0;
		while (i < philosophers)
		{
			current_time = get_time();
			if (((*philos)[i].eat_time > 0 && (*philos)[i].eaten != (*philos)[i].data->times_must_eat && current_time - (*philos)[i].eat_time > (*philos)[i].data->time_to_die) \
				|| (philosophers == 1))
			{
				print_message(philos[i]->data, philos[i]->id, "died\n");
				philos[i]->data->done = 1;
				return (NULL);
			}
			i++;
		}
		if (philos[0]->data->done)
		{
			return (NULL);
		}
		usleep(10);
	}
}

void	sleep_think(t_philo *philo)
{
	if (philo->data->done)
		return ;
	print_message(philo->data, philo->id, "is sleeping\n");
	beauty_sleep(philo);
	if (philo->data->done)
		return ;
	print_message(philo->data, philo->id, "is thinking\n");
	if (philo->eaten != philo->data->times_must_eat && !philo->data->done)
		eat((void *)philo);
}

void	*eat(void *vargp)
{
	t_philo		*philo;
	int			right_fork;

	philo = (t_philo *)vargp;
	if (philo->id % 2 == 0 && philo->eaten == 0)
		usleep(200);
	right_fork = (philo->id) % philo->data->philosophers;
	pthread_mutex_lock(&philo->data->forks[philo->id - 1]);
	if (philo->data->done)
		return (vargp);
	print_message(philo->data, philo->id, "has taken a fork\n");
	pthread_mutex_lock(&philo->data->forks[right_fork]);
	if (philo->data->done)
		return (vargp);
	print_message(philo->data, philo->id, "has taken a fork\n");
	philo->eat_time = get_time();
	print_message(philo->data, philo->id, "is eating\n");
	philo->eaten++;
	fancy_eat(philo);
	pthread_mutex_unlock(&philo->data->forks[philo->id - 1]);
	pthread_mutex_unlock(&philo->data->forks[right_fork]);
	sleep_think(philo);
	return (vargp);
}

void	make_threads(t_data *data)
{
	unsigned long	i;
	t_philo			*philos;
	pthread_t		die_thread_id;

	i = 0;
	philos = malloc((data->philosophers + 1) * sizeof(t_philo));
	if (philos == NULL)
		printf("Error: Malloc failed\n");
	data->start_time = get_time();
	while (i < data->philosophers)
	{
		philos[i].id = i + 1;
		philos[i].data = data;
		philos[i].eat_time = get_time();//data->start_time; // this created segfault
		philos[i].eaten = 0;
		pthread_create(&(philos[i].thread_id), NULL, eat, (void *)&philos[i]);
		i++;
	}
	pthread_create(&die_thread_id, NULL, die, (void *)&philos);
	while (i > 0)
	{
		pthread_join(philos[i].thread_id, NULL);
		i--;
	}
	philos[i].data->done = 1;
	pthread_join(die_thread_id, NULL);
	return ;
}

// 1 philosopher dies too early
// 9 philosophers die with a segfault
