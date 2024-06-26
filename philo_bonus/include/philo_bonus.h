/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:05:37 by otodd             #+#    #+#             */
/*   Updated: 2024/05/13 16:04:55 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include "colour_codes.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdatomic.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/time.h>
# include <sys/wait.h>

# define SEM_FORKS "/forks"
# define SEM_WRITE "/write"
# define SEM_STOP "/stop"

struct	s_ctx;

typedef struct s_philo
{
	int				id;
	atomic_int		meals_eaten;
	atomic_bool		max_ate;
	atomic_long		last_ate;
	pid_t			pid;
	struct s_ctx	*ctx;
	pthread_t		monitor_thread;
}	t_philo;

typedef struct s_ctx
{
	t_philo		*philos;
	int			nop;
	int			ttd;
	int			tte;
	int			tts;
	int			notepme;
	sem_t		*forks;
	sem_t		*write_lock;
	sem_t		*stop;
	long		start_time;
	pthread_t	death_trigger;
}	t_ctx;

// ft_utils.c

int		ft_atoi(const char *nptr);
int		ft_isdigit(int c);
int		ft_ischeck_str(char *str, int (*f)(int));

// init.c

void	ft_wait_process(t_ctx *ctx);
void	ft_close_semaphores(t_ctx *ctx);

// logging.c

void	ft_taken_fork(t_philo *philo);
void	ft_is_eating(t_philo *philo);
void	ft_is_sleeping(t_philo *philo);
void	ft_is_thinking(t_philo *philo);
void	ft_has_died(t_philo *philo);

// manage.c

void	ft_init_philos(t_ctx *ctx);
void	ft_init_semaphores(t_ctx *ctx);
void	ft_exit(t_ctx *ctx);
void	ft_launch(t_ctx *ctx);
long	ft_get_current_time(void);

// run.c

void	ft_routine(t_philo *philo);

#endif