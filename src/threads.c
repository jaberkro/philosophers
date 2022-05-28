/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/28 16:46:52 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/05/28 19:50:42 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*say_hi(void *vargp)
{
	t_data		*data;
	static int	i = 0;

	data = NULL;
	//pthread_mutex_lock(&data->print);
	//printf("locked mutex...\n");
	data = (t_data *)vargp;
	printf("Hi from philo %d\n", i);
	i++;
	//pthread_mutex_unlock(&data->print);
	return (vargp);
}

void	make_threads(t_data data)
{
	unsigned long	i;

	i = 0;
	printf("Making threads...\n");
	pthread_mutex_init(&data.print, NULL);
	while (i < data.philosophers)
	{
		pthread_create(&data.philos->thread_id, NULL, say_hi, (void *)&data);
		usleep(10);
		i++;
	}
	return ;
}
