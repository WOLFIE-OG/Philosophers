/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:21:18 by otodd             #+#    #+#             */
/*   Updated: 2024/04/24 17:05:25 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	ft_taken_fork(t_philo *philo)
{
	sem_wait(philo->ctx->write_lock);
	printf(
		BBLU"%ld"RESET" %d has taken a fork\n",
		ft_get_current_time(),
		philo->id + 1
		);
	sem_post(philo->ctx->write_lock);
}

void	ft_is_eating(t_philo *philo)
{
	sem_wait(philo->ctx->write_lock);
	printf(
		BCYN"%ld"RESET" %d is eating\n",
		ft_get_current_time(),
		philo->id + 1
		);
	sem_post(philo->ctx->write_lock);
}

void	ft_is_sleeping(t_philo *philo)
{
	sem_wait(philo->ctx->write_lock);
	printf(
		BHMAG"%ld"RESET" %d is sleeping\n",
		ft_get_current_time(),
		philo->id + 1
		);
	sem_post(philo->ctx->write_lock);
}

void	ft_is_thinking(t_philo *philo)
{
	sem_wait(philo->ctx->write_lock);
	printf(
		BYEL"%ld"RESET" %d is thinking\n",
		ft_get_current_time(),
		philo->id + 1
		);
	sem_post(philo->ctx->write_lock);
}

void	ft_has_died(t_philo *philo)
{
	sem_wait(philo->ctx->write_lock);
	printf(
		BRED"%ld"RESET" %d has died\n",
		ft_get_current_time(),
		philo->id + 1
		);
}
