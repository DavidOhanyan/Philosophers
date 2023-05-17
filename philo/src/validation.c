/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohanyan <dohanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 22:04:31 by dohanyan          #+#    #+#             */
/*   Updated: 2023/05/10 22:08:43 by dohanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_neg_pos(char ch)
{
	if (ch == '-')
		return (0);
	return (1);
}

int	chech_args(char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (argv[i][0] == '-' || argv[i][0] == '+')
			{
				if (check_neg_pos(argv[i][0]) == 0)
					return (1);
				j++;
			}
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_siz_num(char **argv)
{
	long	val;
	int		i;

	i = 1;
	val = 0;
	while (argv[i])
	{
		if (ft_strlen(argv[i]) > 10 || ft_atoi(argv[i]) > 2147483647)
			return (1);
		i++;
	}
	return (0);
}

int	check_init(t_main *philo, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		write (2, "Error\n", 6);
		return (1);
	}
	if (chech_args(argv) == 1 || check_siz_num(argv) == 1)
	{
		write (2, "Error\n", 6);
		return (1);
	}
	if (init_t_main(philo, argv) == 1)
		return (1);
	init_t_info(philo, argv);
	init_mutex(philo);
	return (0);
}
