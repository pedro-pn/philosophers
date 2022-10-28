/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 10:57:25 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/10/28 11:02:50 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_last_meal(t_moni *moni, int id)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	if (get_time(time) - get_lastmeal(moni->philos[id])
		<= moni->data->tm_to_die)
		return (0);
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

long int	get_lastmeal(t_philo *philo)
{
	long int	last_meal;

	pthread_mutex_lock(&philo->meal_mutex);
	last_meal = philo->die_count;
	pthread_mutex_unlock(&philo->meal_mutex);
	return (last_meal);
}
