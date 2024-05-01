/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:21:18 by otodd             #+#    #+#             */
/*   Updated: 2024/05/01 17:24:02 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	ft_taken_fork(t_philo *philo)
{
	if (philo->max_ate)
		return ;
	sem_wait(philo->ctx->write_lock);
	printf(
		BBLU"%09ld"RESET" %d has taken a fork\n",
		ft_get_current_time() - philo->ctx->start_time,
		philo->id + 1
		);
	sem_post(philo->ctx->write_lock);
}

void	ft_is_eating(t_philo *philo)
{
	if (philo->max_ate)
		return ;
	sem_wait(philo->ctx->write_lock);
	printf(
		BCYN"%09ld"RESET" %d is eating\n",
		ft_get_current_time() - philo->ctx->start_time,
		philo->id + 1
		);
	sem_post(philo->ctx->write_lock);
}

void	ft_is_sleeping(t_philo *philo)
{
	if (philo->max_ate)
		return ;
	sem_wait(philo->ctx->write_lock);
	printf(
		BHMAG"%09ld"RESET" %d is sleeping\n",
		ft_get_current_time() - philo->ctx->start_time,
		philo->id + 1
		);
	sem_post(philo->ctx->write_lock);
}

void	ft_is_thinking(t_philo *philo)
{
	if (philo->max_ate)
		return ;
	sem_wait(philo->ctx->write_lock);
	printf(
		BYEL"%09ld"RESET" %d is thinking\n",
		ft_get_current_time() - philo->ctx->start_time,
		philo->id + 1
		);
	sem_post(philo->ctx->write_lock);
}

void	ft_has_died(t_philo *philo)
{
	sem_wait(philo->ctx->write_lock);
	printf(
		BRED"%09ld"RESET" %d has died\n",
		ft_get_current_time() - philo->ctx->start_time,
		philo->id + 1
		);
}
