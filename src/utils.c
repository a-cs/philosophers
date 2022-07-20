/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarneir <acarneir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 22:07:50 by acarneir          #+#    #+#             */
/*   Updated: 2022/07/20 00:06:56 by acarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	print_action(t_obj *obj, int id, char *str)
{
	pthread_mutex_lock(&obj->mutex.print);
	if (!has_stoped(obj))
		printf("%lld\t\t%d\t%s\n", timestamp(obj->time_start), id, str);
	pthread_mutex_unlock(&obj->mutex.print);
}

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	ft_is_space(char c)
{
	if (c == '\n' || c == '\t' || c == '\v'
		|| c == '\r' || c == '\f' || c == ' ')
		return (1);
	return (0);
}

int	ft_atoi(char *str)
{
	int	signal;
	int	number;

	while (ft_is_space(*str))
		str++;
	signal = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			signal = -1;
		str++;
	}
	number = 0;
	while ((ft_isdigit(*str)))
	{
		number *= 10;
		number += signal * (*str - '0');
		str++;
	}
	return (number);
}
