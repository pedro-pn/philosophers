/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:50:01 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/10/27 10:34:22 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_args(int argc)
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

t_philo	**alloc_philo(t_data *data)
{
	t_philo	**philos;
	int		index;

	index = 0;
	philos = malloc(sizeof(*philos) * (data->num_philo + 1));
	if (!philos)
		return (NULL);
	philos[data->num_philo] = NULL;
	while (index < data->num_philo)
	{
		philos[index] = malloc(sizeof(**philos));
		if (!philos[index])
		{
			clean_array((void **)philos);
			return (NULL);
		}
		index++;
	}
	return (philos);
}

t_philo	**create_philo(t_data *data)
{
	t_philo	**philos;
	int		index;

	index = 0;
	philos = alloc_philo(data);
	if (!philos)
		return (NULL);
	while (philos[index])
	{
		philos[index]->total_eated = 0;
		philos[index]->id = index;
		philos[index]->die_count = data->start;
		philos[index]->data = data;
		philos[index]->start = data->start;
		pthread_mutex_init(&philos[index]->meal_mutex, NULL);
		index++;
	}
	return (philos);
}
