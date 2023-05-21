/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate_close.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 22:00:52 by dohanyan          #+#    #+#             */
/*   Updated: 2023/05/21 22:18:53 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	unlink_close(t_phlio *philo)
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
	free(main->philos);
}
