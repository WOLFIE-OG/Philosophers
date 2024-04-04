/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:39:26 by otodd             #+#    #+#             */
/*   Updated: 2024/04/04 19:23:08 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	take_fork(t_carbon *carbon)
{
	if (carbon->left_fork < carbon->right_fork)
	{
		pthread_mutex_lock(carbon->left_fork);
		carbon->state = GOT_FIRST_FORK;
		l_taken_fork(carbon);
		pthread_mutex_lock(carbon->right_fork);
		carbon->state = GOT_SECOND_FORK;
		l_taken_fork(carbon);
	}
	else
	{
		pthread_mutex_lock(carbon->right_fork);
		carbon->state = GOT_FIRST_FORK;
		l_taken_fork(carbon);
		pthread_mutex_lock(carbon->left_fork);
		carbon->state = GOT_SECOND_FORK;
		l_taken_fork(carbon);
	}
}

void	eating(t_carbon *carbon)
{
	take_fork(carbon);
	l_is_eating(carbon);
	carbon->state = EATING;
	if (carbon->earth->notepme != -1)
		carbon->meals_eaten++;
	carbon->last_ate = get_current_time();
	slumber(carbon->earth->tte, carbon);
	pthread_mutex_unlock(carbon->left_fork);
	pthread_mutex_unlock(carbon->right_fork);
}

bool	set_table(t_earth *earth)
{
	int	i;

	i = -1;
	earth->forks = malloc(sizeof(pthread_mutex_t) * earth->nop);
	while (++i < earth->nop)
		if (pthread_mutex_init(&earth->forks[i], NULL))
			return (false);
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
		earth->souls[i]->ready = false;
		earth->souls[i]->left_fork = &earth->forks[i];
		earth->souls[i]->right_fork = &earth->forks[(i + 1) % earth->nop];
	}
}
