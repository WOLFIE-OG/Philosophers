/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:21:18 by otodd             #+#    #+#             */
/*   Updated: 2024/04/18 16:33:33 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	l_taken_fork(t_carbon *c)
{
	if (!c->earth->solar_flare)
	{
		lock_mutex(c->earth->write_lock);
		printf(
			BBLU"%ld"RESET" %d has taken a fork\n",
			get_current_time(),
			c->id + 1
			);
		unlock_mutex(c->earth->write_lock);
	}
}

void	l_is_eating(t_carbon *c)
{
	if (!c->earth->solar_flare)
	{
		lock_mutex(c->earth->write_lock);
		printf(
			BCYN"%ld"RESET" %d is eating\n",
			get_current_time(),
			c->id + 1
			);
		unlock_mutex(c->earth->write_lock);
	}
}

void	l_is_sleeping(t_carbon *c)
{
	if (!c->earth->solar_flare)
	{
		lock_mutex(c->earth->write_lock);
		printf(
			BHMAG"%ld"RESET" %d is sleeping\n",
			get_current_time(),
			c->id + 1
			);
		unlock_mutex(c->earth->write_lock);
	}
}

void	l_is_thinking(t_carbon *c)
{
	if (!c->earth->solar_flare)
	{
		lock_mutex(c->earth->write_lock);
		printf(
			BYEL"%ld"RESET" %d is thinking\n",
			get_current_time(),
			c->id + 1
			);
		unlock_mutex(c->earth->write_lock);
	}
}

void	l_has_died(t_carbon *c)
{
	lock_mutex(c->earth->write_lock);
	printf(
		BRED"%ld"RESET" %d has died\n",
		get_current_time(),
		c->id + 1
		);
	unlock_mutex(c->earth->write_lock);
}
