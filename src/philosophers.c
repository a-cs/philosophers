/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarneir <acarneir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 21:03:30 by acarneir          #+#    #+#             */
/*   Updated: 2022/07/16 00:50:11 by acarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	is_valid_input(int argc, char **argv)
{
	int			i;

	if (argc < 5 || argc > 6)
	{
		printf("Expected 4 or 5 arguments!\n");
		return (FALSE);
	}
	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) <= 0)
		{
			printf("Invalid argument on position %d!\n", i);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

void	initialize_philos(t_obj *obj)
{
	int	i;

	i = 0;
	while (i < obj->total_philos)
	{
		obj->philos[i].id = i;
		obj->philos[i].left_fork = i;
		obj->philos[i].right_fork = i + 1;
		if (i == obj->total_philos -1)
			obj->philos[i].right_fork = 0;
		obj->philos[i].meal_counter = 0;
		obj->philos[i].last_meal = get_current_time_ms();
		pthread_mutex_init(&obj->mutex.forks[i], NULL);
		obj->philos[i].obj = obj;
		i++;
	}
}

void	initialize_obj(t_obj *obj, char **argv)
{
	obj->total_philos = ft_atoi(argv[1]);
	obj->time_to_die = ft_atoi(argv[2]);
	obj->time_to_eat = ft_atoi(argv[3]);
	obj->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		obj->max_nbr_meals = ft_atoi(argv[5]);
	else
		obj->max_nbr_meals = 0;
	obj->time_start = get_current_time_ms();
	obj->stop = FALSE;
	obj->philos = malloc(obj->total_philos * sizeof(t_philo));
	obj->mutex.forks = malloc(obj->total_philos * sizeof(pthread_mutex_t));
	initialize_philos(obj);
	pthread_mutex_init(&obj->mutex.print, NULL);
}

void	exit_philo(t_obj *obj)
{
	int	i;

	i = 0;
	while (i < obj->total_philos)
	{
		pthread_mutex_destroy(&obj->mutex.forks[i]);
		i++;
	}
	pthread_mutex_destroy(&obj->mutex.print);
	if (obj->philos)
		free(obj->philos);
	if (obj->mutex.forks)
		free(obj->mutex.forks);
}

int	main(int argc, char **argv)
{
	int		i;
	t_obj	obj;

	if (!is_valid_input(argc, argv))
		return (1);
	initialize_obj(&obj, argv);
	i = 0;
	while (i < obj.total_philos)
	{
		pthread_create(&obj.philos[i].thread, NULL, &routine, &obj.philos[i]);
		i++;
	}
	pthread_create(&obj.observer, NULL, &observer_routine, &obj);
	i = 0;
	while (i < obj.total_philos)
	{
		pthread_join(obj.philos[i].thread, NULL);
		i++;
	}
	pthread_join(obj.observer, NULL);
	exit_philo(&obj);
	return (0);
}
