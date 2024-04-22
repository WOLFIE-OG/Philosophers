/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   god.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:43:45 by otodd             #+#    #+#             */
/*   Updated: 2024/04/22 16:07:17 by otodd            ###   ########.fr       */
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
			if (get_current_total_eaten_meals(earth)
				>= earth->notepme * earth->nop)
				earth->solar_flare = true;
		if ((int)(get_current_time() - earth->souls[i]->last_ate) > earth->ttd)
		{
			earth->solar_flare = true;
			l_has_died(earth->souls[i]);
			earth->souls[i]->state = DEAD;
			earth->souls[i]->is_dead = true;
			if (earth->souls[i]->left_fork->is_locked)
				unlock_mutex(earth->souls[i]->left_fork);
			if (earth->souls[i]->right_fork->is_locked)
				unlock_mutex(earth->souls[i]->right_fork);
		}
		i = (i + 1) % earth->nop;
	}
}

bool	create_locks(t_earth *earth)
{
	earth->write_lock = malloc(sizeof(t_mutex));
	if (pthread_mutex_init(&earth->write_lock->mutex, NULL))
		return (false);
	if (!set_table(earth))
		return (false);
	return (true);
}

void	hell(t_earth *earth)
{
	int	i;

	while (!are_souls_finished(earth))
		usleep(100);
	i = -1;
	while (++i < earth->nop)
		pthread_join(earth->souls[i]->thread, NULL);
	i = -1;
	while (++i < earth->nop)
	{
		pthread_mutex_destroy(&earth->forks[i].mutex);
		free(earth->souls[i]);
	}
	free(earth->souls);
	free(earth->forks);
	pthread_mutex_destroy(&earth->write_lock->mutex);
	free(earth->write_lock);
}
