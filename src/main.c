/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/23 18:08:37 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/06/10 16:32:38 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sleep_and_think(t_philo	*philo)
{
	if (casualty(philo->data))
		return (0);
	print_message(philo->data, philo->id, "is sleeping\n");
	beauty_sleep(philo);
	if (casualty(philo->data))
		return (0);
	print_message(philo->data, philo->id, "is thinking\n");
	return (1);
}

int	eat_spaghetti(t_philo	*philo)
{
	if (casualty(philo->data))
		return (0);
	pthread_mutex_lock(&philo->data->forks[philo->left]);
	if (casualty(philo->data))
		return (0);
	print_message(philo->data, philo->id, "has taken a fork\n");
	pthread_mutex_lock(&philo->data->forks[philo->right]);
	if (casualty(philo->data))
		return (0);
	print_message(philo->data, philo->id, "has taken a fork\n");
	pthread_mutex_lock(&philo->data->eat_check);
	philo->eat_time = get_time();
	philo->eaten++;
	pthread_mutex_unlock(&philo->data->eat_check);
	print_message(philo->data, philo->id, "is eating\n");
	fancy_eat(philo);
	pthread_mutex_unlock(&philo->data->forks[philo->left]);
	pthread_mutex_unlock(&philo->data->forks[philo->right]);
	return (1);
}

static	void	*thread(void *vargp)
{
	t_philo		*philo;

	philo = (t_philo *)vargp;
	if (philo->id % 2 == 0)
		usleep(100);
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
	while (i < data->philosophers)
	{
		pthread_create(&(*philos)[i].thread_id, NULL, thread, &(*philos)[i]);
		i++;
	}
	pthread_create(&die_thread_id, NULL, die_thread, &(*philos));
	if (casualty((*philos)[0].data))
		return ;
	while (i - 1 > 0 && !casualty((*philos)[0].data))
	{
		pthread_join((*philos)[i - 1].thread_id, NULL);
		i--;
	}
	pthread_mutex_lock(&(*philos)[0].data->casualty_check);
	(*philos)[0].data->done = 1;
	pthread_mutex_unlock(&(*philos)[0].data->casualty_check);
	pthread_join(die_thread_id, NULL);
}

// static void	make_threads(t_data *data, t_philo **philos)
// {
// 	unsigned long	i;
// 	pthread_t		die_thread_id;

// 	i = 0;
// 	data->start_time = get_time();
// 	while (i < data->philosophers)
// 	{
// 		pthread_create(&(*philos)[i].thread_id, NULL, eat, &(*philos)[i]);
// 		i++;
// 	}
// 	pthread_create(&die_thread_id, NULL, die, &(*philos));
// 	if (casualty((*philos)[0].data))
// 		return ;
// 	while (i - 1 > 0 && !casualty((*philos)[0].data))
// 	{
// 		//printf("waiting\n");
// 		pthread_join((*philos)[i - 1].thread_id, NULL);
// 		i--;
// 	}
// 	if (casualty((*philos)[0].data))
// 		return ;
// 	pthread_mutex_lock(&data->eat_check);
// 	if (!casualty((*philos)[0].data))
// 		pthread_join(die_thread_id, NULL);
// 	(*philos)[0].data->done = 1;
// 	pthread_mutex_unlock(&data->eat_check);
// 	return ;
// }

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philos;

	if (!error_check(argc, argv))
		return (1);
	if (!parsing(argc, argv, &data, &philos))
		return (1);
	//make_threads(&data, &philos);
	create_threads(&data, &philos);
	return (0);
}

// is 020 valid input?
// and what about +20?
// "" can be given as input as well now, better not