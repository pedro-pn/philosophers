/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:32:26 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/10/21 10:54:38 by ppaulo-d         ###   ########.fr       */
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
	if (get_time(time) - philo->die_count > philo->data->tm_to_die)
	{
		pthread_mutex_lock(&philo->data->print_lock);
		gettimeofday(&time, NULL);
		if (!dead_checker(philo->data))
			printf(DIE_MSG, (get_time(time) - philo->start) / 1000, philo->id + 1);
		pthread_mutex_unlock(&philo->data->print_lock);
		pthread_mutex_lock(&philo->data->die_mutex);
		philo->data->is_dead = 1;
		pthread_mutex_unlock(&philo->data->die_mutex);
		return ;
	}
	if (dead_checker(philo->data))
		return ;
	pthread_mutex_lock(&philo->data->print_lock);
	gettimeofday(&time, NULL);
	if (!dead_checker(philo->data))
	{
		printf("%ld %d has taken a fork\n",
				(get_time(time) - philo->start) / 1000, philo->id + 1);
		printf("%ld %d has taken a fork\n",
				(get_time(time) - philo->start) / 1000, philo->id + 1);
		printf("%ld ms %d is eating\n",
					(get_time(time) - philo->start) / 1000, philo->id + 1);
	}
	pthread_mutex_unlock(&philo->data->print_lock);
	usleep(philo->data->tm_to_eat);
	if (dead_checker(philo->data))
		return ;
	if (get_time(time) - philo->die_count > philo->data->tm_to_die)
	{
		pthread_mutex_lock(&philo->data->die_mutex);
		philo->data->is_dead = 1;
		pthread_mutex_unlock(&philo->data->die_mutex);
		pthread_mutex_lock(&philo->data->print_lock);
		gettimeofday(&time, NULL);
		if (!dead_checker(philo->data))
			printf(DIE_MSG, (get_time(time) - philo->start) / 1000, philo->id + 1);
		pthread_mutex_unlock(&philo->data->print_lock);
		return ;
	}
	philo->die_count = get_time(time);
	philo->total_eated++;
}

void	sleeping_act(t_philo philo)
{
	struct timeval	time;

	if (dead_checker(philo.data))
		return ;
	pthread_mutex_lock(&philo.data->print_lock);
	gettimeofday(&time, NULL);
	if (get_time(time) - philo.die_count < philo.data->tm_to_die)
	{
		pthread_mutex_unlock(&philo.data->print_lock);
		return ;
	}
	if (!dead_checker(philo.data))
		printf("%ld %d is sleeping\n",
				(get_time(time) - philo.start) / 1000, philo.id + 1);
	pthread_mutex_unlock(&philo.data->print_lock);
	usleep(philo.data->tm_to_sleep);
}

void	thinking_act(t_philo philo)
{
	struct timeval	time;

	if (dead_checker(philo.data))
		return ;
	pthread_mutex_lock(&philo.data->print_lock);
	gettimeofday(&time, NULL);
	if (get_time(time) - philo.die_count < philo.data->tm_to_die)
	{
		pthread_mutex_unlock(&philo.data->print_lock);
		return ;
	}
	if (!dead_checker(philo.data))
		printf("%ld %d is thinking\n",
				(get_time(time) - philo.start) / 1000, philo.id + 1);
	pthread_mutex_unlock(&philo.data->print_lock);
}
