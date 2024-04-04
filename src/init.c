/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:06:41 by otodd             #+#    #+#             */
/*   Updated: 2024/04/04 19:23:48 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	parse_args(t_earth *earth, int arg_n, char **arg_a)
{
	earth->nop = ft_atoi(arg_a[1]);
	earth->ttd = ft_atoi(arg_a[2]);
	earth->tte = ft_atoi(arg_a[3]);
	earth->tts = ft_atoi(arg_a[4]);
	if (arg_n == 6)
		earth->notepme = ft_atoi(arg_a[5]);
	else
		earth->notepme = -1;
}

static void	bigbrother(t_earth *earth)
{
	int		i;

	i = 0;
	while (!earth->solar_flare)
	{
		if (earth->notepme != -1)
			if (get_current_total_eaten_meals(earth) >= earth->notepme)
				earth->solar_flare = true;
		if ((int)(get_current_time() - earth->souls[i]->last_ate) >= earth->ttd)
		{
			earth->solar_flare = true;
			l_has_died(earth->souls[i]);
			earth->souls[i]->state = DEAD;
			pthread_mutex_unlock(earth->souls[i]->left_fork);
			pthread_mutex_unlock(earth->souls[i]->right_fork);
		}
		i = (i + 1) % earth->nop;
		usleep(10);
	}
}

int	main(int arg_n, char **arg_a)
{
	t_earth	earth;

	if (arg_n < 4)
		return (EXIT_FAILURE);
	earth.solar_flare = false;
	earth.ready = false;
	parse_args(&earth, arg_n, arg_a);
	if (!create_locks(&earth))
		return (EXIT_FAILURE);
	invite_philos(&earth);
	start_life(&earth);
	bigbrother(&earth);
	hell(&earth);
	return (EXIT_SUCCESS);
}
