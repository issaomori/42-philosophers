/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:13:07 by gissao-m          #+#    #+#             */
/*   Updated: 2023/03/02 13:50:09 by gissao-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	fork_lock(t_list *list)
{
	if (!verify_mutex_stop(list->data))
		return ;
	pthread_mutex_lock(&list->fork);
	pthread_mutex_lock(list->data->status);
	if (!verify_mutex_stop(list->data))
	{
		pthread_mutex_unlock(list->data->status);
		pthread_mutex_unlock(&list->fork);
		return ;
	}
	printf("%lli %i has taken a fork\n", \
	get_time() - list->data->start_time, list->philo_id);
	pthread_mutex_unlock(list->data->status);
	pthread_mutex_lock(&list->prev->fork);
	pthread_mutex_lock(list->data->status);
	if (!verify_mutex_stop(list->data))
	{
		pthread_mutex_unlock(list->data->status);
		pthread_mutex_unlock(&list->prev->fork);
		pthread_mutex_unlock(&list->fork);
		return ;
	}
	printf("%lli %i has taken a fork\n", \
	get_time() - list->data->start_time, list->philo_id);
	pthread_mutex_unlock(list->data->status);
}

void	fork_unlock(t_list *list)
{
	pthread_mutex_unlock(&list->prev->fork);
	pthread_mutex_unlock(&list->fork);
}
