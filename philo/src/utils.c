/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:25:00 by otodd             #+#    #+#             */
/*   Updated: 2024/04/18 17:09:41 by otodd            ###   ########.fr       */
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
	while (!carbon->earth->solar_flare && carbon->state != DEAD)
	{
		if ((get_current_time() - then) >= time)
			break ;
		usleep(carbon->earth->nop * 2);
	}
}

int	get_current_total_eaten_meals(t_earth *earth)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (++i < earth->nop)
		count += earth->souls[i]->meals_eaten;
	return (count);
}

int	get_total_soul_ready_count(t_earth *earth)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (++i < earth->nop)
		if (earth->souls[i]->is_ready)
			count++;
	return (count);
}

bool	are_souls_finished(t_earth *earth)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (++i < earth->nop)
		if (earth->souls[i]->is_finished)
			count++;
	if (count == earth->nop)
		return (true);
	else
		return (false);
}
