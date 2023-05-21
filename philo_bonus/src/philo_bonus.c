/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 20:30:26 by dohanyan          #+#    #+#             */
/*   Updated: 2023/05/21 22:12:44 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*call_threads(void *p)
{
	t_merg	*merg;

	merg = (t_merg *)p;
	while (1)
	{
		sem_wait(merg->philo->last_eat);
		if ((my_get_time() - merg->philo->philo_last_eat)
			> merg->main->time_to_die)
		{
			ft_print(merg->philo, "is dead", merg->philo->id, my_get_time());
			sem_wait(merg->philo->print);
			sem_post(merg->philo->last_eat);
			exit(1);
		}
		sem_post(merg->philo->last_eat);
		sem_wait(merg->philo->each_eat);
		if (merg->main->max_eat != -1
			&& merg->philo->count_each_eat >= merg->main->max_eat)
		{
			sem_post(merg->philo->each_eat);
			break ;
		}
		sem_post(merg->philo->each_eat);
	}
	return (NULL);
}

void	call_action(t_phlio *philo)
{
	sem_wait(philo->forks);
	ft_print(philo, "has taken a left fork", philo->id, my_get_time());
	sem_wait(philo->forks);
	ft_print(philo, "has taken a right fork", philo->id, my_get_time());
	ft_print(philo, "is eating", philo->id, my_get_time());
	sem_wait(philo->last_eat);
	philo->philo_last_eat = my_get_time();
	sem_post(philo->last_eat);
	my_usleap(philo->date_of_eat);
	sem_wait(philo->each_eat);
	philo->count_each_eat++;
	sem_post(philo->each_eat);
	sem_post(philo->forks);
	sem_post(philo->forks);
	sem_wait(philo->each_eat);
}

void	call_forks(t_main *m, int i)
{
	t_merg	merg;
	t_main	*main;
	t_phlio	*philo;

	main = (t_main *)m;
	merg.main = main;
	philo = &(main->philos[i]);
	merg.philo = philo;
	pthread_create(&(philo->thread), NULL, &call_threads, (void *)&merg);
	if (philo->id % 2 == 0)
		my_usleap(philo->date_of_eat);
	while (1)
	{
		call_action(philo);
		if (m->max_eat != -1 && philo->count_each_eat >= m->max_eat)
		{
			sem_post(philo->each_eat);
			break ;
		}
		sem_post(philo->each_eat);
		ft_print(philo, "is sleaping", philo->id, my_get_time());
		my_usleap(philo->date_of_sleep);
		ft_print(philo, "is thinking", philo->id, my_get_time());
	}
	pthread_join(philo->thread, NULL);
	exit(0);
}

void	create_forks(t_main *main)
{
	int	i;

	i = -1;
	while (++i < main->count_philo)
	{
		main->philos[i].pid = fork();
		if (main->philos[i].pid < 0)
		{
			perror("fork()");
			exit(EXIT_FAILURE);
		}
		if (main->philos[i].pid == 0)
			call_forks(main, i);
	}
	terminate(main);
}

int	main(int argc, char **argv)
{
	t_main	main;

	if (check_init(argc, argv))
		return (0);
	my_get_time();
	init_main(&main, argv);
	create_forks(&main);
	return (0);
}
