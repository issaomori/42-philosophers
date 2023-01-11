/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:47:15 by gissao-m          #+#    #+#             */
/*   Updated: 2023/01/09 14:00:06 by gissao-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"



int verify_mutex_stop(t_data *data)
{
    pthread_mutex_lock(&data->lock_mutex);
    if (data->lock == 1)
    {
        pthread_mutex_unlock(&data->lock_mutex);
        return (0);
    }
    pthread_mutex_unlock(&data->lock_mutex);
    return (1);
}
