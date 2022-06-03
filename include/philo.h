/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/23 18:05:19 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/06/03 12:59:06 by jaberkro      ########   odam.nl         */
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
	unsigned long	philosophers;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	unsigned long	times_must_eat;
	unsigned long	start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
}	t_data;

typedef struct s_philo {
	int				id;
	pthread_t		thread_id;
	unsigned long	eat_time;
	unsigned long	eaten;
	t_data			*data;
}	t_philo;

int				print_return(char *message, int value);
int				error_check(int argc, char **argv);

int				parsing(int argc, char **argv, t_data *data);
unsigned long	get_time(void);

void			make_threads(t_data *data);
void			*eat(void *vargp);

#endif
