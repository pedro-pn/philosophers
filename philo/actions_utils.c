/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 18:09:47 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/10/28 10:59:54 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_eating(t_philo *philo)
{
	struct timeval	time;

	pthread_mutex_lock(&philo->data->print_lock);
	gettimeofday(&time, NULL);
	if (!dead_checker(philo->data))
	{
		printf("%ld %d has taken a fork\n",
			(get_time(time) - philo->start), philo->id + 1);
		printf("%ld %d has taken a fork\n",
			(get_time(time) - philo->start), philo->id + 1);
		printf("%ld %d is eating\n",
			(get_time(time) - philo->start), philo->id + 1);
	}
	pthread_mutex_unlock(&philo->data->print_lock);
}

void	print_sleeping(t_philo *philo)
{
	struct timeval	time;

	pthread_mutex_lock(&philo->data->print_lock);
	gettimeofday(&time, NULL);
	if (!dead_checker(philo->data))
	{
		printf("%ld %d is sleeping\n",
			(get_time(time) - philo->start), philo->id + 1);
	}
	pthread_mutex_unlock(&philo->data->print_lock);
}

void	print_thinking(t_philo *philo)
{
	struct timeval	time;

	pthread_mutex_lock(&philo->data->print_lock);
	gettimeofday(&time, NULL);
	if (!dead_checker(philo->data))
	{
		printf("%ld %d is thinking\n",
			(get_time(time) - philo->start), philo->id + 1);
	}
	pthread_mutex_unlock(&philo->data->print_lock);
}
