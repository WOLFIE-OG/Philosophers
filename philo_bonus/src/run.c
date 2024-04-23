/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 18:13:55 by otodd             #+#    #+#             */
/*   Updated: 2024/04/23 17:27:50 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	ft_sleep(unsigned long time, t_philo *philo)
{
	unsigned long	then;

	then = ft_get_current_time();
	while (true)
	{
		if ((ft_get_current_time() - then) >= time)
			break ;
		usleep(philo->ctx->nop * 2);
	}
}

static void	*ft_monitor(void	*p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while (true)
	{
		if ((int)(ft_get_current_time() - philo->last_ate) > philo->ctx->ttd)
		{
			ft_has_died(philo);
			sem_post(philo->ctx->death);
			break ;
		}
		if (philo->meals_eaten >= philo->ctx->notepme)
		{
			sem_post(philo->ctx->death);
			break ;
		}
	}
	return (NULL);
}

static void	ft_forks(t_philo *philo)
{
	sem_wait(philo->ctx->forks);
	ft_taken_fork(philo);
	sem_wait(philo->ctx->forks);
	ft_taken_fork(philo);
}

static void	ft_eating(t_philo *philo)
{
	ft_forks(philo);
	ft_is_eating(philo);
	philo->last_ate = ft_get_current_time();
	if (philo->ctx->notepme != -1)
		philo->meals_eaten++;
	ft_sleep(philo->ctx->tte, philo);
	sem_post(philo->ctx->forks);
	sem_post(philo->ctx->forks);
}

void	ft_routine(t_philo *philo)
{
	if (philo->id % 2)
		ft_sleep(philo->ctx->tte / 50, philo);
	philo->last_ate = ft_get_current_time();
	pthread_create(&philo->monitor_thread, NULL, ft_monitor, philo);
	pthread_detach(philo->monitor_thread);
	while (true)
	{
		ft_eating(philo);
		ft_is_sleeping(philo);
		ft_sleep(philo->ctx->tts, philo);
		ft_is_thinking(philo);
	}
}
