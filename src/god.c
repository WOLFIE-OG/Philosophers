/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   god.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:43:45 by otodd             #+#    #+#             */
/*   Updated: 2024/04/04 19:21:37 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	start_life(t_earth *earth)
{
	int	i;

	i = -1;
	while (++i < earth->nop)
	{
		earth->souls[i]->last_ate = get_current_time();
		pthread_create(&earth->souls[i]->thread,
			NULL, life, earth->souls[i]);
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
