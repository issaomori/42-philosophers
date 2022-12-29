/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 18:15:35 by gissao-m          #+#    #+#             */
/*   Updated: 2022/12/28 18:17:03 by gissao-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	check_args(int	argc)
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

int	is_number(char *argv[])
{
	int	i;

	i = 1;
	while(argv[i])
	//faço ++i para pular o primeiro argumento passado que no caso é o executavel.
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
			printf("Error: Invalid argument, found letter when expecting numbers.\n");
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
