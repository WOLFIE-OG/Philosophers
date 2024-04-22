/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 18:13:55 by otodd             #+#    #+#             */
/*   Updated: 2024/04/22 18:39:27 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*life(void *i)
{
	t_carbon	*carbon;

	carbon = (t_carbon *)i;
	carbon->earth->is_parent = false;
	if (carbon->id % 2)
		slumber(carbon->earth->tte / 50, carbon);
	carbon->last_ate = get_current_time();
	pthread_create(&carbon->bigbrother, NULL, bigbrother, carbon);
	while (!carbon->is_dead)
	{
		eating(carbon);
		l_is_sleeping(carbon);
		carbon->state = SLEEPING;
		slumber(carbon->earth->tts, carbon);
		l_is_thinking(carbon);
		carbon->state = THINKING;
	}
	pthread_join(carbon->bigbrother, NULL);
	exit(0);
}
