/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:27:20 by gissao-m          #+#    #+#             */
/*   Updated: 2022/12/29 16:25:22 by gissao-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <string.h>

void	collect_args(int argc, char *argv[], t_data *data)
{
	data->philo_nb = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->time_must_eat = ft_atoi(argv[5]);
	else
		data->time_must_eat = -1;
}

void	init_threads(t_data *data)
{
	t_list	*aux;
	int		i;

	
}

int	main(int argc, char *argv[])
{
	t_data	*data;
	
	//funcao para verificar se os argumentos passados estao passados de forma correta.
	validate_args(argc, argv);
	collect_args(argc, argv, data);
	init_data(data);
	//primeiro passo eh transformar todos os argumentos que sao passados como strings para inteiro, e armazenar em variaveis correspondentes ás suas funcs.

	//como esta func nao precisa existir necessariamente, atribuo ela numa cond, se existir ele faz, se nao existir continua normalmente tbm.
}
