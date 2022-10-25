/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:32:26 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/10/25 10:14:59 by ppaulo-d         ###   ########.fr       */
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
	eating_act(philo);
	pthread_mutex_unlock(left_fork);
	pthread_mutex_unlock(right_fork);
}

void	eating_act(t_philo *philo)
{
	struct timeval	time;

	if (dead_checker(philo->data))
			return ;
	gettimeofday(&time, NULL);
	death_checker(philo, time);
	if (dead_checker(philo->data))
		return ;
	gettimeofday(&time, NULL); // talvez n precise
	print_eating(philo, time);
	usleep(philo->data->tm_to_eat);
	gettimeofday(&time, NULL);
	if (dead_checker(philo->data))
		return ;
	death_checker(philo, time);
	philo->die_count = get_time(time);
	philo->total_eated++;
}

void	sleeping_act(t_philo *philo)
{
	struct timeval	time;

	if (dead_checker(philo->data))
		return ;
	gettimeofday(&time, NULL);
	print_sleeping(philo, time);
	usleep(philo->data->tm_to_sleep);
}

void	thinking_act(t_philo *philo)
{
	struct timeval	time;

	if (dead_checker(philo->data))
		return ;
	gettimeofday(&time, NULL);
	print_thinking(philo, time);
}
