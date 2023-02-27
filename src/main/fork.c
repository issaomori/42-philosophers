/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:13:07 by gissao-m          #+#    #+#             */
/*   Updated: 2023/02/27 12:50:32 by gissao-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"


// void	fork_lock(t_list *list)
// {
// 	if (verify_mutex_stop(list->data))
// 	{
// 		pthread_mutex_lock(&list->fork);
// 		/* Locking the printer so that only one thread can print at a time. */
// 		pthread_mutex_lock(&list->data->status);
// 		/* Checking if the program is still running. If it is, it prints the message. */
// 		if (verify_mutex_stop(list->data))
// 			printf ("%lli %i has taken a forkaqui\n", get_time() \
// 					- list->data->start_time, list->philo_id);
// 		/* Unlocking the status so that other threads can print. */
// 		pthread_mutex_unlock(&list->data->status);
// 		/* This is a special case for when there is only one listsopher. */
// 		if (list->data->philo_nb == 1)
// 		{
// 			/* Checking if the program is still running. */
// 			while (verify_mutex_stop(list->data))
// 			//fazer dormir ate o filo morrer.
// 				/* A function that makes the program sleep for a certain amount of time. */
// 				usleep(1000);
// 			pthread_mutex_unlock(&list->fork);
// 			return ;
// 		}
// 		pthread_mutex_lock(&list->prev->fork);
// 		pthread_mutex_lock(&list->data->status);
// 		if (verify_mutex_stop(list->data))
// 			printf ("%lli %i has taken a fork\n", get_time() \
// 					- list->data->start_time, list->philo_id);
// 		pthread_mutex_unlock(&list->data->status);
// 	}
// }

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
	printf("%lli %i has taken a fork\n", get_time() - list->data->start_time, list->philo_id);
	// just_one_philo(list);
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
	printf("%lli %i has taken a fork\n", get_time() - list->data->start_time, list->philo_id);
	pthread_mutex_unlock(&list->data->status);
}

void	fork_unlock(t_list *list)
{
	pthread_mutex_unlock(&list->prev->fork);
	pthread_mutex_unlock(&list->fork);
}
