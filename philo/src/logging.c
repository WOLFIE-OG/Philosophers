/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:21:18 by otodd             #+#    #+#             */
/*   Updated: 2024/05/07 19:02:51 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_taken_fork(t_philo *philo)
{
	if (!philo->ctx->stop)
	{
		pthread_mutex_lock(&philo->ctx->write_lock);
		if (!philo->ctx->stop)
		{
			printf(
				BBLU"%013ld"RESET" %d has taken a fork\n",
				ft_get_current_time() - philo->ctx->start_time,
				philo->id + 1
				);
		}
		pthread_mutex_unlock(&philo->ctx->write_lock);
	}
}

void	ft_is_eating(t_philo *philo)
{
	if (!philo->ctx->stop)
	{
		pthread_mutex_lock(&philo->ctx->write_lock);
		if (!philo->ctx->stop)
		{
			printf(
				BCYN"%013ld"RESET" %d is eating\n",
				ft_get_current_time() - philo->ctx->start_time,
				philo->id + 1
				);
		}
		pthread_mutex_unlock(&philo->ctx->write_lock);
	}
}

void	ft_is_sleeping(t_philo *philo)
{
	if (!philo->ctx->stop)
	{
		pthread_mutex_lock(&philo->ctx->write_lock);
		if (!philo->ctx->stop)
		{
			printf(
				BHMAG"%013ld"RESET" %d is sleeping\n",
				ft_get_current_time() - philo->ctx->start_time,
				philo->id + 1
				);
		}
		pthread_mutex_unlock(&philo->ctx->write_lock);
	}
}

void	ft_is_thinking(t_philo *philo)
{
	if (!philo->ctx->stop)
	{
		pthread_mutex_lock(&philo->ctx->write_lock);
		if (!philo->ctx->stop)
		{
			printf(
				BYEL"%013ld"RESET" %d is thinking\n",
				ft_get_current_time() - philo->ctx->start_time,
				philo->id + 1
				);
		}
		pthread_mutex_unlock(&philo->ctx->write_lock);
	}
}

void	ft_has_died(t_philo *philo)
{
	if (!philo->ctx->stop)
	{
		pthread_mutex_lock(&philo->ctx->write_lock);
		if (!philo->ctx->stop)
		{
			printf(
				BRED"%013ld"RESET" %d has died\n",
				ft_get_current_time() - philo->ctx->start_time,
				philo->id + 1
				);
		}
		pthread_mutex_unlock(&philo->ctx->write_lock);
	}
}
