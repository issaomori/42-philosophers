/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 15:20:40 by gissao-m          #+#    #+#             */
/*   Updated: 2023/02/24 18:52:34 by gissao-m         ###   ########.fr       */
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
	philo_init->data = data;
	philo_init->eat_counter = 0;
	philo_init->philo_id = i + 1;
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

	i = 1;
	data->list = (t_list *) malloc (sizeof(t_list));
	pthread_mutex_init(&data->list->fork, NULL);
	data->list->data = data;
	data->list->eat_counter = 0;
	data->list->philo_id = 1;
	data->list->next = data->list;
	data->list->prev = data->list;
	i = 0;
	while (++i < data->philo_nb)
	{
		init_list(data->list, data, i);
	}
}
