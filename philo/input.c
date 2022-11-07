/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:04:10 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/11/07 12:22:03 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_input(char *input);

int	check_args(int argc, char **argv)
{
	if (argc < 5)
	{
		write(STDERR_FILENO, "Insufficient args. \n", 20);
		return (ARGERR);
	}
	else if (argc > 6)
	{
		write(STDERR_FILENO, "Too many args. \n", 16);
		return (ARGERR);
	}
	else if (check_total_to_eat(argc, argv))
		return (ARGERR);
	else if (check_values(argc, argv))
		return (INVERR);
	return (0);
}

static int	check_input(char *input)
{
	int	index;

	index = 0;
	while (input[index])
	{
		if (!ft_isdigit(input[index]))
			return (INVERR);
		index++;
	}
	return (0);
}

int	check_total_to_eat(int argc, char **argv)
{
	if (argc != 6)
		return (0);
	if (ft_atoi(argv[5]) == 0)
	{
		write(STDERR_FILENO, "Invalid argument.\n", 18);
		return (ARGERR);
	}
	return (0);
}

int	check_values(int argc, char **argv)
{
	int	index;

	index = 1;
	while (index < argc)
	{
		if (check_input(argv[index]))
		{
			write(STDERR_FILENO, "Invalid argument.\n", 18);
			return (INVERR);
		}
		index++;
	}
	return (0);
}
