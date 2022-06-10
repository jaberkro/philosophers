/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/23 18:05:19 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/06/10 15:58:54 by jaberkro      ########   odam.nl         */
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
	pthread_mutex_t	eat_check;
	pthread_mutex_t	casualty_check;
	int				done;
}	t_data;

typedef struct s_philo {
	int				id;
	pthread_t		thread_id;
	unsigned long	eat_time;
	unsigned long	eaten;
	unsigned long	right;
	unsigned long	left;
	t_data			*data;
}	t_philo;

int				print_return(char *message, int value);
int				error_check(int argc, char **argv);

int				parsing(int argc, char **argv, t_data *data, t_philo **philos);
unsigned long	get_time(void);

void			*eat(void *vargp);
void			*die_thread(void *vargp);
void			sleep_think(t_philo *philo);
void			beauty_sleep(t_philo *philo);
void			fancy_eat(t_philo *philo);
int				casualty(t_data *data);
void			print_message(t_data *data, int id, char *activity);

#endif
