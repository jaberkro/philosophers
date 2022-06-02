/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/25 13:34:16 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/06/02 17:27:32 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_forks(t_data *data)
{
	unsigned long	i;

	i = 0;
	data->forks = malloc (data->philosophers * sizeof(pthread_mutex_t));
	if (data->forks == NULL)
		return (print_return("Error: malloc failed\n", 0));
	while (i < data->philosophers)
	{
		pthread_mutex_init(&(data->forks[i]), NULL);
		i++;
	}
	return (1);
}

// static int	init_philos(t_data *data)
// {
// 	unsigned long	i;

// 	i = 0;
// 	data->philos = malloc ((data->philosophers) * sizeof(t_philo));
// 	if (data->philos == NULL)
// 		return (print_return("Error: Malloc failed", 0));
// 	while (i < data->philosophers)
// 	{
// 		data->philos[i].id = i + 1;
// 		data->philos[i].eat_time = 0;
// 		data->philos[i].to_eat = data->times_must_eat;
// 		data->philos[i].eaten = 0;
// 		i++;
// 	}
// 	return (1);
// }

static unsigned long	atoul(const char *input)
{
	unsigned long	number;
	int				i;

	number = 0;
	i = 0;
	if (input[i] == '+')
		i++;
	while (input[i] >= '0' && input[i] <= '9')
	{
		number = number * 10 + input[i] - '0';
		i++;
	}
	return (number);
}

int	parsing(int argc, char **argv, t_data *data)
{
	data->philosophers = atoul(argv[1]);
	data->time_to_die = atoul(argv[2]);
	data->time_to_eat = atoul(argv[3]);
	data->time_to_sleep = atoul(argv[4]);
	data->times_must_eat = -1;
	if (argc == 6)
		data->times_must_eat = atoul(argv[5]);
	data->start_time = get_time();
	// if (!init_philos(data))
	// 	return (0);
	if (!init_forks(data))
		return (0);
	pthread_mutex_init(&(data->print), NULL);
	return (1);
}

	//printf("philos: %lu, die: %lu eat: %lu sleep: %lu times: %lu start: %lu\n", data->philosophers, data->time_to_die, data->time_to_eat, data->time_to_sleep, data->times_must_eat, data->start_time);