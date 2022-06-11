/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/28 16:46:52 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/06/11 15:45:42 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_message(t_data *data, int id, char *activity)
{
	unsigned long	time_stamp;

	time_stamp = (get_time() - data->start_time);
	pthread_mutex_lock(&data->print);
	if (data->done)
	{
		pthread_mutex_unlock(&data->print);
		return (0);
	}
	printf("%lu %d %s", time_stamp, id, activity);
	pthread_mutex_unlock(&data->print);
	return (1);
}

int	casualty(t_data *data)
{
	int	dead;

	dead = data->done;
	return (dead);
}

int	die_check(t_philo *philo)
{
	unsigned long	current_time;

	current_time = get_time();
	pthread_mutex_lock(&philo->data->eat_check);
	if (current_time - philo->eat_time > philo->data->time_to_die + 5 && \
		philo->eaten < philo->data->times_must_eat)
	{
		pthread_mutex_unlock(&philo->data->eat_check);
		if (!print_message(philo->data, philo->id, "died\n"))
			return (1);
		philo->data->done = 1;
		return (1);
	}
	pthread_mutex_unlock(&philo->data->eat_check);
	return (0);
}

void	*die_thread(void *vargp)
{
	t_philo			**philos;
	unsigned long	i;

	philos = vargp;
	while (42)
	{
		i = 0;
		while (i < (*philos)[0].data->philosophers && \
			!(*philos)[i].data->done)
		{
			if (die_check(&(*philos)[i]) == 1)
			{
				return (NULL);
			}
			i++;
		}
		if ((*philos)[0].data->done)
		{
			return (NULL);
		}
		usleep(10);
	}
}

// void	*die(void *vargp)
// {
// 	t_philo			**philos;
// 	unsigned long	i;
// 	unsigned long	philosophers;
// 	unsigned long	current_time;

// 	philos = vargp;
// 	philosophers = (*philos)[0].data->philosophers;
// 	while (42)
// 	{
// 		i = 0;
// 		while (i < philosophers)
// 		{
// 			current_time = get_time();
// 			if (philosophers == 1)
// 				usleep((*philos)[i].data->time_to_die * 1000);
// 			pthread_mutex_lock(&(*philos)[i].data->eat_check);
// 			if (((*philos)[i].eat_time > 0 && (*philos)[i].eaten != (*philos)[i].data->times_must_eat && current_time - (*philos)[i].eat_time > (*philos)[i].data->time_to_die) \
// 				|| (philosophers == 1))
// 			{
// 				print_message((*philos)[i].data, (*philos)[i].id, "died\n");
// 				(*philos)[i].data->done = 1;
// 				return (NULL);
// 			}
// 			pthread_mutex_unlock(&(*philos)[i].data->eat_check);
// 			i++;
// 		}
// 		if (casualty((*philos)[0].data))
// 			return (NULL);
// 		usleep(10);
// 	}
// }

// void	sleep_think(t_philo *philo)
// {
// 	if (casualty(philo->data))
// 		return ;
// 	print_message(philo->data, philo->id, "is sleeping\n");
// 	beauty_sleep(philo);
// 	if (casualty(philo->data))
// 		return ;
// 	print_message(philo->data, philo->id, "is thinking\n");
// 	pthread_mutex_lock(&philo->data->eat_check);
// 	if (philo->eaten != philo->data->times_must_eat && !casualty(philo->data))
// 		eat((void *)philo);
// 	pthread_mutex_unlock(&philo->data->eat_check);
// }

// void	*eat(void *vargp)
// {
// 	t_philo		*philo;

// 	philo = (t_philo *)vargp;
// 	if (philo->id % 2 == 0 && philo->eaten == 0)
// 		usleep(150); // does this cause the problem of greedy fork takers?
// 	pthread_mutex_lock(&philo->data->forks[philo->left]);
// 	if (casualty(philo->data))
// 		return (NULL);
// 	print_message(philo->data, philo->id, "has taken a fork\n");
// 	pthread_mutex_lock(&philo->data->forks[philo->right]);
// 	if (casualty(philo->data))
// 		return (NULL);
// 	print_message(philo->data, philo->id, "has taken a fork\n");
// 	pthread_mutex_lock(&philo->data->eat_check);
// 	philo->eat_time = get_time();
// 	philo->eaten++;
// 	pthread_mutex_unlock(&philo->data->eat_check);
// 	print_message(philo->data, philo->id, "is eating\n");
// 	fancy_eat(philo);
// 	pthread_mutex_unlock(&philo->data->forks[philo->left]);
// 	pthread_mutex_unlock(&philo->data->forks[philo->right]);
// 	sleep_think(philo);
// 	return (vargp);
// }

// 1 philosopher dies too early
// 9 philosophers die with a segfault