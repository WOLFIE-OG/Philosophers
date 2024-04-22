/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   god.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:43:45 by otodd             #+#    #+#             */
/*   Updated: 2024/04/22 18:39:33 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*bigbrother(void	*c)
{
	t_carbon	*carbon;

	carbon = (t_carbon *)c;
	while (!carbon->is_dead)
	{
		if ((int)(get_current_time() - carbon->last_ate) > carbon->earth->ttd)
		{
			l_has_died(carbon);
			carbon->state = DEAD;
			carbon->is_dead = true;
			sem_post(carbon->earth->death);
		}
	}
	return (NULL);
}

void	hell(t_earth *earth)
{
	int	i;

	i = -1;
	while (++i < earth->nop)
	{
		kill(earth->souls[i]->pid, 15);
		free(earth->souls[i]);
	}
	free(earth->souls);
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_FORKS);
}
