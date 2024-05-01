/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 18:13:55 by otodd             #+#    #+#             */
/*   Updated: 2024/05/01 11:59:47 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	ft_sleep(unsigned long time, t_philo *philo)
{
	unsigned long	then;

	then = ft_get_current_time();
	while (!philo->ctx->stop && !philo->is_dead)
	{
		if ((ft_get_current_time() - then) >= time)
			break ;
		usleep(100);
	}
}

void	ft_monitor(t_ctx *ctx)
{
	int		i;

	i = 0;
	while (!ctx->stop)
	{
		if ((ft_get_total_eaten_meals(ctx) >= ctx->notepme * ctx->nop)
			&& ctx->notepme != -1)
			ctx->stop = true;
		if ((int)(ft_get_current_time() - ctx->philos[i]->last_ate) > ctx->ttd)
		{
			ft_has_died(ctx->philos[i]);
			ctx->stop = true;
			ctx->philos[i]->is_dead = true;
		}
		usleep(100);
		i = (i + 1) % ctx->nop;
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
	philo->last_ate = ft_get_current_time();
	if (philo->ctx->notepme != -1)
		philo->meals_eaten++;
	ft_sleep(philo->ctx->tte, philo);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*ft_routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	philo->is_ready = true;
	while (ft_get_total_philo_ready_count(philo->ctx) != philo->ctx->nop)
		usleep(100);
	if (philo->id % 2)
		ft_sleep(100, philo);
	while (!philo->ctx->stop && !philo->is_dead)
	{
		ft_eating(philo);
		if (philo->ctx->stop)
			break ;
		ft_is_sleeping(philo);
		ft_sleep(philo->ctx->tts, philo);
		if (philo->ctx->stop)
			break ;
		ft_is_thinking(philo);
	}
	philo->is_finished = true;
	return (NULL);
}
