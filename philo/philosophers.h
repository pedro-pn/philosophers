/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:34:21 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/10/25 13:28:40 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <string.h>

# define ARGERR 1
# define DIE_MSG "%ld ms %d died\n"

typedef struct s_data
{
	int					num_philo;
	int					tm_to_sleep;
	int					tm_to_eat;
	int					tm_to_die;
	int					total_eat;
	int					is_dead;
	int					end;
	long int			start;
	pthread_t			*philos;
	pthread_mutex_t		*forks;
	pthread_mutex_t		die_mutex;
	pthread_mutex_t		print_lock;
	pthread_mutex_t		end_lock;
}			t_data;

typedef struct s_philo
{
	int			total_eated;
	int			id;
	long int	die_count;
	long int	start;
	t_data		*data;
}				t_philo;

/* init.c */

int			check_args(int argc);
t_data		*create_data(int argc, char **argv);
void		create_mutex(t_data *data);
t_philo		**create_philo(t_data *data);
t_philo		**alloc_philo(t_data *data);

/* philo.c */

void		*philosopher(void *arg);
void		*monitor(void *arg);

/* run.c */

int			start_threads(t_data *data);
void		start_philos(t_data *data, t_philo **philosophers);
void		join_philos(t_data *data);
int			dead_checker(t_data *data);
int			end_checker(t_data *data);

/* actions.c */

void		get_fork(t_philo *philo);
void		eating_act(t_philo *philo);
void		sleeping_act(t_philo *philo);
void		thinking_act(t_philo *philo);
void	one_philo(t_philo *philo);

/* actions_utils.c */

void		print_eating(t_philo *philo, struct timeval time);
void		print_sleeping(t_philo *philo, struct timeval time);
void		print_thinking(t_philo *philo, struct timeval time);
void		death_checker(t_philo *philo, struct timeval time);

/* utils.c */

int			ft_atoi(const char *nptr);
void		clean_array(void **array);
long int	get_time(struct timeval time);
void		clean_program(t_data *data);

#endif