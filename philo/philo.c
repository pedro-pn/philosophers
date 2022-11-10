/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 17:13:08 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/10/28 13:41:43 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*monitor(void *arg)
{
	t_moni			*moni;
	int				id;

	moni = (t_moni *)arg;
	while (!end_checker(moni->data))
	{
		id = 0;
		while (id < moni->data->num_philo)
		{
			if (check_last_meal(moni, id))
				return (NULL);
			id++;
		}
		msleep(1);
	}
	return (NULL);
}

void	*philosopher(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2)
		usleep(50);
	while (!dead_checker(philo->data))
	{
		get_fork(philo);
		if (philo->total_eated == philo->data->total_eat
			&& philo->data->total_eat != 0)
			break ;
		sleeping_act(philo);
		thinking_act(philo);
	}
	return (NULL);
}
