/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:22:37 by gissao-m          #+#    #+#             */
/*   Updated: 2023/03/02 20:30:52 by gissao-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	philo_sleeping(t_list *list)
{
	if (verify_mutex_stop(list->data))
	{
		pthread_mutex_lock(list->data->status);
		if (verify_mutex_stop(list->data))
			printf("%lli %i is sleeping\n", \
			get_time() - list->data->start_time, list->philo_id);
		pthread_mutex_unlock(list->data->status);
		if (verify_mutex_stop(list->data))
			usleep(list->data->time_to_sleep * 1000);
	}
}

void	philo_thinking(t_list *list)
{
	if (!verify_mutex_stop(list->data))
		return ;
	pthread_mutex_lock(list->data->status);
	if (verify_mutex_stop(list->data))
		printf("%lli %i is thinking\n", \
		get_time() - list->data->start_time, list->philo_id);
	pthread_mutex_unlock(list->data->status);
}

static void	*daily_activities(t_list *list, t_data *data)
{
	pthread_mutex_lock(list->data->time_to_eat_mutex);
	list->last_meal = get_time();
	pthread_mutex_unlock(list->data->time_to_eat_mutex);
	if (!just_one_philo(list))
		return (NULL);
	if (list->philo_id % 2 == 0)
		miliseconds_sleep(list->data->time_to_eat - 5);
	while (verify_mutex_stop(list->data) && (list->eat_counter \
	< list->data->time_must_eat || list->data->time_must_eat == -1))
	{
		fork_lock(list);
		if (verify_mutex_stop(list->data) == 0)
			break ;
		philo_eating(list);
		fork_unlock(list);
		philo_sleeping(list);
		philo_thinking(list);
	}
	return (NULL);
}

static void	create_thread(t_data *data, int nb_philo, t_list *temp)
{
	while (nb_philo > 0)
	{
		if (pthread_create(&temp->thread, NULL, \
		(void *)daily_activities, temp) != 0)
		{
			perror("Pthread_create failed.\n");
			exit(EXIT_FAILURE);
		}
		temp = temp->next;
		nb_philo--;
	}
}

void	init_thread(t_data *data)
{
	int		nb_philo;
	t_list	*temp;

	nb_philo = data->philo_nb;
	temp = data->list;
	data->start_time = get_time();
	create_thread(data, nb_philo, temp);
	check_die(data);
	nb_philo = data->philo_nb;
	while (nb_philo > 0)
	{
		if (pthread_join(temp->thread, NULL) != 0)
		{
			perror("Pthread_join failed.\n");
			exit(EXIT_FAILURE);
		}
		temp = temp->next;
		nb_philo--;
	}
}
