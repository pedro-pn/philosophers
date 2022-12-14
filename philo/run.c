/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 18:36:25 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/10/28 11:07:38 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	start_threads(t_data *data)
{
	pthread_t	monitor_thread;
	t_philo		**philosophers;
	t_moni		*moni;

	philosophers = create_philo(data);
	if (!philosophers)
		return (1);
	moni = malloc(sizeof(t_moni));
	moni->data = data;
	moni->philos = philosophers;
	start_philos(data, philosophers);
	pthread_create(&monitor_thread, NULL, &monitor, (void *)moni);
	join_philos(data);
	pthread_mutex_lock(&data->end_lock);
	data->end = 1;
	pthread_mutex_unlock(&data->end_lock);
	pthread_join(monitor_thread, NULL);
	delete_meal_mutex(philosophers);
	clean_array((void **)philosophers);
	free(moni);
	return (0);
}

void	start_philos(t_data *data, t_philo **philosophers)
{
	int	id;

	id = 0;
	while (philosophers[id])
	{
		pthread_create(&data->philos[id], NULL, &philosopher,
			(void *)philosophers[id]);
		id++;
	}
}

void	join_philos(t_data *data)
{
	int	id;

	id = 0;
	while (id < data->num_philo)
	{
		pthread_join(data->philos[id], NULL);
		id++;
	}
}

int	dead_checker(t_data *data)
{
	pthread_mutex_lock(&data->die_mutex);
	if (data->is_dead)
	{
		pthread_mutex_unlock(&data->die_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->die_mutex);
	return (0);
}

int	end_checker(t_data *data)
{
	pthread_mutex_lock(&data->end_lock);
	if (data->end)
	{
		pthread_mutex_unlock(&data->end_lock);
		return (1);
	}
	pthread_mutex_unlock(&data->end_lock);
	return (0);
}
