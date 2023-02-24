/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:13:07 by gissao-m          #+#    #+#             */
/*   Updated: 2023/02/24 18:24:47 by gissao-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	just_one_philo(t_list *list)
{
	if (list->data->philo_nb == 1)
	{
		while(verify_mutex_stop(list->data))
			usleep(1000);
		pthread_mutex_unlock(&list->fork);
		return ;
	}
}

void	fork_lock(t_list *list)
{
	if(!verify_mutex_stop(list->data))
		return ;
	pthread_mutex_lock(&list->fork);
	pthread_mutex_lock(&list->data->status);
	if (!verify_mutex_stop(list->data))
	{
		pthread_mutex_unlock(&list->data->status);
		pthread_mutex_unlock(&list->fork);
		return ;
	}
	printf("%lli %i has taken a fork\n", past_time(list->data->start_time), list->philo_id);
	just_one_philo(list);
	// if (list->data->philo_nb == 1)
	// {
	// 	while(verify_mutex_stop(list->data))
	// 		usleep(1000);
	// 	pthread_mutex_unlock(&list->fork);
	// 	return ;
	// }
	pthread_mutex_lock(&list->prev->prev->fork);
	pthread_mutex_lock(&list->data->status);
	if (!verify_mutex_stop(list->data))
	{
		pthread_mutex_unlock(&list->data->status);
		pthread_mutex_unlock(&list->prev->fork);
		pthread_mutex_unlock(&list->fork);
		return ;
	}
	printf("%lli %i has taken a fork\n", past_time(list->data->start_time), list->philo_id);
	pthread_mutex_unlock(&list->data->status);
}

void	fork_unlock(t_list *list)
{
	pthread_mutex_unlock(&list->prev->fork);
	pthread_mutex_unlock(&list->fork);
}
