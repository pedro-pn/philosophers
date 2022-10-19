/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:32:26 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/10/19 19:13:06 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	get_fork(t_philo *philo)
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct timeval	time;

	if (philo->id == 0)
		left_fork = &philo->data->forks[philo->data->num_philo - 1];
	else
		left_fork = &philo->data->forks[philo->id - 1];
	right_fork = &philo->data->forks[philo->id];
	pthread_mutex_lock(left_fork);
	pthread_mutex_lock(right_fork);
	gettimeofday(&time, NULL);
	eating_act(philo);
	pthread_mutex_unlock(left_fork);
	pthread_mutex_unlock(right_fork);
}

void	eating_act(t_philo *philo)
{	
	struct timeval	time;

	gettimeofday(&time, NULL);
	if (philo->data->is_dead)
		return ;
	if (get_time(time) - philo->die_count > philo->data->tm_to_die)
	{
		printf(DIE_MSG, get_time(time) - philo->data->start, philo->id + 1);
		return ;
	}
	philo->die_count = get_time(time);
	philo->total_eated++;
	printf("%ld ms %d has taken a fork\n",
			get_time(time) - philo->data->start, philo->id + 1);
	printf("%ld ms %d is eating\n",
				get_time(time) - philo->data->start, philo->id + 1);
	usleep(philo->data->tm_to_eat);
}

void	sleeping_act(t_philo philo)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	printf("%ld ms %d is sleeping\n",
			get_time(time) - philo.data->start, philo.id + 1);
	usleep(philo.data->tm_to_sleep);
}

void	thinking_act(t_philo philo)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	printf("%ld ms %d is thinking\n",
			get_time(time) - philo.data->start, philo.id + 1);
}
