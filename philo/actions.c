/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:32:26 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/10/28 13:52:50 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	get_fork(t_philo *philo)
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	if (philo->data->num_philo == 1)
	{
		one_philo(philo);
		return ;
	}
	if (philo->id == 0)
		left_fork = &philo->data->forks[philo->data->num_philo - 1];
	else
		left_fork = &philo->data->forks[philo->id - 1];
	right_fork = &philo->data->forks[philo->id];
	pthread_mutex_lock(left_fork);
	pthread_mutex_lock(right_fork);
	if (dead_checker(philo->data))
	{
		pthread_mutex_unlock(left_fork);
		pthread_mutex_unlock(right_fork);
		return ;
	}
	eating_act(philo);
	pthread_mutex_unlock(left_fork);
	pthread_mutex_unlock(right_fork);
}

void	eating_act(t_philo *philo)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->die_count = get_time(time);
	pthread_mutex_unlock(&philo->meal_mutex);
	print_eating(philo);
	usleep(philo->data->tm_to_eat * 1000);
	philo->total_eated++;
}

void	sleeping_act(t_philo *philo)
{
	print_sleeping(philo);
	usleep(philo->data->tm_to_sleep * 1000);
}

void	thinking_act(t_philo *philo)
{
	print_thinking(philo);
}

void	one_philo(t_philo *philo)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	printf("%ld %d has taken a fork\n",
		get_time(time) - philo->data->start, philo->id);
	usleep(philo->data->tm_to_die * 1000);
	pthread_mutex_lock(&philo->data->die_mutex);
	philo->data->is_dead = philo->id + 1;
	pthread_mutex_unlock(&philo->data->die_mutex);
}
