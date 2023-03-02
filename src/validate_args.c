/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 18:15:35 by gissao-m          #+#    #+#             */
/*   Updated: 2023/03/02 13:40:36 by gissao-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	check_args(int argc)
{
	if (argc < 5)
	{
		printf("Error: Argument number is less than required!\n");
		exit (1);
	}
	if (argc > 6)
	{
		printf("Error: Argument number is more than required\n");
		exit (1);
	}	
}

static int	is_number(char *argv[])
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) > 2147483647)
		{
			printf("esteError: Argument invalid,try only integers numbers.\n");
			return (1);
		}
		else if (ft_atoi(argv[i]) < 0)
		{
			printf("Error: Invalid argument,try only positive integers.\n");
			return (1);
		}
		else if (ft_str_is_numeric(argv[i]) == 0)
		{
			printf("Error: Invalid argument, found letter\
			when expecting numbers.\n");
			return (1);
		}
		i++;
	}
	return (0);
}

void	validate_args(int argc, char *argv[])
{
	check_args(argc);
	if (is_number(argv))
		exit (1);
}

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
