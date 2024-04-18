/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:06:41 by otodd             #+#    #+#             */
/*   Updated: 2024/04/18 14:49:06 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool	parse_args(t_earth *earth, int arg_n, char **arg_a)
{
	if (arg_n == 1 || arg_n > 6)
		return (false);
	if (!ft_ischeck_str(arg_a[1], ft_isdigit))
		return (false);
	earth->nop = ft_atoi(arg_a[1]);
	if (!ft_ischeck_str(arg_a[2], ft_isdigit))
		return (false);
	earth->ttd = ft_atoi(arg_a[2]);
	if (!ft_ischeck_str(arg_a[3], ft_isdigit))
		return (false);
	earth->tte = ft_atoi(arg_a[3]);
	if (!ft_ischeck_str(arg_a[4], ft_isdigit))
		return (false);
	earth->tts = ft_atoi(arg_a[4]);
	if (arg_n == 6)
	{
		if (!ft_ischeck_str(arg_a[5], ft_isdigit))
			return (false);
		earth->notepme = ft_atoi(arg_a[5]);
	}
	else
		earth->notepme = -1;
	return (true);
}

int	main(int arg_n, char **arg_a)
{
	t_earth	earth;

	if (!parse_args(&earth, arg_n, arg_a))
	{
		printf("Program usage: ");
		printf("./philo <number_of_philosophers> <time_to_die time_to_eat> ");
		printf("<time_to_sleep> [number_of_times_each_philosopher_must_eat]\n");
		return (EXIT_FAILURE);
	}
	if (!create_locks(&earth))
		return (EXIT_FAILURE);
	earth.solar_flare = false;
	invite_philos(&earth);
	start_life(&earth);
	bigbrother(&earth);
	hell(&earth);
	return (EXIT_SUCCESS);
}
