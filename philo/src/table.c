/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:39:26 by otodd             #+#    #+#             */
/*   Updated: 2024/04/18 17:13:40 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	take_fork(t_carbon *carbon)
{
	if (&carbon->left_fork->mutex < &carbon->right_fork->mutex)
	{
		lock_mutex(carbon->left_fork);
		carbon->state = GOT_FIRST_FORK;
		l_taken_fork(carbon);
		lock_mutex(carbon->right_fork);
		carbon->state = GOT_SECOND_FORK;
		l_taken_fork(carbon);
	}
	else
	{
		lock_mutex(carbon->right_fork);
		carbon->state = GOT_FIRST_FORK;
		l_taken_fork(carbon);
		lock_mutex(carbon->left_fork);
		carbon->state = GOT_SECOND_FORK;
		l_taken_fork(carbon);
	}
}

void	eating(t_carbon *carbon)
{
	if (carbon->earth->solar_flare)
		return ;
	take_fork(carbon);
	l_is_eating(carbon);
	carbon->last_ate = get_current_time();
	carbon->state = EATING;
	if (carbon->earth->notepme != -1)
		carbon->meals_eaten++;
	slumber(carbon->earth->tte, carbon);
	unlock_mutex(carbon->left_fork);
	unlock_mutex(carbon->right_fork);
}

bool	set_table(t_earth *earth)
{
	int	i;

	i = -1;
	earth->forks = malloc(sizeof(t_mutex) * earth->nop);
	while (++i < earth->nop)
	{
		if (pthread_mutex_init(&earth->forks[i].mutex, NULL))
			return (false);
		earth->forks[i].is_locked = false;
	}
	return (true);
}

void	invite_philos(t_earth *earth)
{
	int		i;

	earth->souls = malloc(sizeof(t_carbon) * earth->nop);
	i = -1;
	while (++i < earth->nop)
	{
		earth->souls[i] = malloc(sizeof(t_carbon));
		earth->souls[i]->id = i;
		earth->souls[i]->meals_eaten = 0;
		earth->souls[i]->state = NONE;
		earth->souls[i]->earth = earth;
		earth->souls[i]->is_ready = false;
		earth->souls[i]->is_dead = false;
		earth->souls[i]->is_finished = false;
		earth->souls[i]->left_fork = &earth->forks[i];
		earth->souls[i]->right_fork = &earth->forks[(i + 1) % earth->nop];
	}
}
