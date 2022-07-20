/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarneir <acarneir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 23:07:29 by acarneir          #+#    #+#             */
/*   Updated: 2022/07/20 00:05:03 by acarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

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

static void	only_one(t_philo *philo)
{
	pthread_mutex_lock(&philo->obj->mutex.forks[philo->left_fork]);
	print_action(philo->obj, philo->id + 1, "has taken a fork");
	delay_ms(philo->obj->time_to_die);
	print_action(philo->obj, philo->id + 1, "died");
	pthread_mutex_unlock(&philo->obj->mutex.forks[philo->left_fork]);
	pthread_mutex_lock(&philo->obj->mutex.stop);
	philo->obj->stop = TRUE;
	pthread_mutex_unlock(&philo->obj->mutex.stop);
}

void	*routine(void *var)
{
	t_philo	*philo;

	philo = var;
	if (philo->obj->total_philos == 1)
		only_one(philo);
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
