/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:04:10 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/10/31 16:10:30 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_input(char *input);

int	check_args(int argc, char **argv)
{
	int	index;

	if (argc < 5)
	{
		write(STDERR_FILENO, "Insufficient args. \n", 20);
		return (ARGERR);
	}
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
