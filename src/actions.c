/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarneir <acarneir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 23:07:29 by acarneir          #+#    #+#             */
/*   Updated: 2022/07/15 23:36:20 by acarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	print_action(t_obj *obj, int id, char *str)
{
	pthread_mutex_lock(&obj->mutex.print);
	printf("%lld\t\t%d\t%s\n", timestamp(obj->time_start), id, str);
	pthread_mutex_unlock(&obj->mutex.print);
}

static void	sleeping(t_philo *philo)
{
	print_action(philo->obj, philo->id, "is sleeping");
	// printf("%6lld %3d is sleeping\n", timestamp(philo->obj->time_start),
	// 	philo->id);
	delay_ms(philo->obj->time_to_sleep);
}

static void	thinking(t_philo *philo)
{
	print_action(philo->obj, philo->id, "is thinking");
	// printf("%6lld %3d is thinking\n", timestamp(philo->obj->time_start),
	// 	philo->id);
	delay_ms(10);
}

void	*routine(void *var)
{
	t_philo	*philo;

	philo = var;
	if (philo->id % 2 != 0)
		delay_ms(2);
	// while (!philo->obj->stop)
	while (philo->meal_counter < philo->obj->max_nbr_meals)
	{
		sleeping(philo);
		thinking(philo);
		philo->meal_counter++;
	}
	return (NULL);
}
