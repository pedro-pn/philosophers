/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:50:01 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/10/24 13:29:16 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_args(int argc, char **argv)
{
	if (argc >= 5)
		return (0);
	write(STDERR_FILENO, "Insufficient args. \n", 20);
	return (ARGERR);
}

t_data	*create_data(int argc, char **argv)
{
	t_data			*data;
	struct timeval	time;

	data = malloc(sizeof(*data));
	gettimeofday(&time, NULL);
	data->num_philo = ft_atoi(argv[1]);
	data->start = get_time(time);
	data->forks = malloc(sizeof(pthread_mutex_t) * (data->num_philo));
	data->philos = malloc(sizeof(pthread_t) * (data->num_philo));
	data->is_dead = 0;
	data->end = 0;
	data->tm_to_die = ft_atoi(argv[2]) * 1000;
	data->tm_to_eat = ft_atoi(argv[3]) * 1000;
	data->tm_to_sleep = ft_atoi(argv[4]) * 1000;
	create_mutex(data);
	if (argc == 6)
		data->total_eat = ft_atoi(argv[5]);
	else
		data->total_eat = 0;
	return (data);
}

void	create_mutex(t_data *data)
{
	int	count;

	count = 0;
	pthread_mutex_init(&data->die_mutex, NULL);
	pthread_mutex_init(&data->print_lock, NULL);
	pthread_mutex_init(&data->end_lock, NULL);
	while (count < data->num_philo)
	{
		pthread_mutex_init(&data->forks[count], NULL);
		count++;
	}
}

t_philo	**create_philo(t_data *data)
{
	t_philo	**philos;
	int		index;

	index = 0;
	philos = malloc(sizeof(*philos) * (data->num_philo + 1));
	philos[data->num_philo] = NULL;
	while (index < data->num_philo)
	{
		philos[index] = malloc(sizeof(**philos));
		index++;
	}
	index = 0;
	while (philos[index])
	{
		philos[index]->total_eated = 0;
		philos[index]->id = index;
		philos[index]->die_count = data->start;
		philos[index]->data = data;
		philos[index]->start = data->start;
		index++;
	}
	return (philos);
}

void	start_threads(t_data *data)
{
	int		i;
	int		*status;
	pthread_t	moni;
	t_philo	**philosophers;

	i = 0;
	philosophers = create_philo(data);
	status = malloc(sizeof(int));
	*status = 0;
	while (philosophers[i])
	{
		pthread_create(&data->philos[i], NULL, &philosopher, (void *)philosophers[i]);
		i++;
	}
	pthread_create(&moni, NULL, &monitor, (void *)data);
	//pthread_detach(moni);
	i = 0;
	while (i < data->num_philo)
	{
		pthread_join(data->philos[i], (void **)&status);
		free(status);
		i++;
	}
	pthread_mutex_lock(&data->end_lock);
	data->end = 1;
	pthread_mutex_unlock(&data->end_lock);
	pthread_join(moni, NULL);
}


