/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:33:46 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/10/24 13:28:17 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int argc, char *argv[])
{
	t_data	*data;

	if (check_args(argc, argv))
		return (ARGERR);
	data = create_data(argc, argv);
	start_threads(data);
	return (0);
}
