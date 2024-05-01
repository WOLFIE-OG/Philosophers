/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 18:13:55 by otodd             #+#    #+#             */
/*   Updated: 2024/05/01 13:37:03 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static void	ft_sleep(long time)
{
	long	then;

	then = ft_get_current_time();
	while ((ft_get_current_time() - then) < time)
		usleep(100);
}

static void	*ft_monitor(void	*p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while (true)
	{
		if (philo->meals_eaten >= philo->ctx->notepme
			&& philo->ctx->notepme > 0)
		{
			philo->max_ate = true;
			break ;
		}
		if (((ft_get_current_time() - philo->ctx->start_time)
				- philo->last_ate) > philo->ctx->ttd)
		{
			ft_has_died(philo);
			sem_post(philo->ctx->stop);
			break ;
		}
		usleep(100);
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
	philo->last_ate = ft_get_current_time() - philo->ctx->start_time;
	ft_sleep(philo->ctx->tte);
	if (philo->meals_eaten < philo->ctx->notepme
		&& philo->ctx->notepme > 0)
		philo->meals_eaten++;
	sem_post(philo->ctx->forks);
	sem_post(philo->ctx->forks);
}

void	ft_routine(t_philo *philo)
{
	pthread_create(&philo->monitor_thread, NULL, ft_monitor, philo);
	pthread_detach(philo->monitor_thread);
	if (philo->id % 2)
		ft_sleep(100);
	while (true)
	{
		if (philo->max_ate)
			break ;
		ft_eating(philo);
		ft_is_sleeping(philo);
		ft_sleep(philo->ctx->tts);
		ft_is_thinking(philo);
		usleep(100);
	}
	ft_close_semaphores(philo->ctx);
	free(philo->ctx->philos);
	exit(EXIT_SUCCESS);
}
