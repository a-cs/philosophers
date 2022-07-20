/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarneir <acarneir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 00:42:39 by acarneir          #+#    #+#             */
/*   Updated: 2022/07/16 01:15:21 by acarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	has_stoped(t_obj *obj)
{
	int	flag;

	flag = FALSE;
	pthread_mutex_lock(&obj->mutex.stop);
	if (obj->stop == TRUE)
		flag = TRUE;
	pthread_mutex_unlock(&obj->mutex.stop);
	return (flag);
}

static void	has_philo_died(t_obj *obj)
{
	int	i;

	i = 0;
	while (i < obj->total_philos && !obj->stop)
	{
		pthread_mutex_lock(&obj->mutex.last_meal[obj->philos[i].id]);
		if (obj->philos[i].last_meal < get_current_time_ms() - obj->time_to_die)
		{
			print_action(obj, obj->philos[i].id + 1, "died");
			pthread_mutex_lock(&obj->mutex.stop);
			obj->stop = TRUE;
			pthread_mutex_unlock(&obj->mutex.stop);
		}
		pthread_mutex_unlock(&obj->mutex.last_meal[obj->philos[i].id]);
		i++;
	}
}

void	are_all_philos_full(t_obj *obj)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (!has_stoped(obj) && i < obj->total_philos)
	{
		pthread_mutex_lock(&obj->mutex.meal_counter[i]);
		if (obj->philos[i].meal_counter >= obj->max_nbr_meals)
			counter++;
		pthread_mutex_unlock(&obj->mutex.meal_counter[i]);
		i++;
	}
	if (counter == obj->total_philos)
	{
		pthread_mutex_lock(&obj->mutex.stop);
		obj->stop = TRUE;
		pthread_mutex_unlock(&obj->mutex.stop);
	}
}

void	*watcher_routine(void *var)
{
	t_obj	*obj;

	obj = var;
	while (!has_stoped(obj))
	{
		has_philo_died(obj);
		if (obj->max_nbr_meals != 0)
			are_all_philos_full(obj);
	}
	return (NULL);
}
