/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 18:13:55 by otodd             #+#    #+#             */
/*   Updated: 2024/05/14 14:33:52 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_monitor(t_ctx *ctx)
{
	int		i;

	i = 0;
	while (!ctx->stop)
	{
		if (ctx->philos[i].ctx->notepme != -1)
			if (ctx->philos[i].meals_eaten == ctx->philos[i].ctx->notepme)
				ctx->philos[i].is_full = true;
		if (ft_are_philos_full(ctx))
			ctx->stop = true;
		if (!ctx->philos[i].is_full)
		{
			if (((ft_get_current_time() - ctx->start_time)
					- ctx->philos[i].last_ate) > ctx->ttd)
			{
				if (!ctx->philos[i].is_full)
				{
					ft_has_died(&ctx->philos[i]);
					ctx->stop = true;
				}
			}
		}
		i = (i + 1) % ctx->nop;
		ft_sleep(1);
	}
}

static bool	ft_take_forks(t_philo *philo)
{
	if (philo->ctx->stop)
		return (false);
	if (philo->left_fork < philo->right_fork)
	{
		pthread_mutex_lock(philo->left_fork);
		ft_taken_fork(philo);
		if (philo->left_fork == philo->right_fork)
			return (false);
		pthread_mutex_lock(philo->right_fork);
		ft_taken_fork(philo);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		ft_taken_fork(philo);
		if (philo->left_fork == philo->right_fork)
			return (false);
		pthread_mutex_lock(philo->left_fork);
		ft_taken_fork(philo);
	}
	return (true);
}

static bool	ft_eating(t_philo *philo)
{
	if (!ft_take_forks(philo))
		return (false);
	ft_is_eating(philo);
	philo->last_ate = ft_get_current_time() - philo->ctx->start_time;
	philo->meals_eaten++;
	ft_sleep(philo->ctx->tte);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (true);
}

void	*ft_routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if (philo->id % 2)
		ft_sleep(100);
	while (true)
	{
		if (!ft_eating(philo) || philo->is_full || philo->ctx->stop)
			break ;
		ft_is_sleeping(philo);
		ft_sleep(philo->ctx->tts);
		ft_is_thinking(philo);
	}
	if (philo->left_fork == philo->right_fork)
		pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}
