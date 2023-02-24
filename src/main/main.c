/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:27:20 by gissao-m          #+#    #+#             */
/*   Updated: 2023/02/24 17:56:13 by gissao-m         ###   ########.fr       */
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
	data->start_time = get_time();
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

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

long	past_time(t_data *data)
{
	return (get_time() - data->start_time);
}

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

void	just_one_philo(t_list *list)
{
	if (list->data->philo_nb == 1)
	{
		while(verify_mutex_stop(list->data))
			usleep(1000);
		pthread_mutex_unlock(&list->fork);
		return ;
	}
}

void	fork_lock(t_list *list)
{
	if(!verify_mutex_stop(list->data))
		return ;
	pthread_mutex_lock(&list->fork);
	pthread_mutex_lock(&list->data->status);
	if (!verify_mutex_stop(list->data))
	{
		pthread_mutex_unlock(&list->data->status);
		pthread_mutex_unlock(&list->fork);
		return ;
	}
	printf("%lli %i has taken a fork\n", past_time(list->data->start_time), list->philo_id);
	just_one_philo(list);
	// if (list->data->philo_nb == 1)
	// {
	// 	while(verify_mutex_stop(list->data))
	// 		usleep(1000);
	// 	pthread_mutex_unlock(&list->fork);
	// 	return ;
	// }
	pthread_mutex_lock(&list->prev->prev->fork);
	pthread_mutex_lock(&list->data->status);
	if (!verify_mutex_stop(list->data))
	{
		pthread_mutex_unlock(&list->data->status);
		pthread_mutex_unlock(&list->prev->fork);
		pthread_mutex_unlock(&list->fork);
		return ;
	}
	printf("%lli %i has taken a fork\n", past_time(list->data->start_time), list->philo_id);
	pthread_mutex_unlock(&list->data->status);
}

void	fork_unlock(t_list *list)
{
	pthread_mutex_unlock(&list->prev->fork);
	pthread_mutex_unlock(&list->fork);
}

int	nb_times_eat(t_list *list)
{
	pthread_mutex_lock(&list->data->eat_mutex);
	if (list->eat_counter != list->data->eat_mutex)
	{
		pthread_mutex_unlock(&list->data->eat_mutex);
		return (1);
	}
	pthread_mutex_unlock(&list->data->eat_mutex);
	return (0);
}

int	amount_of_times_eat(t_data *data)
{
	t_list *list = data->list;

// Adicionamos um loop infinito para iterar sobre os filósofos.
	while (1)
	{
		if (check_eat_mutex(list))
			return 0;

		//adicionamos a verificação do ID do filósofo ao primeiro if. Isso nos permite tratar o primeiro filósofo de maneira diferente dos outros.
		if (list->philo_id == data->philo_nb)
			break;
		// Adicionamos um break para sair do loop quando chegarmos ao último filósofo.

		list = list->next;
	}
	pthread_mutex_lock(&data->lock_mutex);
	data->lock = 1;
	pthread_mutex_unlock(&data->lock_mutex);
	return (1);
}

int	check_stop(t_data *data)
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
        pthread_mutex_lock(&list->data->time_to_eat_mutex);
		time_since_last_meal = get_time() - list->last_meal;
        pthread_mutex_unlock(&list->data->time_to_eat_mutex);

        if (time_since_last_meal > data->time_to_die)
		{
            pthread_mutex_lock(&data->lock_mutex);
            data->lock = 1;
            pthread_mutex_unlock(&data->lock_mutex);
            pthread_mutex_lock(&data->status);
            printf("%lli %i died\n", get_time() - data->start_time, list->philo_id);
            pthread_mutex_unlock(&data->status);
            break;
        }

        list = list->next;
	}
}

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

void	philo_eating(t_list *list)
{
	if (!verify_mutex_stop(list->data))
		return ;
	pthread_mutex_lock(&list->data->time_to_eat_mutex);
	list->last_meal = get_time();
	pthread_mutex_lock(&list->data->time_to_eat_mutex);
	pthread_mutex_lock(&list->data->status);
	if (verify_mutex_stop(list->data))
		printf("%lli %d is eating\n", past_time(list->data), list->philo_id);
	pthread_mutex_lock(&list->data->eat_mutex);
	list->eat_counter++;
	pthread_mutex_unlock(&list->data->eat_mutex);
	amount_of_times_eat(list->data);
	pthread_mutex_unlock(&list->data->status);
	if (verify_mutex_stop(list->data))
		usleep(list->data->time_to_eat * 1000);
}

void	*daily_activities(t_list *list, t_data *data)
{
	pthread_mutex_lock(&list->data->time_to_eat_mutex);
	list->last_meal = get_time();
	pthread_mutex_unlock(&list->data->time_to_eat_mutex);
	if (list->philo_id % 2 == 0)
		miliseconds_sleep(5);
	while (verify_mutex_stop(list->data))
	{
		if ((list->eat_counter < list->data->time_must_eat || list->data->time_must_eat == -1))
			break ;
		fork_lock(list);
		if (verify_mutex_stop(list->data) == 0)
			break ;
		philo_eating(list);
		fork_unlock(list);
	}
	
}

void	init_thread(t_data *data)
{
    int nb_philo;
    t_list *temp;

	nb_philo = data->philo_nb;
	t_list *temp = data->list;
    pthread_mutex_init(&data->status, NULL);
    pthread_mutex_init(&data->lock_mutex, NULL);
    pthread_mutex_init(&data->eat_mutex, NULL);
    pthread_mutex_init(&data->time_to_eat_mutex, NULL);
    data->start_time = get_time();
	// o while serve para que a variável temp seja reiniciada para o valor inicial em cada iteração, garantindo que as threads sejam corretamente associadas aos filósofos correspondentes.
    while (nb_philo > 0)
	{
        if (pthread_create(&temp->thread, NULL, daily_activities, temp) != 0)
		{
            perror("Pthread_create failed.\n");
            exit(EXIT_FAILURE);
        }
        temp = temp->next;
        nb_philo--;
    }
    check_die(data);
    nb_philo = data->philo_nb;
    temp = data->list;
    while (nb_philo > 0)
	{
        if (pthread_join(temp->thread, NULL) != 0) {
            perror("Pthread_join failed.\n");
            exit(EXIT_FAILURE);
        }
        temp = temp->next;
        nb_philo--;
    }
}

void	free_philo(t_data *data)
{
	if (data->philo_nb == 1)
	{
		free(data->list);
		free (data);
	}
	else
	{
		while (data->philo_nb > 1)
		{
			data->list = data->list->next;
			free (data->list->prev);
			data->philo_nb--;
		}
		free(data->list);
		free(data);
	}
}

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
