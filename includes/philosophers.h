/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarneir <acarneir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 21:03:30 by acarneir          #+#    #+#             */
/*   Updated: 2022/07/13 21:45:19 by acarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>

# define FALSE	0
# define TRUE	1

typedef struct s_args
{
	int	total;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	max_nbr_meals;
}	t_args;

int	ft_atoi(char *str);

#endif