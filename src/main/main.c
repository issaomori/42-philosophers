/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:27:20 by gissao-m          #+#    #+#             */
/*   Updated: 2023/01/09 15:40:52 by gissao-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <string.h>

void	collect_args(int argc, char *argv[], t_data *data)
{
	data->philo_nb = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->time_must_eat = ft_atoi(argv[5]);
	else
		data->time_must_eat = -1;
}

void	init_threads(t_data *data)
{
	t_list	*aux;

	aux = data->list;
	//inicializo os mutex e como nao eh ponteiro, adciono que quero pegar o endereco da minha variavel. Coloco NULL pq o attr nao eh algo que irei utilizar neste momento.
	pthread_mutex_init(&data->lock_mutex, NULL);
	pthread_mutex_init(&data->eat_mutex, NULL);
	pthread_mutex_init(&data->time_to_eat_mutex, NULL);

	while (data->philo_nb > 0)
	{
		pthread_create(&aux->thread, NULL, (void *)&daily_activities, aux);
		aux = aux->next;
		data->philo_nb--;
	}
}

void	miliseconds_sleep(int time_in_ms)
{
	long	start_time;

	start_time = current_time();
	while ((current_time() - start_time) < (long)time_in_ms)
		usleep(10);
}

long	current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

long	past_time(long time_started)
{
	return (current_time() - time_started);
}

void	fork_lock()
{
	
}

void	*daily_activities(t_list *list, t_data *data)
{
	pthread_mutex_lock(&list->data->time_to_eat_mutex);
	list->last_meal = current_time();
	pthread_mutex_unlock(&list->data->time_to_eat_mutex);
	if (list->philo_id % 2 == 0)
		miliseconds_sleep(5);
	while (verify_mutex_stop(list->data) && (list->eat_counter < list->data->time_must_eat || list->data->time_must_eat == -1))
	{
		
	}
	
}

int	main(int argc, char *argv[])
{
	t_data	*data;
	
	//funcao para verificar se os argumentos passados estao passados de forma correta.
	validate_args(argc, argv);
	collect_args(argc, argv, data);
	init_data(data);
	//primeiro passo eh transformar todos os argumentos que sao passados como strings para inteiro, e armazenar em variaveis correspondentes ás suas funcs.

	//como esta func nao precisa existir necessariamente, atribuo ela numa cond, se existir ele faz, se nao existir continua normalmente tbm.
}
