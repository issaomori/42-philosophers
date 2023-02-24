/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:27:20 by gissao-m          #+#    #+#             */
/*   Updated: 2023/02/24 18:35:57 by gissao-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// void	collect_args(int argc, char *argv[], t_data *data)
// {
// 	data->philo_nb = ft_atoi(argv[1]);
// 	data->time_to_die = ft_atoi(argv[2]);
// 	data->time_to_eat = ft_atoi(argv[3]);
// 	data->time_to_sleep = ft_atoi(argv[4]);
// 	if (argc == 6)
// 		data->time_must_eat = ft_atoi(argv[5]);
// 	else
// 		data->time_must_eat = -1;
// }

// void	fork_lock(t_list *list)
// {
// 	if (verify_mutex_stop(list->data))
// 	{
// 		pthread_mutex_lock(&list->fork);
// 		pthread_mutex_lock(&list->data->status);
// 		if (verify_mutex_stop(list->data))
// 			printf("%lli %i has taken a fork\n", past_time(list->data->start_time), list->philo_id);
// 		pthread_mutex_unlock(&list->data->status);
// 		if (list->data->philo_nb == 1)
// 		{
// 			while(verify_mutex_stop(list->data))
// 				usleep(1000);
// 			pthread_mutex_unlock(&list->fork);
// 			return ;
// 		}
// 		pthread_mutex_lock(&list->prev->fork);
// 		pthread_mutex_lock(&list->data->status);
// 		if (verify_mutex_stop(list->data))
// 			printf("%lli %i has taken a fork\n", past_time(list->data->start_time), list->philo_id);
// 	}
// }

// int check_eat_limit(t_philo *philo) {
// pthread_mutex_lock(&philo->data->eat_mutex);
// int can_eat = philo->eat_count != philo->data->eat_num;
// pthread_mutex_unlock(&philo->data->eat_mutex);
// return can_eat;
// }

// int end_of_eating(t_data *data) {
// t_philo *curr_philo = data->philo;
// do {
// if (check_eat_limit(curr_philo)) {
// return 0;
// }
// curr_philo = curr_philo->next;
// } while (curr_philo != data->philo);

// pthread_mutex_lock(&data->stop_mutex);
// data->stop = 1;
// pthread_mutex_unlock(&data->stop_mutex);
// return 1;
// }

int	main(int argc, char *argv[])
{
	t_data	*data;
	
	//funcao para verificar se os argumentos passados estao passados de forma correta.
	validate_args(argc, argv);
	collect_args(argc, argv, data);
	init_data(data);
	init_thread(data);
	free_philo(data);
	//primeiro passo eh transformar todos os argumentos que sao passados como strings para inteiro, e armazenar em variaveis correspondentes ás suas funcs.

	//como esta func nao precisa existir necessariamente, atribuo ela numa cond, se existir ele faz, se nao existir continua normalmente tbm.
}
