/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:08:37 by otodd             #+#    #+#             */
/*   Updated: 2024/04/18 17:08:51 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	lock_mutex(t_mutex *mutex)
{
	pthread_mutex_lock(&mutex->mutex);
	mutex->is_locked = true;
}

void	unlock_mutex(t_mutex *mutex)
{
	pthread_mutex_unlock(&mutex->mutex);
	mutex->is_locked = false;
}
