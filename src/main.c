/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/23 18:08:37 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/05/25 18:00:30 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
	{
		printf("Wrong amount of arguments\n");
		return (1);
	}
	data = parsing(argc, argv);
	if (data.error == 1)
		return (1);
	if (gettimeofday(&data.start_time, NULL) < 0)
	{
		printf("Gettimeofday failed\n");
		return (1);
	}
	printf("%ld - Starttime of simulation in microseconds\n", \
	data.start_time.tv_sec * 1000000 + data.start_time.tv_sec);
	return (0);
}

// is 020 valid input?