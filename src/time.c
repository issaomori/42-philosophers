/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:07:19 by gissao-m          #+#    #+#             */
/*   Updated: 2023/03/01 12:58:47 by gissao-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	miliseconds_sleep(int time_in_ms)
{
	long	start_time;

	start_time = get_time();
	while ((get_time() - start_time) < (long)time_in_ms)
		usleep(10);
}

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

// long long	past_time(t_list *list)
// {
// 	return (get_time() - list->data->start_time);
// }
