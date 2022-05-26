/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/23 18:08:37 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/05/26 18:30:49 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (!error_check(argc, argv))
		return (1);
	if (!parsing(argc, argv, &data))
		return (1);
	
	// printf("%d\n", data.philos[0].to_eat);
	// if (data.error == 1)
	// 	return (1);
	// if (gettimeofday(&data.start_time, NULL) < 0)
	// {
	// 	printf("Gettimeofday failed\n");
	// 	return (1);
	// }
	// printf("%ld - Starttime of simulation in microseconds\n", \
	// data.start_time.tv_sec * 1000000 + data.start_time.tv_sec);
	return (0);
}

// is 020 valid input?
// and what about +20?
// "" can be given as input as well now, better not