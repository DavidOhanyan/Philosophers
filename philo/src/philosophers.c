/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:19:54 by dohanyan          #+#    #+#             */
/*   Updated: 2023/05/11 20:21:20 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_main	philo;
	int		i;

	i = -1;
	my_get_time();
	if (check_init(&philo, argc, argv))
		return (0);
	while (++i < philo.count_philo)
		pthread_create(&(philo.s_philo[i].philo), NULL,
			(t_thread_handler)(&call_threads), &(philo.s_philo[i]));
	while (1)
	{
		if (die_check(&philo) == 1 || end_eat(&philo) == 1)
			break ;
	}
	i = -1;
	if (philo.count_philo != 1)
	{
		while (++i < philo.count_philo)
			pthread_join(philo.s_philo[i].philo, 0);
	}
	destroy_free(&philo);
	return (0);
}
