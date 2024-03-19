/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:21:18 by otodd             #+#    #+#             */
/*   Updated: 2024/03/19 13:55:56 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	l_taken_fork(t_carbon *c)
{
	printf(
		"["BBLU"%ld"RESET"]	%d has taken a fork\n",
		get_current_time(),
		c->id
		);
}

void	l_is_eating(t_carbon *c)
{
	printf(
		"["BCYN"%ld"RESET"]	%d is eating\n",
		get_current_time(),
		c->id
		);
}

void	l_is_sleeping(t_carbon *c)
{
	printf(
		"["BHMAG"%ld"RESET"]	%d is sleeping\n",
		get_current_time(),
		c->id
		);
}

void	l_is_thinking(t_carbon *c)
{
	printf(
		"["BYEL"%ld"RESET"]	%d is thinking\n",
		get_current_time(),
		c->id
		);
}

void	l_has_died(t_carbon *c)
{
	printf(
		"["BRED"%ld"RESET"]	%d has died\n",
		get_current_time(),
		c->id
		);
}
