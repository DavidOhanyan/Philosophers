/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_bfunctions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 20:16:38 by dohanyan          #+#    #+#             */
/*   Updated: 2023/05/21 00:08:52 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

unsigned	long	my_get_time(void)
{
	static unsigned long long	start;
	static int					call_count;
	struct timeval				t1;

	if (call_count == 0)
	{
		gettimeofday(&t1, NULL);
		start = (t1.tv_sec * 1000 + t1.tv_usec / 1000);
		call_count ++;
	}
	gettimeofday(&t1, NULL);
	return ((t1.tv_sec * 1000) + (t1.tv_usec / 1000) - start);
}

void	my_usleap(unsigned long t1)
{
	unsigned long	val;

	val = my_get_time();
	while (my_get_time() - val <= t1)
		usleep(50);
}
