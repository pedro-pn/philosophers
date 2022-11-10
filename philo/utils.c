/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:59:08 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/11/04 15:56:32 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	msleep(unsigned int time_ms)
{
	struct timeval	time;
	long int		time_start;

	gettimeofday(&time, NULL);
	time_start = get_time(time);
	while (get_time(time) - time_start < time_ms)
	{
		usleep(1);
		gettimeofday(&time, NULL);
	}
}

long int	get_time(struct timeval time)
{
	return (((time.tv_sec * 1000000) + time.tv_usec) / 1000);
}

void	clean_array(void **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}

void	clean_program(t_data *data)
{
	int	i;

	i = 0;
	free(data->philos);
	while (i < data->num_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
	pthread_mutex_destroy(&data->die_mutex);
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->end_lock);
	free(data);
}

void	delete_meal_mutex(t_philo **philos)
{
	int	i;

	i = 0;
	while (philos[i])
	{
		pthread_mutex_destroy(&philos[i]->meal_mutex);
		i++;
	}
}
