/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/23 18:08:37 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/06/03 12:45:02 by jaberkro      ########   odam.nl         */
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
	make_threads(&data);
	return (0);
}

// is 020 valid input?
// and what about +20?
// "" can be given as input as well now, better not