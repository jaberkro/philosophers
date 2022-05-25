/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/23 18:05:19 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/05/25 17:41:36 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data {
	unsigned long	inputs[5];
	struct timeval	start_time;
	int				error;
}	t_data;

t_data	parsing(int argc, char **argv);

#endif
