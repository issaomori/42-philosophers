/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 14:18:20 by gissao-m          #+#    #+#             */
/*   Updated: 2023/03/02 13:58:40 by gissao-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_str_is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
		return (1);
	if (str[0] == '+')
		i++;
	while (str[i] != '\0')
	{
		while (str[i] >= 48 && str[i] <= 57)
			i++;
		if (str[i] == '\0')
			return (1);
		else
			return (0);
	}
	return (0);
}

int	ft_isdigit(int i)
{
	if (i >= 48 && i <= 57)
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	result;
	int	ch_sign;
	int	count_size;

	result = 0;
	ch_sign = 1;
	count_size = 0;
	while ((str[count_size] >= '\t' && str[count_size] <= '\r') \
	|| str[count_size] == ' ')
		count_size++;
	if (str[count_size] == '-' || str[count_size] == '+')
	{
		if (str[count_size] == '-')
			ch_sign *= -1;
		count_size++;
	}
	while (ft_isdigit(str[count_size]))
	{
		result = (result * 10) + (str[count_size] - '0');
		count_size++;
	}
	return (ch_sign * result);
}
