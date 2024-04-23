/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 18:13:55 by otodd             #+#    #+#             */
/*   Updated: 2024/04/23 18:24:52 by otodd            ###   ########.fr       */
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
		usleep(philo->ctx->nop * 2);
	}
}

void	ft_monitor(t_ctx *ctx)
{
	int		i;

	i = 0;
	while (!ctx->stop)
	{
		if (ctx->notepme != -1)
			if (ft_get_current_total_eaten_meals(ctx)
				>= ctx->notepme * ctx->nop)
				ctx->stop = true;
		if ((int)(ft_get_current_time() - ctx->philos[i]->last_ate) > ctx->ttd)
		{
			ft_has_died(ctx->philos[i]);
			ctx->stop = true;
			ctx->philos[i]->is_dead = true;
			if (ctx->philos[i]->left_fork->is_locked)
				ft_unlock_mutex(ctx->philos[i]->left_fork);
			if (ctx->philos[i]->right_fork->is_locked)
				ft_unlock_mutex(ctx->philos[i]->right_fork);
		}
		i = (i + 1) % ctx->nop;
	}
}

static void	ft_take_forks(t_philo *philo)
{
	if (&philo->left_fork->mutex < &philo->right_fork->mutex)
	{
		ft_lock_mutex(philo->left_fork);
		ft_taken_fork(philo);
		ft_lock_mutex(philo->right_fork);
		ft_taken_fork(philo);
	}
	else
	{
		ft_lock_mutex(philo->right_fork);
		ft_taken_fork(philo);
		ft_lock_mutex(philo->left_fork);
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
	ft_unlock_mutex(philo->left_fork);
	ft_unlock_mutex(philo->right_fork);
}

void	*ft_routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	philo->is_ready = true;
	while (ft_get_total_philo_ready_count(philo->ctx) != philo->ctx->nop)
		usleep(10);
	if (philo->id % 2)
		ft_sleep(philo->ctx->tte / 50, philo);
	while (!philo->ctx->stop && !philo->is_dead)
	{
		ft_eating(philo);
		ft_is_sleeping(philo);
		ft_sleep(philo->ctx->tts, philo);
		ft_is_thinking(philo);
	}
	philo->is_finished = true;
	return (NULL);
}
