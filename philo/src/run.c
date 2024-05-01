/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 18:13:55 by otodd             #+#    #+#             */
/*   Updated: 2024/05/01 17:26:30 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_monitor(t_ctx *ctx)
{
	int		i;

	i = 0;
	while (!ctx->stop)
	{
		if ((ft_get_total_eaten_meals(ctx) >= ctx->notepme * ctx->nop)
			&& ctx->notepme != -1)
			ctx->stop = true;
		if (((ft_get_current_time() - ctx->start_time)
				- ctx->philos[i]->last_ate) > ctx->ttd)
		{
			pthread_mutex_unlock(&ctx->write_lock);
			ft_has_died(ctx->philos[i]);
			ctx->stop = true;
		}
		i = (i + 1) % ctx->nop;
		ft_sleep(1);
	}
}

static void	ft_take_forks(t_philo *philo)
{
	if (philo->left_fork < philo->right_fork)
	{
		pthread_mutex_lock(philo->left_fork);
		ft_taken_fork(philo);
		pthread_mutex_lock(philo->right_fork);
		ft_taken_fork(philo);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		ft_taken_fork(philo);
		pthread_mutex_lock(philo->left_fork);
		ft_taken_fork(philo);
	}
}

static void	ft_eating(t_philo *philo)
{
	if (philo->ctx->stop)
		return ;
	ft_take_forks(philo);
	ft_is_eating(philo);
	philo->last_ate = ft_get_current_time() - philo->ctx->start_time;
	ft_sleep(philo->ctx->tte);
	if (philo->ctx->notepme != -1)
		philo->meals_eaten++;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*ft_routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if (philo->id % 2)
		ft_sleep(100);
	while (!philo->ctx->stop)
	{
		ft_eating(philo);
		if (philo->ctx->stop)
			break ;
		ft_is_sleeping(philo);
		ft_sleep(philo->ctx->tts);
		if (philo->ctx->stop)
			break ;
		ft_is_thinking(philo);
	}
	philo->is_finished = true;
	return (NULL);
}
