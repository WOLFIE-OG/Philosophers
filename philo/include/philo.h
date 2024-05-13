/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:05:37 by otodd             #+#    #+#             */
/*   Updated: 2024/05/13 15:56:04 by otodd            ###   ########.fr       */
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

typedef struct s_philo
{
	int				id;
	atomic_int		meals_eaten;
	atomic_long		last_ate;
	pthread_t		thread;
	struct s_ctx	*ctx;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	atomic_bool		is_full;
}	t_philo;

typedef struct s_ctx
{
	atomic_bool		stop;
	t_philo			*philos;
	int				nop;
	int				ttd;
	int				tte;
	int				tts;
	int				notepme;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
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

// run.c

void			ft_monitor(t_ctx *ctx);
void			*ft_routine(void *p);

// utils.c

bool			ft_are_philos_full(t_ctx *ctx);
long			ft_get_current_time(void);
void			ft_sleep(long time);

#endif