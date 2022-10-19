/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:50:01 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/10/19 16:25:40 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_args(t_philo *philo, int argc, char **argv)
{
	struct timeval	time;
	int				count;

	count = 0;
	if (argc < 5)
	{
		write(STDERR_FILENO, "Insufficient args. \n", 20);
		return (ARGERR);
	}
	gettimeofday(&time, NULL);
	philo->i = 0;
	philo->num_philo = ft_atoi(argv[1]);
	philo->start = get_time(time);
	philo->forks = malloc(sizeof(pthread_mutex_t) * (philo->num_philo));
	philo->philos = malloc(sizeof(pthread_t) * (philo->num_philo));
	philo->die_count = malloc(sizeof(long int) * philo->num_philo);
	while (count < philo->num_philo)
	{
		philo->die_count[count] = philo->start;
		count++;
	}
	philo->is_dead = 0;
	philo->tm_to_die = ft_atoi(argv[2]) * 1000;
	philo->tm_to_eat = ft_atoi(argv[3]) * 1000;
	philo->tm_to_sleep = ft_atoi(argv[4]) * 1000;
	philo->total_eated = malloc(sizeof(int) * philo->num_philo);
	memset(philo->total_eated, 0, philo->num_philo);
	create_mutex(philo);
	if (argc == 6)
		philo->total_eat = ft_atoi(argv[5]);
	else
		philo->total_eat = 0;
	 return (0);
}

void	create_mutex(t_philo *philo)
{
	int	count;

	count = 0;
	while (count < philo->num_philo)
	{
		pthread_mutex_init(&philo->forks[count], NULL);
		count++;
	}
}

void	start_threads(t_philo *philo)
{
	int	i;
	int	*status;

	i = 0;
	status = malloc(sizeof(int));
	*status = 0;
	while (i < philo->num_philo)
	{
		philo->i = i;
		pthread_create(&philo->philos[i], NULL, &philosopher, (void *)philo);
		i++;
	}
	i = 0;
	while (i < philo->num_philo)
	{
		if (*status != 0)
			philo->is_dead = 1;
		pthread_join(philo->philos[i], (void **)&status);
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
	while (!philo->is_dead && get_time(time) - philo->die_count[philo->i] < philo->tm_to_die)
	{
		gettimeofday(&time, NULL);
		thinking_act(*philo);
		get_fork(philo);
		gettimeofday(&time, NULL);
		if (philo->is_dead)
			break ;
		if (get_time(time) - philo->die_count[philo->i] < philo->tm_to_die)
			sleeping_act(*philo);
		if (philo->total_eated[philo->i] == philo->total_eat
				&& philo->total_eat != 0)
			break ;
	}
	if (get_time(time) - philo->die_count[philo->i] > philo->tm_to_die)
	{
		*status = 2;
		return ((void *)status);
	}
	else if (philo->is_dead)
	{
		*status = 3;
		return ((void *)status);
	}
	return ((void *)status);
}