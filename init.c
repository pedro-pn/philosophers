/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:50:01 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/10/20 12:48:51 by ppaulo-d         ###   ########.fr       */
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
	i = 0;
	while (i < data->num_philo)
	{
		// if (*status != 0)
		// 	data->is_dead = 1;
		pthread_join(data->philos[i], (void **)&status);
		free(status);
		i++;
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
		pthread_mutex_lock(&philo->data->die_mutex);
		if (philo->data->is_dead)
		{
			pthread_mutex_unlock(&philo->data->die_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->die_mutex);
		gettimeofday(&time, NULL);
		thinking_act(*philo);
		get_fork(philo);
		gettimeofday(&time, NULL);
		pthread_mutex_lock(&philo->data->die_mutex);
		if (philo->data->is_dead)
		{
			pthread_mutex_unlock(&philo->data->die_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->die_mutex);
		pthread_mutex_lock(&philo->data->die_mutex);
		if (get_time(time) - philo->die_count < philo->data->tm_to_die)
		{
			pthread_mutex_unlock(&philo->data->die_mutex);
			sleeping_act(*philo);
		}
		else
			pthread_mutex_unlock(&philo->data->die_mutex);
		if (philo->total_eated == philo->data->total_eat
				&& philo->data->total_eat != 0)
			break ;
	}
	// if (get_time(time) - philo->die_count > philo->data->tm_to_die)
	// {
	// 	*status = 2;
	// 	return ((void *)status);
	// }
	// else if (philo->data->is_dead)
	// {
	// 	*status = 3;
	// 	return ((void *)status);
	// }
	return ((void *)status);
}