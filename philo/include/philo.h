/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:05:37 by otodd             #+#    #+#             */
/*   Updated: 2024/04/23 18:04:55 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include "colour_codes.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdatomic.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>

struct	s_ctx;

typedef struct s_mutex
{
	pthread_mutex_t	mutex;
	atomic_bool		is_locked;
}	t_mutex;

typedef struct s_philo
{
	atomic_int		id;
	atomic_int		meals_eaten;
	atomic_ulong	last_ate;
	pthread_t		thread;
	struct s_ctx	*ctx;
	t_mutex			*left_fork;
	t_mutex			*right_fork;
	atomic_bool		is_ready;
	atomic_bool		is_finished;
	atomic_bool		is_dead;
}	t_philo;

typedef struct s_ctx
{
	atomic_bool		stop;
	t_philo			**philos;
	int				nop;
	int				ttd;
	int				tte;
	int				tts;
	int				notepme;
	t_mutex			*forks;
	t_mutex			*write_lock;
}	t_ctx;

// ft_utils.c

int				ft_atoi(const char *nptr);
int				ft_isdigit(int c);
int				ft_ischeck_str(char *str, int (*f)(int));

// logging.c

void			ft_taken_fork(t_philo *philo);
void			ft_is_eating(t_philo *philo);
void			ft_is_sleeping(t_philo *philo);
void			ft_is_thinking(t_philo *philo);
void			ft_has_died(t_philo *philo);

// manage.c

void			ft_init_philos(t_ctx *ctx);
void			ft_init_mutexes(t_ctx *ctx);
void			ft_exit(t_ctx *ctx);
void			ft_create_threads(t_ctx *ctx);
unsigned long	ft_get_current_time(void);

// run.c

void			ft_monitor(t_ctx *ctx);
void			*ft_routine(void *p);

// utils.c

int				ft_get_current_total_eaten_meals(t_ctx *ctx);
int				ft_get_total_philo_ready_count(t_ctx *ctx);
bool			ft_are_philos_finished(t_ctx *ctx);
void			ft_lock_mutex(t_mutex *mutex);
void			ft_unlock_mutex(t_mutex *mutex);

#endif