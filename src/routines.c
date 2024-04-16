/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 18:13:55 by otodd             #+#    #+#             */
/*   Updated: 2024/04/15 18:32:50 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*life(void *i)
{
	t_carbon	*carbon;

	carbon = (t_carbon *)i;
	carbon->is_ready = true;
	while (get_total_soul_ready_count(carbon->earth) != carbon->earth->nop)
		usleep(10);
	if (carbon->id % 2 && carbon->earth->nop > 1)
		slumber(carbon->earth->tte / 50, carbon);
	while (!carbon->earth->solar_flare && carbon->state != DEAD)
	{
		eating(carbon);
		l_is_sleeping(carbon);
		carbon->state = SLEEPING;
		slumber(carbon->earth->tts, carbon);
		l_is_thinking(carbon);
		carbon->state = THINKING;
	}
	return (NULL);
}
