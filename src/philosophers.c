/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarneir <acarneir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 21:03:30 by acarneir          #+#    #+#             */
/*   Updated: 2022/07/06 23:00:40 by acarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int argc, char *argv[])
{
	int	i;
	int	args[6];

	if (argc < 5 || argc > 6)
	{
		printf("Expected 4 or 5 arguments!\n");
		return (1);
	}
	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) <= 0)
		{
			printf("Invalid argument on position %d!\n", i);
			return (1);
		}
		args[i] = ft_atoi(argv[i]);
		printf("arg[%d] = %d\n", i, args[i]);
		i++;
	}
	return (0);
}
