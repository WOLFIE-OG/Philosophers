/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:05:37 by otodd             #+#    #+#             */
/*   Updated: 2024/04/18 17:10:39 by otodd            ###   ########.fr       */
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

enum e_state
{
	NONE = 0,
	DEAD = 1,
	GOT_FIRST_FORK = 2,
	GOT_SECOND_FORK = 3,
	EATING = 4,
	SLEEPING = 5,
	THINKING = 6
};

struct	s_earth;

typedef struct s_mutex
{
	pthread_mutex_t	mutex;
	atomic_bool		is_locked;
}	t_mutex;

typedef struct s_carbon
{
	atomic_int		id;
	atomic_int		meals_eaten;
	atomic_ulong	last_ate;
	atomic_int		state;
	pthread_t		thread;
	struct s_earth	*earth;
	t_mutex			*left_fork;
	t_mutex			*right_fork;
	atomic_bool		is_ready;
	atomic_bool		is_finished;
	atomic_bool		is_dead;
}	t_carbon;

typedef struct s_earth
{
	atomic_bool		solar_flare;
	t_carbon		**souls;
	int				nop;
	int				ttd;
	int				tte;
	int				tts;
	int				notepme;
	t_mutex			*forks;
	t_mutex			*write_lock;
}	t_earth;

unsigned long	get_current_time(void);
void			l_taken_fork(t_carbon *c);
void			l_is_eating(t_carbon *c);
void			l_is_sleeping(t_carbon *c);
void			l_is_thinking(t_carbon *c);
void			l_has_died(t_carbon *c);
int				ft_atoi(const char *nptr);
int				ft_isdigit(int c);
int				ft_ischeck_str(char *str, int (*f)(int));
void			slumber(unsigned long time, t_carbon *carbon);
void			*life(void *i);
int				get_current_total_eaten_meals(t_earth *earth);
int				get_total_soul_ready_count(t_earth *earth);
void			eating(t_carbon *carbon);
void			invite_philos(t_earth *earth);
bool			set_table(t_earth *earth);
bool			create_locks(t_earth *earth);
void			start_life(t_earth *earth);
void			hell(t_earth *earth);
void			bigbrother(t_earth *earth);
bool			are_souls_finished(t_earth *earth);
void			lock_mutex(t_mutex *mutex);
void			unlock_mutex(t_mutex *mutex);
#endif