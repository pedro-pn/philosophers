/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:33:46 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/10/25 12:52:18 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int argc, char *argv[])
{
	t_data	*data;
	int		status;

	status = 0;
	if (check_args(argc))
		return (ARGERR);
	data = create_data(argc, argv);
	status = start_threads(data);
	clean_program(data);
	if (status)
		write(2, "philosophers: something went wrong\n", 35);
	return (status);
}
