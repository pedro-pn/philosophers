/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 17:13:08 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/10/27 10:30:33 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*monitor(void *arg)
{
	t_moni			*moni;
	int				id;

	moni = (t_moni *)arg;
	while (1)
	{
		id = 0;
		if (end_checker(moni->data))
			break ;
		while (id < moni->data->num_philo)
		{
			if (check_last_meal(moni, id))
				return (NULL);
			id++;
		}
		usleep(1000);
	}
	return (NULL);
}

void	*philosopher(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2)
		usleep(500);
	while (1)
	{
		if (dead_checker(philo->data))
			break ;
		get_fork(philo);
		if (philo->total_eated == philo->data->total_eat
			&& philo->data->total_eat != 0)
			break ;
		sleeping_act(philo);
		thinking_act(philo);
	}
	return (NULL);
}

int	check_last_meal(t_moni *moni, int id)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	if (get_time(time) - get_lastmeal(moni->philos[id]) > moni->data->tm_to_die / 1000)
	{
		pthread_mutex_lock(&moni->data->die_mutex);
		moni->data->is_dead = id + 1;
		pthread_mutex_unlock(&moni->data->die_mutex);
		pthread_mutex_lock(&moni->data->print_lock);
		gettimeofday(&time, NULL);
		printf("%ld %d died\n",
			(get_time(time) - moni->data->start), id + 1);
		pthread_mutex_unlock(&moni->data->print_lock);
		return (1);
	}
	return (0);
}

long int	get_lastmeal(t_philo *philo)
{
	long int	last_meal;
	
	pthread_mutex_lock(&philo->meal_mutex);
	last_meal = philo->die_count;
	pthread_mutex_unlock(&philo->meal_mutex);
	return (last_meal);
}