/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:03:23 by gissao-m          #+#    #+#             */
/*   Updated: 2023/02/24 18:04:10 by gissao-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_philo(t_data *data)
{
	if (data->philo_nb == 1)
	{
		free(data->list);
		free (data);
	}
	else
	{
		while (data->philo_nb > 1)
		{
			data->list = data->list->next;
			free (data->list->prev);
			data->philo_nb--;
		}
		free(data->list);
		free(data);
	}
}
