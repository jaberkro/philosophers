/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/23 18:08:37 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/06/04 19:32:57 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	make_threads(t_data *data, t_philo **philos)
{
	unsigned long	i;
	pthread_t		die_thread_id;

	i = 0;
	data->start_time = get_time();
	while (i < data->philosophers)
	{
		pthread_create(&(*philos)[i].thread_id, NULL, eat, &(*philos)[i]);
		i++;
	}
	pthread_create(&die_thread_id, NULL, die, &(*philos));
	if (casualty((*philos)[0].data))
		return ;
	while (i - 1 > 0 && !casualty((*philos)[0].data))
	{
		pthread_join((*philos)[i - 1].thread_id, NULL);
		i--;
	}
	if (casualty((*philos)[0].data))
		return ;
	pthread_mutex_lock(&data->eat_check);
	if (!casualty((*philos)[0].data))
		pthread_join(die_thread_id, NULL);
	(*philos)[0].data->done = 1;
	pthread_mutex_unlock(&data->eat_check);
	return ;
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philos;

	if (!error_check(argc, argv))
		return (1);
	if (!parsing(argc, argv, &data, &philos))
		return (1);
	make_threads(&data, &philos);
	return (0);
}

// is 020 valid input?
// and what about +20?
// "" can be given as input as well now, better not