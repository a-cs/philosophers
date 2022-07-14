/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarneir <acarneir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 21:03:30 by acarneir          #+#    #+#             */
/*   Updated: 2022/07/13 23:46:13 by acarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

// void	*routine()
// {
// 	printf("Test from threads\n");
// 	usleep(1000000);
// 	printf("End of thread\n");
// 	return (0);
// }

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

void	initialize_args(t_args *args, char **argv)
{
	args->total = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		args->max_nbr_meals = ft_atoi(argv[5]);
	else
		args->max_nbr_meals = 0;
	args->time_start = get_current_time_ms();
}

int	main(int argc, char **argv)
{
	t_args	args;
	// pthread_t	t1, t2;

	// pthread_create(&t1, NULL, &routine, NULL);
	// pthread_create(&t2, NULL, &routine, NULL);
	// pthread_join(t1, NULL);
	// pthread_join(t2, NULL);
	
	if (!is_valid_input(argc, argv))
		return (1);
	initialize_args(&args, argv);
	sleeping(args);
	thinking(args);
	printf("total time = %lld\n", timestamp(args.time_start));
	return (0);
}
