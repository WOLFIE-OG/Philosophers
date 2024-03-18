/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:21:18 by otodd             #+#    #+#             */
/*   Updated: 2024/03/18 17:39:20 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	l_taken_fork(char *tmp)
{
	printf(
		"["BBLU"%ld"RESET"]	%s has taken a fork\n",
		get_current_time(),
		tmp
		);
}

void	l_is_eating(char *tmp)
{
	printf(
		"["BCYN"%ld"RESET"]	%s is eating\n",
		get_current_time(),
		tmp
		);
}

void	l_is_sleeping(char *tmp)
{
	printf(
		"["BHMAG"%ld"RESET"]	%s is sleeping\n",
		get_current_time(),
		tmp
		);
}

void	l_is_thinking(char *tmp)
{
	printf(
		"["BYEL"%ld"RESET"]	%s is thinking\n",
		get_current_time(),
		tmp
		);
}

void	l_has_died(char *tmp)
{
	printf(
		"["BRED"%ld"RESET"]	%s has died\n",
		get_current_time(),
		tmp
		);
}
