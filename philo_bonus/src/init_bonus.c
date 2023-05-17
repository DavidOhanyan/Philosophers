/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 20:14:43 by dohanyan          #+#    #+#             */
/*   Updated: 2023/05/17 14:47:45 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <errno.h>
#include <string.h>

void init_main(t_main *main,char **argv)
{
	main->count_philo = ft_atoi(argv[1]);
	main->is_dead = 0;
	main->time_to_die = ft_atoi(argv[2]);
	if(argv[5])
		main->max_eat = ft_atoi(argv[5]);
	main->philos = (t_phlio *)malloc(sizeof(t_phlio) * main->count_philo);
}

void init_sem(t_sem *sems, int count_philo)
{
	unlink(SEM_DIE);
	unlink(SEM_EACH_EAT);
	unlink(SEM_FORKS);
	unlink(SEM_LAST_EAT);
	unlink(SEM_PRINT);
	sems->forks = sem_open(SEM_FORKS, O_CREAT, S_IRWXU, count_philo);
	sems->print = sem_open(SEM_PRINT, O_CREAT, S_IRWXU, 1);
	sems->die = sem_open(SEM_DIE, O_CREAT, S_IRWXU, 1);
	sems->each_eat = sem_open(SEM_EACH_EAT, O_CREAT, S_IRWXU, 1);
	sems->last_eat = sem_open(SEM_LAST_EAT, O_CREAT, S_IRWXU, 1);
	if(sems->forks == SEM_FAILED || sems->print == SEM_FAILED ||
	sems->die == SEM_FAILED || sems->each_eat == SEM_FAILED ||
	sems->last_eat == SEM_FAILED)
	{
		perror("sem_open()");
		exit(EXIT_FAILURE);
	}
}

void init_philo(t_main *main,char **argv)
{
	int i;
	t_sem sem;

	init_sem(&sem, main->count_philo);
	i = -1;
	while (++i < main->count_philo)
	{
		main->philos[i].count_each_eat = 0;
		main->philos[i].id = i;
		main->philos[i].date_of_eat = ft_atoi(argv[3]);
		main->philos[i].date_of_sleep = ft_atoi(argv[4]);
		main->philos[i].last_eat = 0;
		main->philos[i].is_dead = &(main->is_dead);
		main->philos[i].sems = &sem;
	}
	i = -1;
}