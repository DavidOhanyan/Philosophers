/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:20:05 by dohanyan          #+#    #+#             */
/*   Updated: 2023/05/17 20:05:40 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <time.h>

typedef void*	(*t_thread_handler)(void*);

typedef struct s_info
{
	unsigned long	last_eat;
	int				*is_dead;
	int				id;
	int				date_of_eat;
	int				date_of_sleep;
	int				count_each_eat;
	pthread_t		philo;
	pthread_mutex_t	last_eat_mutex;
	pthread_mutex_t	each_eat;
	pthread_mutex_t	*mutex_die;
	pthread_mutex_t	*mutex_write;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
}		t_info;

typedef struct s_main
{
	unsigned long	time_to_die;
	int				count_philo;
	int				max_eat;
	int				is_dead;
	t_info			*s_philo;
	pthread_mutex_t	mutex_write;
	pthread_mutex_t	mutex_die;
	pthread_mutex_t	*mutex;
}		t_main;

unsigned long	my_get_time(void);
int				init_t_main(t_main *philo, char **argv);
long			ft_atoi(const char *str);
int				ft_strlen(const char	*s);
void			init_t_info(t_main *philo, char **argv);
void			init_mutex(t_main *philo);
void			my_usleap(unsigned long t1);
int				chech_args(char **argv);
int				check_siz_num(char **argv);
int				die_check(t_main *philo);
int				end_eat(t_main *philo);
void			destroy_free(t_main *philo);
int				is_dead(t_info *philo);
void			my_print(t_info *philo, char *str, int id, unsigned	long time);
void			*call_threads(t_info *philo);
int				check_init(t_main *philo, int argc, char **argv);
int				check_neg_pos(char ch);
#endif