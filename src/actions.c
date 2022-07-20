/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarneir <acarneir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 23:07:29 by acarneir          #+#    #+#             */
/*   Updated: 2022/07/19 22:41:59 by acarneir         ###   ########.fr       */
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

static void	sleeping(t_philo *philo)
{
	print_action(philo->obj, philo->id + 1, "is sleeping");
	delay_ms(philo->obj->time_to_sleep);
}

static void	thinking(t_philo *philo)
{
	print_action(philo->obj, philo->id + 1, "is thinking");
}

static void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->obj->mutex.forks[philo->left_fork]);
	print_action(philo->obj, philo->id + 1, "has taken a fork");
	pthread_mutex_lock(&philo->obj->mutex.forks[philo->right_fork]);
	print_action(philo->obj, philo->id + 1, "has taken a fork");
	print_action(philo->obj, philo->id + 1, "is eating");
	pthread_mutex_lock(&philo->obj->mutex.last_meal[philo->id]);
	philo->last_meal = get_current_time_ms();
	pthread_mutex_unlock(&philo->obj->mutex.last_meal[philo->id]);
	delay_ms(philo->obj->time_to_eat);
	pthread_mutex_lock(&philo->obj->mutex.meal_counter[philo->id]);
	philo->meal_counter++;
	pthread_mutex_unlock(&philo->obj->mutex.meal_counter[philo->id]);
	pthread_mutex_unlock(&philo->obj->mutex.forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->obj->mutex.forks[philo->right_fork]);
}

void	*routine(void *var)
{
	t_philo	*philo;

	philo = var;
	if (philo->id % 2 != 0)
		delay_ms(5);
	while (!has_stoped(philo->obj))
	{
		if (!has_stoped(philo->obj))
			eating(philo);
		if (!has_stoped(philo->obj))
			sleeping(philo);
		if (!has_stoped(philo->obj))
			thinking(philo);
	}
	return (NULL);
}
