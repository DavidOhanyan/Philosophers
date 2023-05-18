/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 22:06:43 by dohanyan          #+#    #+#             */
/*   Updated: 2023/05/18 19:39:42 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_free(t_main *philo)
{
	int	i;

	i = 0;
	while (i < philo->count_philo)
		pthread_mutex_destroy(&(philo->mutex[i++]));
	pthread_mutex_destroy(&philo->mutex_write);
	pthread_mutex_destroy(&philo->mutex_die);
	free(philo->mutex);
	free(philo->s_philo);
}

int	is_dead(t_info *philo)
{
	int	rv;

	pthread_mutex_lock(philo->mutex_die);
	rv = *(philo->is_dead);
	pthread_mutex_unlock(philo->mutex_die);
	return (rv);
}

void	my_print(t_info *philo, char *str, int id, unsigned	long time)
{
	pthread_mutex_lock(philo->mutex_write);
	if (!is_dead(philo))
		printf("%d [%lu] %s\n", id, time, str);
	pthread_mutex_unlock(philo->mutex_write);
}

void	*call_threads(t_info *philo)
{
	if (philo->id % 2 != 0)
		my_usleap(philo->date_of_eat);
	while (!is_dead(philo))
	{	
		pthread_mutex_lock(philo->left);
		my_print(philo, "has taken a left fork", philo->id + 1, my_get_time());
		pthread_mutex_lock(philo->right);
		my_print(philo, "has taken a right fork", philo->id + 1, my_get_time());
		my_print(philo, "is eating", philo->id + 1, my_get_time());
		pthread_mutex_lock(&philo->last_eat_mutex);
		philo->last_eat = my_get_time();
		pthread_mutex_unlock(&philo->last_eat_mutex);
		my_usleap(philo->date_of_eat);
		pthread_mutex_lock(&philo->each_eat);//
		philo->count_each_eat++;//
		pthread_mutex_unlock(&philo->each_eat);//
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
		my_print(philo, "is sleeping", philo->id + 1, my_get_time());
		my_usleap(philo->date_of_sleep);
		my_print(philo, "is thinking", philo->id + 1, my_get_time());
	}
	return (NULL);
}
