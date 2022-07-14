/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarneir <acarneir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 23:07:29 by acarneir          #+#    #+#             */
/*   Updated: 2022/07/13 23:48:34 by acarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	sleeping(t_args args)
{
	printf("%lld X is sleeping\n", timestamp(args.time_start));
	delay_ms(args.time_to_sleep);
	return (1);
}

int	thinking(t_args args)
{
	printf("%lld X is thinking\n", timestamp(args.time_start));
	delay_ms(1000);
	return (1);
}
