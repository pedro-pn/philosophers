/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:34:21 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/10/19 15:34:17 by ppaulo-d         ###   ########.fr       */
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

typedef struct s_philo
{
	int						num_philo;
	int						tm_to_sleep;
	int						tm_to_eat;
	int						tm_to_die;
	int						total_eat;
	int						*total_eated;
	int						i;
	long int				*die_count;
	long int				*time_count;
	long int				start;
	int						is_dead;
	pthread_t				*philos;
	pthread_mutex_t			*forks;
}				t_philo;

/* init.c */

int		check_args(t_philo *philo, int argc, char **argv);
void	create_mutex(t_philo *philo);
void	start_threads(t_philo *philo);
void	*philosopher(void *arg);

/* actions.c */

void	get_fork(t_philo *philo);
void	eating_act(t_philo *philo);
void	sleeping_act(t_philo philo);
void	thinking_act(t_philo philo);

/* utils.c */

int	ft_atoi(const char *nptr);
long int	get_time(struct timeval time);

#endif