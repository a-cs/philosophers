/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarneir <acarneir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 00:42:39 by acarneir          #+#    #+#             */
/*   Updated: 2022/07/16 01:15:21 by acarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*observer_routine(void *var)
{
	int		i;
	int		counter;
	t_obj	*obj;

	obj = var;
	while (!obj->stop)
	{
		if (obj->max_nbr_meals != 0)
		{
			i = 0;
			counter = 0;
			while (i < obj->total_philos)
			{
				if (obj->philos[i].meal_counter >= obj->max_nbr_meals)
					counter++;
				i++;
			}
			if (counter == obj->total_philos)
				obj->stop = TRUE;
		}
	}
	return (NULL);
}
