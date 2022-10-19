/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:32:26 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/10/19 16:10:33 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	get_fork(t_philo *philo)
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct timeval	time;

	if (philo->i == 0)
		left_fork = &philo->forks[philo->num_philo - 1];
	else
		left_fork = &philo->forks[philo->i - 1];
	right_fork = &philo->forks[philo->i];
	pthread_mutex_lock(left_fork);
	pthread_mutex_lock(right_fork);
	gettimeofday(&time, NULL);
	printf("%ld ms %d has taken a fork\n",
			get_time(time) - philo->start, philo->i + 1);
	eating_act(philo);
	pthread_mutex_unlock(left_fork);
	pthread_mutex_unlock(right_fork);
}

void	eating_act(t_philo *philo)
{	
	struct timeval	time;

	gettimeofday(&time, NULL);
	if (philo->is_dead)
		return ;
	if (get_time(time) - philo->die_count[philo->i] > philo->tm_to_die)
	{
		printf(DIE_MSG, get_time(time) - philo->start, philo->i + 1);
		return ;
	}
	philo->die_count[philo->i] = get_time(time);
	philo->total_eated++;
	printf("%ld ms %d is eating\n",
				get_time(time) - philo->start, philo->i + 1);
	usleep(philo->tm_to_eat);
}

void	sleeping_act(t_philo philo)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	printf("%ld ms %d is sleeping\n",
			get_time(time) - philo.start, philo.i + 1);
	usleep(philo.tm_to_sleep);
}

void	thinking_act(t_philo philo)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	printf("%ld ms %d is thinking\n",
			get_time(time) - philo.start, philo.i + 1);
}
