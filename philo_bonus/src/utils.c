/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:25:00 by otodd             #+#    #+#             */
/*   Updated: 2024/04/22 17:35:33 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

unsigned long	get_current_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * (unsigned long)1000) + (t.tv_usec / 1000));
}

void	slumber(unsigned long time, t_carbon *carbon)
{
	unsigned long	then;

	then = get_current_time();
	while (!carbon->is_dead)
	{
		if ((get_current_time() - then) >= time)
			break ;
		usleep(carbon->earth->nop * 2);
	}
}
