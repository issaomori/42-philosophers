/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:03:23 by gissao-m          #+#    #+#             */
/*   Updated: 2023/03/02 13:34:50 by gissao-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	free_mutex(t_data *data)
{
	if (data->status && data->status != NULL)
	{
		pthread_mutex_destroy(data->status);
		free(data->status);
	}
	if (data->lock_mutex && data->lock_mutex != NULL)
	{
		pthread_mutex_destroy(data->lock_mutex);
		free(data->lock_mutex);
	}
	if (data->eat_mutex && data->eat_mutex != NULL)
	{
		pthread_mutex_destroy(data->eat_mutex);
		free(data->eat_mutex);
	}
	if (data->time_to_eat_mutex && data->time_to_eat_mutex != NULL)
	{
		pthread_mutex_destroy(data->time_to_eat_mutex);
		free(data->time_to_eat_mutex);
	}
}

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
		free_mutex(data);
		free(data);
	}
}
