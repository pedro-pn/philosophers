/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:59:08 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/10/19 15:34:05 by ppaulo-d         ###   ########.fr       */
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