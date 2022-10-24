/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:59:08 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/10/24 18:52:00 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *nptr)
{
	int	atoi;
	int	sign;

	sign = 1;
	atoi = 0;
	while ((*nptr) && (*nptr == '\n' || *nptr == '\t'
			|| *nptr == '\r' || *nptr == '\f'
			|| *nptr == '\v' || *nptr == 32))
		++nptr;
	if (*nptr == '-')
		sign = -1;
	if (*nptr == '+' || *nptr == '-')
		++nptr;
	while (*nptr && *nptr >= 48 && *nptr <= 57)
	{
		atoi = (atoi * 10) + (*nptr - 48);
		++nptr;
	}
	return (atoi * sign);
}

long int	get_time(struct timeval time)
{
	return((time.tv_sec * 1000000) + time.tv_usec);
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
}