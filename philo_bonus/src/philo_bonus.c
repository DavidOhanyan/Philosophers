/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 20:30:26 by dohanyan          #+#    #+#             */
/*   Updated: 2023/05/21 20:53:45 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void unlink_close(t_phlio *philo)
{
	sem_close(philo->die);
	sem_close(philo->each_eat);
	sem_close(philo->forks);
	sem_close(philo->last_eat);
	sem_close(philo->print);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_DIE);
	sem_unlink(SEM_EACH_EAT);
	sem_unlink(SEM_FORKS);
	sem_unlink(LAST_EAT);
}

void	terminate(t_main *main)
{
	int	i;
	int	rv;

	i = 0;
	while (i <= main->count_philo)
	{

		waitpid(-1, &rv, 0);
		if (WEXITSTATUS(rv) > 0)
		{
			i = -1;
			while (++i < main->count_philo)
				kill(main->philos[i].pid, SIGKILL);
			break ;
		}
		i ++;
	}
	unlink_close(main->philos);
}

void *call_threads(void *p)
{
	t_merg *merg;
	t_main	*main;
	t_phlio *philo;

	merg = (t_merg *)p;
	
	main = merg->main;
	philo = merg->philo;
	
	while (1)
	{
		sem_wait(philo->last_eat);
		if ((my_get_time() - philo->philo_last_eat) > main->time_to_die)
		{
			sem_wait(philo->print);
			printf("%d [%lu] is die\n",philo->id + 1, my_get_time() - philo->philo_last_eat);
			sem_post(philo->print);
			sem_wait(philo->print);
			sem_post(philo->last_eat);
			exit(1);
		}
		sem_post(philo->last_eat);
		
		sem_wait(philo->each_eat);
		if(main->max_eat != -1 && philo->count_each_eat >= main->max_eat)
		{
			sem_post(philo->each_eat);
			break;
		}
		sem_post(philo->each_eat);
	}
	return (NULL);
}

void call_forks(t_main *m, int i)
{
	t_merg merg;
	t_main *main;
	t_phlio *philo;
	
	main = (t_main *)m;
	philo = &m->philos[i];
	
	merg.main = main;
	merg.philo = philo;
	
	pthread_create(&(philo->thread), NULL, &call_threads, (void *)&merg);
	if (philo->id % 2 == 0)
		my_usleap(philo->date_of_eat);
	while (1)
	{
		sem_wait(philo->forks);

		sem_wait(philo->print);//wait print
			printf("%d [%lu] has taken a left fork\n", philo->id +1,  my_get_time());
		sem_post(philo->print);//post print
		
		sem_wait(philo->forks);//right fork
		
		sem_wait(philo->print);//wait print
			printf("%d [%lu] has taken a right fork\n", philo->id +1,  my_get_time());
		sem_post(philo->print);//post print
		
		sem_wait(philo->print);//wait print
			printf("%d [%lu] is eating\n", philo->id +1,  my_get_time());
		sem_post(philo->print);//post print
		
		sem_wait(philo->last_eat);//wait last_eat
		philo->philo_last_eat = my_get_time();
		sem_post(philo->last_eat);//post last_eat

		my_usleap(philo->date_of_eat);
		
		sem_wait(philo->each_eat);//wait each_eat
		philo->count_each_eat++;
		sem_post(philo->each_eat);//post each_eat
			
		sem_post(philo->forks);//post forks
		sem_post(philo->forks);//post forks	
		
		sem_wait(philo->each_eat);//wait each_eat
		if(m->max_eat != -1 && philo->count_each_eat >= m->max_eat)
		{
			sem_post(philo->each_eat);
			break;	
		}
		sem_post(philo->each_eat);
		
		sem_wait(philo->print);//wait print
			printf("%d [%lu] is sleeping\n", philo->id +1,  my_get_time());	
		sem_post(philo->print);//post print
		
		my_usleap(philo->date_of_sleep);
		
		sem_wait(philo->print);//wait print
			printf("%d [%lu] is thinking\n", philo->id+1,  my_get_time());	
		sem_post(philo->print);//post print
	}
	pthread_join(philo->thread, NULL);
	exit(0);
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
			call_forks(main, i);		
	}
	terminate(main);
}

int main(int argc, char **argv)
{
	t_main main;
	if(check_init(argc,argv))
		return (0);
	my_get_time();
	
	init_main(&main, argv);
	create_forks(&main);
	return(0);	
}
