/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:27:20 by gissao-m          #+#    #+#             */
/*   Updated: 2023/03/02 13:59:09 by gissao-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char *argv[])
{
	t_data	*data;

	data = (t_data *) malloc (sizeof(t_data));
	validate_args(argc, argv);
	collect_args(argc, argv, data);
	init_data(data);
	init_thread(data);
	free_philo(data);
}
