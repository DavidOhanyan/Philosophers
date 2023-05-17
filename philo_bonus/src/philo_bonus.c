/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 20:30:26 by dohanyan          #+#    #+#             */
/*   Updated: 2023/05/17 21:59:18 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	is_dead(t_phlio *philo)
{
	int	rv;

	sem_wait(philo->sems->die);
	rv = *(philo->is_dead);
	sem_post(philo->sems->die);
	return (rv);
}

void *call_threads(void *p)
{
	t_phlio *philo;

	philo = (t_phlio *)p;

	return (NULL);
}

void call_forks(t_main *main, int i)
{
	t_phlio* philo;
	
	philo = &main->philos[i];
	pthread_create(&(philo->thread), NULL, &call_threads, (void *)&philo);
	if (philo->id % 2 != 0)
		my_usleap(philo->date_of_eat);
	while (1)
	{
		sem_wait(philo->sems->forks);//left fork
		sem_wait(philo->sems->print);//wait print
		printf("%d [%lu] has taken a left fork", philo->id,  my_get_time());
		sem_post(philo->sems->print);//post print
		sem_wait(philo->sems->forks);//right fork
		sem_wait(philo->sems->print);//wait print
		printf("%d [%lu] has taken a right fork", philo->id,  my_get_time());
		sem_post(philo->sems->print);//post print
		sem_wait(philo->sems->print);//wait print
		printf("%d [%lu] is eating", philo->id,  my_get_time());
		sem_post(philo->sems->print);//post print
		sem_wait(philo->sems->each_eat);//wait each_eat
		philo->count_each_eat++;
		sem_post(philo->sems->each_eat);//post each_eat	
		sem_wait(philo->sems->last_eat);//wait last_eat
		philo->last_eat = my_get_time();
		sem_wait(philo->sems->last_eat);//post last_eat
		my_usleap(philo->date_of_eat);
		sem_post(philo->sems->forks);//post forks
		sem_post(philo->sems->forks);//post forks	
		if()
		
		sem_wait(philo->sems->print);//wait print
		printf("%d [%lu] is sleeping", philo->id,  my_get_time());	
		sem_post(philo->sems->print);//post print
		my_usleap(philo->date_of_sleep);
		sem_wait(philo->sems->print);//wait print
		printf("%d [%lu] is thinking", philo->id,  my_get_time());	
		sem_post(philo->sems->print);//post print
	}
	pthread_join(philo->thread, NULL);
}

void create_forks(t_main *main)
{
	int i;

	i = -1;
	while (++i < main->count_philo)
	{
		main->philos[i].pid = fork();
		if(main->philos[i].pid < 0)
		{
			perror("fork()");
			exit(EXIT_FAILURE);
		}
		if(main->philos[i].pid == 0)
			call_forks(main,i);		
	}
	// retminate
}

int main(int argc, char **argv)
{
	t_main main;
	// int i;
	
	if(check_init(&main,argc,argv))
		return (0);
	init_main(&main,argv);
	init_philo(&main,argv);
	my_get_time();
	
	

	return(0);	
}
