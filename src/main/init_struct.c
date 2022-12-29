/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 15:20:40 by gissao-m          #+#    #+#             */
/*   Updated: 2022/12/29 15:21:47 by gissao-m         ###   ########.fr       */
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
	data->list->next = data->list;
	data->list->prev = data->list;
	while (i < data->philo_nb)
	{
		init_list(data->list, data, i);
	}
}
