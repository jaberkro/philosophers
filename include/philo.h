/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/23 18:05:19 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/05/28 17:48:03 by jaberkro      ########   odam.nl         */
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

typedef struct s_philo {
	int			id;
	pthread_t	thread_id;
	int			eat_time;
	int			to_eat;
	int			eaten;
}	t_philo;

typedef struct s_data {
	unsigned long	philosophers;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	unsigned long	times_must_eat;
	unsigned long	start_time;
	t_philo			*philos;
	int				*forks;
	pthread_mutex_t	print;
}	t_data;

int				print_return(char *message, int value);
int				error_check(int argc, char **argv);

int				parsing(int argc, char **argv, t_data *data);
unsigned long	get_time(void);

void			make_threads(t_data data);

#endif
