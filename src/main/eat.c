/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:14:19 by gissao-m          #+#    #+#             */
/*   Updated: 2023/03/02 13:48:35 by gissao-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	nb_times_eat(t_list *list)
{
	pthread_mutex_lock(list->data->eat_mutex);
	if (list->eat_counter != list->data->time_must_eat)
	{
		pthread_mutex_unlock(list->data->eat_mutex);
		return (1);
	}
	pthread_mutex_unlock(list->data->eat_mutex);
	return (0);
}

static int	amount_of_times_eat(t_data *data)
{
	t_list	*list;

	list = data->list;
	while (1)
	{
		if (nb_times_eat(list))
			return (0);
		if (list->philo_id == data->philo_nb)
			break ;
		list = list->next;
	}
	pthread_mutex_lock(data->lock_mutex);
	data->lock = 1;
	pthread_mutex_unlock(data->lock_mutex);
	return (1);
}

void	philo_eating(t_list *list)
{
	if (!verify_mutex_stop(list->data))
		return ;
	pthread_mutex_lock(list->data->time_to_eat_mutex);
	list->last_meal = get_time();
	pthread_mutex_unlock(list->data->time_to_eat_mutex);
	pthread_mutex_lock(list->data->status);
	if (verify_mutex_stop(list->data))
		printf("%lli %d is eating\n", \
		get_time() - list->data->start_time, list->philo_id);
	pthread_mutex_lock(list->data->eat_mutex);
	list->eat_counter++;
	pthread_mutex_unlock(list->data->eat_mutex);
	amount_of_times_eat(list->data);
	pthread_mutex_unlock(list->data->status);
	if (verify_mutex_stop(list->data))
		usleep(list->data->time_to_eat * 1000);
}
