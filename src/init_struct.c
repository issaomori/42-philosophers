/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 15:20:40 by gissao-m          #+#    #+#             */
/*   Updated: 2023/03/02 13:54:07 by gissao-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	init_list(t_list *list, t_data *data, int i)
{
	t_list	*next_philo;
	t_list	*philo_init;

	philo_init = list;
	next_philo = (t_list *) malloc (sizeof(t_list));
	pthread_mutex_init(&next_philo->fork, NULL);
	next_philo->data = data;
	next_philo->eat_counter = 0;
	next_philo->philo_id = i + 1;
	while (list->next != philo_init)
		list = list->next;
	list->next = next_philo;
	next_philo->next = philo_init;
	next_philo->prev = list;
	philo_init->prev = next_philo;
}

void	init_data(t_data *data)
{
	int	i;

	data->start_time = get_time();
	data->list = (t_list *) malloc (sizeof(t_list));
	i = 0;
	data->list->data = data;
	data->lock = 0;
	data->list->eat_counter = 0;
	data->list->philo_id = 1;
	data->list->next = data->list;
	data->list->prev = data->list;
	while (++i < data->philo_nb)
	{
		init_list(data->list, data, i);
	}
	pthread_mutex_init(&data->list->fork, NULL);
	data->status = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t) * 1);
	pthread_mutex_init(data->status, NULL);
	data->lock_mutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t) * 1);
	pthread_mutex_init(data->lock_mutex, NULL);
	data->eat_mutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t) * 1);
	pthread_mutex_init(data->eat_mutex, NULL);
	data->time_to_eat_mutex = (pthread_mutex_t *) \
	malloc(sizeof(pthread_mutex_t) * 1);
	pthread_mutex_init(data->time_to_eat_mutex, NULL);
}
