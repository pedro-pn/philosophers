/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:32:26 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/10/25 14:37:16 by ppaulo-d         ###   ########.fr       */
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
	gettimeofday(&time, NULL);
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

void	one_philo(t_philo *philo)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	printf("%ld %d has taken a fork\n",
		(get_time(time) - philo->data->start) / 1000, philo->id);
	usleep(philo->data->tm_to_die);
	pthread_mutex_lock(&philo->data->die_mutex);
	philo->data->is_dead = philo->id + 1;
	pthread_mutex_unlock(&philo->data->die_mutex);
}
