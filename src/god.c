/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   god.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:43:45 by otodd             #+#    #+#             */
/*   Updated: 2024/04/17 17:07:07 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	start_life(t_earth *earth)
{
	int	i;

	i = -1;
	while (++i < earth->nop)
	{
		pthread_create(&earth->souls[i]->thread,
			NULL, life, earth->souls[i]);
		earth->souls[i]->last_ate = get_current_time();
	}
}

void	bigbrother(t_earth *earth)
{
	int		i;

	i = 0;
	while (!earth->solar_flare)
	{
		if (earth->notepme != -1)
			if (get_current_total_eaten_meals(earth) >= earth->notepme * earth->nop)
				earth->solar_flare = true;
		if ((int)(get_current_time() - earth->souls[i]->last_ate) >= earth->ttd + 1)
		{
			earth->solar_flare = true;
			l_has_died(earth->souls[i]);
			earth->souls[i]->state = DEAD;
			earth->souls[i]->is_dead = true;
			pthread_mutex_unlock(earth->souls[i]->left_fork);
			pthread_mutex_unlock(earth->souls[i]->right_fork);
		}
		i = (i + 1) % earth->nop;
	}
}

bool	create_locks(t_earth *earth)
{
	if (pthread_mutex_init(&earth->write_lock, NULL))
		return (false);
	if (!set_table(earth))
		return (false);
	return (true);
}

void	hell(t_earth *earth)
{
	int	i;

	i = -1;
	while (++i < earth->nop)
	{
		pthread_join(earth->souls[i]->thread, NULL);
		pthread_mutex_destroy(&earth->forks[i]);
		free(earth->souls[i]);
	}
	free(earth->souls);
	free(earth->forks);
	pthread_mutex_destroy(&earth->write_lock);
}
