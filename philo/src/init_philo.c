/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 17:21:21 by dohanyan          #+#    #+#             */
/*   Updated: 2023/05/10 21:32:24 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_t_main(t_main *philo, char **argv)
{
	philo->is_dead = 0;
	philo->count_philo = ft_atoi(argv[1]);
	if (philo->count_philo == 0)
		return (1);
	pthread_mutex_init(&(philo->mutex_write), NULL);
	pthread_mutex_init(&(philo->mutex_die), NULL);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->mutex = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t) * philo->count_philo);
	philo->s_philo = (t_info *)malloc(sizeof(t_info) * philo->count_philo);
	if (argv[5])
		philo->max_eat = ft_atoi(argv[5]);
	else
			philo->max_eat = -1;
	return (0);
}

void	init_t_info(t_main *philo, char **argv)
{
	int	i;

	i = 0;
	while (i < philo->count_philo)
	{
		philo->s_philo[i].id = 0;
		philo->s_philo[i].is_dead = &(philo->is_dead);
		philo->s_philo[i].count_each_eat = 0;
		philo->s_philo[i].date_of_eat = ft_atoi(argv[3]);
		philo->s_philo[i].date_of_sleep = ft_atoi(argv[4]);
		i++;
	}
}

void	init_mutex(t_main *philo)
{
	int	i;

	i = 0;
	while (i < philo->count_philo)
	{
		philo->s_philo[i].id = i;
		pthread_mutex_init(&(philo->mutex[i]), NULL);
		philo->s_philo[i].mutex_write = &(philo->mutex_write);
		philo->s_philo[i].mutex_die = &(philo->mutex_die);
		pthread_mutex_init(&(philo->s_philo[i].last_eat_mutex), NULL);
		pthread_mutex_init(&(philo->s_philo[i].each_eat), NULL);
		i++;
	}
	i = 0;
	while (i < philo->count_philo)
	{
		philo->s_philo[i].left = &philo->mutex[i];
		philo->s_philo[i].right = &philo->mutex[i + 1];
		if (i == philo->count_philo - 1)
		{
			philo->s_philo[i].left = &philo->mutex[i];
			philo->s_philo[i].right = &philo->mutex[0];
		}
		i++;
	}
}
