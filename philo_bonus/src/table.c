/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:39:26 by otodd             #+#    #+#             */
/*   Updated: 2024/04/22 18:28:10 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	eating(t_carbon *carbon)
{
	if (carbon->is_dead)
		return ;
	sem_wait(carbon->earth->forks);
	carbon->state = GOT_FIRST_FORK;
	l_taken_fork(carbon);
	sem_wait(carbon->earth->forks);
	carbon->state = GOT_SECOND_FORK;
	l_taken_fork(carbon);
	l_is_eating(carbon);
	carbon->last_ate = get_current_time();
	carbon->state = EATING;
	if (carbon->earth->notepme != -1)
	{
		carbon->meals_eaten++;
		sem_wait(carbon->earth->eaten);
	}
	slumber(carbon->earth->tte, carbon);
	sem_post(carbon->earth->forks);
	sem_post(carbon->earth->forks);
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
		earth->souls[i]->is_dead = false;
	}
}
