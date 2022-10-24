/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 13:28:35 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/10/24 15:51:12 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*monitor(void *arg)
{
	struct timeval	time;
	t_data 			*data;
	int				id;

	data = (t_data *)arg;
	while (1)
	{
		gettimeofday(&time, NULL);
		if (end_checker)
			break ;
		pthread_mutex_lock(&data->die_mutex);
		if (data->is_dead)
		{
			id = data->is_dead;
			pthread_mutex_unlock(&data->die_mutex);
			pthread_mutex_lock(&data->print_lock);
			printf("%ld %d died\n", (get_time(time) - data->start) / 1000, id);
			pthread_mutex_unlock(&data->print_lock);
			break ;
		}
		else
			pthread_mutex_unlock(&data->die_mutex);
	}
}

void	*philosopher(void *arg)
{
	t_philo			*philo;
	int				*status;
	struct timeval	time;
	
	status = malloc(sizeof(*status));
	*status = 0;
	philo = (t_philo *)arg;
	gettimeofday(&time, NULL);
	if (philo->id % 2)
		usleep(50);
	while (get_time(time) - philo->die_count < philo->data->tm_to_die)
	{
		if (dead_checker(philo->data))
			break ;
		get_fork(philo);
		if (dead_checker(philo->data))
			break ;
		if (philo->total_eated == philo->data->total_eat
				&& philo->data->total_eat != 0)
			break ;
		sleeping_act(philo);
		thinking_act(philo);
	}
	return ((void *)status);
}
