/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:17:59 by gissao-m          #+#    #+#             */
/*   Updated: 2023/02/27 13:52:53 by gissao-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	check_stop(t_data *data)
{
	int	stop;
    pthread_mutex_lock(&data->lock_mutex);
	stop = data->lock;
    pthread_mutex_unlock(&data->lock_mutex);

    return (!stop);
}

void	check_die(t_data *data)
{
    t_list *list = data->list;
	long long time_since_last_meal;
    usleep(5000);

// Movemos a atribuição da variável philo para o início da função.
// Adicionamos um tempo de espera antes do loop principal para dar aos filósofos a chance de começar a comer.
// Adicionamos uma variável para armazenar o tempo decorrido desde a última refeição do filósofo.
// Adicionamos uma verificação de tempo desde a última refeição do filósofo antes de verificar se o programa deve parar devido à morte de um filósofo. Isso permite que o filósofo termine sua refeição antes de ser considerado morto.

    while (check_stop(data))
	{
        usleep(10);
        pthread_mutex_lock(list->data->time_to_eat_mutex);
		time_since_last_meal = get_time() - list->last_meal;
        printf("last_meal: %lld\n", list->last_meal);
        printf("time_since: %lld\n", time_since_last_meal);
        pthread_mutex_unlock(list->data->time_to_eat_mutex);
        printf("time_to_die: %d\n", data->time_to_die);
        if (time_since_last_meal > data->time_to_die)
		{
            pthread_mutex_lock(&data->lock_mutex);
            data->lock = 1;
            pthread_mutex_unlock(&data->lock_mutex);
            pthread_mutex_lock(&data->status);
            printf("start_time: %lld\n", data->start_time);
            printf("start_time: %lld\n", get_time());
            printf("%lli %i died\n", get_time() - data->start_time, list->philo_id);
            pthread_mutex_unlock(&data->status);
            break;
        }

        list = list->next;
	}
}
