/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 20:14:43 by dohanyan          #+#    #+#             */
/*   Updated: 2023/05/21 20:53:24 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <errno.h>
#include <string.h>

void init_sem(t_phlio *philo, int count_philo)
{
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_DIE);
	sem_unlink(SEM_EACH_EAT);
	sem_unlink(SEM_FORKS);
	sem_unlink(LAST_EAT);
	philo->forks = sem_open(SEM_FORKS, O_CREAT, S_IRWXU, count_philo);
	philo->print = sem_open(SEM_PRINT, O_CREAT, S_IRWXU, 1);
	philo->die = sem_open(SEM_DIE, O_CREAT, S_IRWXU, 1);
	philo->each_eat = sem_open(SEM_EACH_EAT, O_CREAT, S_IRWXU, 1);
	philo->last_eat = sem_open(LAST_EAT, O_CREAT, S_IRWXU, 1);
	if (philo->forks == SEM_FAILED || philo->print == SEM_FAILED ||
	philo->die == SEM_FAILED || philo->each_eat == SEM_FAILED ||
	philo->last_eat == SEM_FAILED)
	{
		perror("sem_open()");
		exit(EXIT_FAILURE);
	}
}

void init_philo(t_phlio *philo,char **argv)
{
	philo->count_each_eat = 0;
	philo->date_of_eat = ft_atoi(argv[3]);
	philo->date_of_sleep = ft_atoi(argv[4]);
	philo->id = 0;
	philo->is_dead = 0;
	philo->philo_last_eat = 0;
	init_sem(philo,ft_atoi(argv[1]));
}

void init_main(t_main *main,char **argv)
{
	int i;
	t_phlio philo;
	
	i = -1;
	main->count_philo = ft_atoi(argv[1]);
	main->time_to_die = ft_atoi(argv[2]);
	if(argv[5])
		main->max_eat = ft_atoi(argv[5]);
	else
		main->max_eat = -1;
	
	main->philos = (t_phlio *)malloc(sizeof(t_phlio) * main->count_philo);
	init_philo(&philo, argv);
	while (++i < main->count_philo)
	{
		philo.id = i;
		main->philos[i] = philo;
	}
	
}
