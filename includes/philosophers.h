/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarneir <acarneir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 21:03:30 by acarneir          #+#    #+#             */
/*   Updated: 2022/07/19 22:14:02 by acarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

# define FALSE	0
# define TRUE	1

typedef struct s_obj	t_obj;

typedef struct s_mutex
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	*meal_counter;
	pthread_mutex_t	*last_meal;
	pthread_mutex_t	print;
	pthread_mutex_t	stop;
}	t_mutex;

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				meal_counter;
	long long int	last_meal;
	pthread_t		thread;
	t_obj			*obj;
}	t_philo;

struct s_obj
{
	int				total_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_nbr_meals;
	int				stop;
	long long int	time_start;
	t_philo			*philos;
	pthread_t		watcher;
	t_mutex			mutex;
};

int				ft_atoi(char *str);
int				has_stoped(t_obj *obj);
void			delay_ms(int delay);
void			print_action(t_obj *obj, int id, char *str);
void			*routine(void *var);
void			*watcher_routine(void *var);
long long int	get_current_time_ms(void);
long long int	timestamp(long long int start);

#endif