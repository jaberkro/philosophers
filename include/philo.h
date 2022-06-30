/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/23 18:05:19 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/06/30 12:46:16 by jaberkro      ########   odam.nl         */
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
	pthread_mutex_t	*sporks;
	pthread_mutex_t	print;
	pthread_mutex_t	eat_check;
	int				done;
}	t_data;

typedef struct s_philo {
	int				id;
	pthread_t		tid;
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
void			update_eat_time(t_philo *philo);
int				die_check(t_philo *philo);

void			*eat(void *vargp);
void			*die_thread(void *vargp);
void			sleep_think(t_philo *philo);
void			beauty_sleep(unsigned long start, unsigned long sleep);
int				casualty(t_data *data);
int				print_message(t_data *data, int id, char *activity);

int				eat_spaghetti(t_philo	*philo);
int				sleep_and_think(t_philo	*philo);
void			destroy_mutexes(t_data *data);

#endif
