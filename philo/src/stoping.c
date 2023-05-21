/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stoping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:51:50 by dohanyan          #+#    #+#             */
/*   Updated: 2023/05/21 00:16:05 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	die_check(t_main *philo)
{
	int	j;

	j = -1;
	while (++j < philo->count_philo)
	{
		pthread_mutex_lock(&(philo->s_philo[j].last_eat_mutex));
		if ((my_get_time() - philo->s_philo[j].last_eat) > philo->time_to_die)
		{
			pthread_mutex_lock(&philo->mutex_die);
			philo->is_dead = 1;
			pthread_mutex_unlock(&philo->mutex_die);
			pthread_mutex_lock(&philo->mutex_write);
			printf("%d [%lu] is died\n", philo->s_philo[j].id + 1,
				my_get_time() - philo->s_philo[j].last_eat);
			pthread_mutex_unlock(&philo->mutex_write);
			pthread_mutex_unlock(&(philo->s_philo[j].last_eat_mutex));
			return (1);
		}
		pthread_mutex_unlock(&(philo->s_philo[j].last_eat_mutex));
	}
	return (0);
}

int	end_eat(t_main *philo)
{
	int	i;

	i = 0;
	while (philo->max_eat != -1 && i < philo->count_philo)
	{
		pthread_mutex_lock(&philo->s_philo[i].each_eat);
		if (philo->s_philo[i].count_each_eat >= philo->max_eat)
		{
			pthread_mutex_unlock(&(philo->s_philo[i].each_eat));
			i++;
		}
		else
		{
			pthread_mutex_unlock(&(philo->s_philo[i].each_eat));
			break ;
		}
	}
	if (i == philo->count_philo)
	{
		pthread_mutex_lock(&philo->mutex_die);
		philo->is_dead = 1;
		pthread_mutex_unlock(&philo->mutex_die);
		return (1);
	}
	return (0);
}
