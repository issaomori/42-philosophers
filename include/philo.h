/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:27:25 by gissao-m          #+#    #+#             */
/*   Updated: 2023/03/02 20:29:01 by gissao-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_list	t_list;
typedef struct s_data	t_data;

typedef struct s_list
{
	long long		last_meal;
	int				philo_id;
	int				eat_counter;
	pthread_t		thread;
	pthread_mutex_t	fork;
	t_list			*next;
	t_list			*prev;
	t_data			*data;
}	t_list;

typedef struct s_data
{
	int				philo_nb;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_must_eat;
	int				lock;
	long long		start_time;
	pthread_mutex_t	*status;
	pthread_mutex_t	*lock_mutex;
	pthread_mutex_t	*eat_mutex;
	pthread_mutex_t	*time_to_eat_mutex;
	t_list			*list;
}	t_data;

int			ft_str_is_numeric(char *str);
void		validate_args(int argc, char *argv[]);
int			ft_atoi(const char *str);
void		init_data(t_data *data);
int			verify_mutex_stop(t_data *data);
void		collect_args(int argc, char *argv[], t_data *data);
long long	get_time(void);
void		miliseconds_sleep(int time_in_ms);
void		philo_eating(t_list *list);
void		check_die(t_data *data);
void		fork_lock(t_list *list);
void		fork_unlock(t_list *list);
void		init_thread(t_data *data);
void		free_philo(t_data *data);
int			just_one_philo(t_list *list);

#endif
