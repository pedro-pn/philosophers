/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 18:36:25 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/10/24 18:52:17 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	start_threads(t_data *data)
{
	pthread_t	moni;
	t_philo		**philosophers;

	philosophers = create_philo(data);
	if (!philosopher)
		return (1);
	start_philos(data, philosophers);
	pthread_create(&moni, NULL, &monitor, (void *)data);
	join_philos(data);
	pthread_mutex_lock(&data->end_lock);
	data->end = 1;
	pthread_mutex_unlock(&data->end_lock);
	pthread_join(moni, NULL);
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
