/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:27:25 by gissao-m          #+#    #+#             */
/*   Updated: 2022/12/29 15:22:09 by gissao-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "stdio.h"
# include "stdlib.h"
# include "pthread.h"

typedef struct  s_list
{
	pthread_t		thread;
	pthread_mutex_t	fork;
	t_list  		*next;
	t_list  		*prev;
	t_list			*data;
}	t_list;

typedef struct  s_data
{
	int     philo_nb;
	int     time_to_die;
	int     time_to_eat;
	int     time_to_sleep;
	int     time_must_eat;
	long    start_time;
	t_list	*list;
}	t_data;

int		ft_str_is_numeric(char *str);
int		ft_atoi(const char *str);
int		ft_strcmp(char *s1, char *s2);
void	init_data(t_data *data);

#endif