/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:17:59 by gissao-m          #+#    #+#             */
/*   Updated: 2023/03/02 20:28:51 by gissao-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	just_one_philo(t_list *list)
{
	if (list->data->philo_nb == 1)
	{
		pthread_mutex_lock(&list->fork);
		printf("%lli %i has taken a fork\n", \
		get_time() - list->data->start_time, list->philo_id);
		miliseconds_sleep(list->data->time_to_die);
		pthread_mutex_unlock(&list->fork);
		return (0);
	}
	return (1);
}

static int	check_stop(t_data *data)
{
	pthread_mutex_lock(data->lock_mutex);
	if (data->lock == 1)
	{
		pthread_mutex_unlock(data->lock_mutex);
		return (0);
	}
	pthread_mutex_unlock(data->lock_mutex);
	return (1);
}

void	check_die(t_data *data)
{
	t_list		*list;
	long long	time_since_last_meal;

	usleep(5000);
	list = data->list;
	while (check_stop(data))
	{
		usleep(10);
		pthread_mutex_lock(list->data->time_to_eat_mutex);
		time_since_last_meal = get_time() - list->last_meal;
		pthread_mutex_unlock(list->data->time_to_eat_mutex);
		if (time_since_last_meal > data->time_to_die)
		{
			pthread_mutex_lock(data->lock_mutex);
			data->lock = 1;
			pthread_mutex_unlock(data->lock_mutex);
			pthread_mutex_lock(data->status);
			printf("%lli %i died\n", \
			(get_time() - data->start_time), list->philo_id);
			pthread_mutex_unlock(data->status);
		}
		list = list->next;
	}
}
