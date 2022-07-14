/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarneir <acarneir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 21:03:30 by acarneir          #+#    #+#             */
/*   Updated: 2022/07/13 23:46:16 by acarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

# define FALSE	0
# define TRUE	1

typedef struct s_args
{
	int				total;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_nbr_meals;
	long long int	time_start;
}	t_args;

int				ft_atoi(char *str);
int				sleeping(t_args args);
int				thinking(t_args args);
void			delay_ms(int delay);
long long int	get_current_time_ms(void);
long long int	timestamp(long long int start);

#endif