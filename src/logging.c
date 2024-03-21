/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:21:18 by otodd             #+#    #+#             */
/*   Updated: 2024/03/21 17:06:57 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	l_taken_fork(t_carbon *c)
{
	t_earth	*const earth = (t_earth *)c->earth;

	pthread_mutex_lock(&earth->write_lock);
	printf(
		"["BBLU"%ld"RESET"]	%d has taken a fork\n",
		get_current_time(),
		c->id
		);
	pthread_mutex_unlock(&earth->write_lock);
}

void	l_is_eating(t_carbon *c)
{
	t_earth	*const earth = (t_earth *)c->earth;

	pthread_mutex_lock(&earth->write_lock);
	printf(
		"["BCYN"%ld"RESET"]	%d is eating\n",
		get_current_time(),
		c->id
		);
	pthread_mutex_unlock(&earth->write_lock);
}

void	l_is_sleeping(t_carbon *c)
{
	t_earth	*const earth = (t_earth *)c->earth;

	pthread_mutex_lock(&earth->write_lock);
	printf(
		"["BHMAG"%ld"RESET"]	%d is sleeping\n",
		get_current_time(),
		c->id
		);
	pthread_mutex_unlock(&earth->write_lock);
}

void	l_is_thinking(t_carbon *c)
{
	t_earth	*const earth = (t_earth *)c->earth;

	pthread_mutex_lock(&earth->write_lock);
	printf(
		"["BYEL"%ld"RESET"]	%d is thinking\n",
		get_current_time(),
		c->id
		);
	pthread_mutex_unlock(&earth->write_lock);
}

void	l_has_died(t_carbon *c)
{
	t_earth	*const earth = (t_earth *)c->earth;

	pthread_mutex_lock(&earth->write_lock);
	printf(
		"["BRED"%ld"RESET"]	%d has died\n",
		get_current_time(),
		c->id
		);
	pthread_mutex_unlock(&earth->write_lock);
}
