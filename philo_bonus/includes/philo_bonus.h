/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 20:32:37 by dohanyan          #+#    #+#             */
/*   Updated: 2023/05/21 20:41:09 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
#define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <time.h>
# include <semaphore.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>

#define SEM_PRINT "/sem_print"
#define SEM_DIE "/sem_die"
#define LAST_EAT "/sem_last_eat"
#define SEM_EACH_EAT "/sem_each_eat"
#define SEM_FORKS "/sem_forks"

typedef struct s_philo
{
	pid_t			pid;
	int				is_dead;
	unsigned long	philo_last_eat;
	int				id;
	int				date_of_eat;
	int				date_of_sleep;
	int				count_each_eat;
	pthread_t		thread;
	// t_sem			*sems;
	sem_t *die;
	sem_t *last_eat;
	sem_t *each_eat;
	sem_t *print;
	sem_t *forks;
	
}		t_phlio;

typedef struct s_main
{
	unsigned long	time_to_die;
	int				count_philo;
	int				max_eat;
	t_phlio			*philos;
}	t_main;

// typedef struct s_sem
// {
// 	sem_t *die;
// 	sem_t *last_eat;
// 	sem_t *each_eat;
// 	sem_t *print;
// 	sem_t *forks;
// }		t_sem;
	
// typedef struct s_philo
// {
// 	pid_t			pid;
// 	int				is_dead;
// 	unsigned long	last_eat;
// 	int				id;
// 	int				date_of_eat;
// 	int				date_of_sleep;
// 	int				count_each_eat;
// 	pthread_t		thread;
// 	t_sem			*sems;
	
// }		t_phlio;

// typedef struct s_main
// {
// 	unsigned long	time_to_die;
// 	int				count_philo;
// 	int				max_eat;
// 	int				is_dead;
// 	t_phlio			*philos;
// }	t_main;

typedef struct s_merg
{
	t_main *main;
	t_phlio *philo;	
}	t_merg;


int	check_neg_pos(char ch);
int	chech_args(char **argv);
int	check_siz_num(char **argv);
int	check_init(int argc, char **argv);
unsigned	long	my_get_time(void);
void	my_usleap(unsigned long t1);
long	ft_atoi(const char *str);
int	ft_strlen(const char	*s);
void init_sem(t_phlio *sems, int count_philo);
void init_philo(t_phlio *philo,char **argv);
void init_main(t_main *main,char **argv);
void unlink_close(t_phlio *philo);

#endif