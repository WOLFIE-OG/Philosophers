/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:05:37 by otodd             #+#    #+#             */
/*   Updated: 2024/03/25 19:24:19 by otodd            ###   ########.fr       */
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

typedef struct s_carbon
{
	int				id;
	atomic_int		meals_eaten;
	atomic_ulong	last_ate;
	atomic_int		state;
	pthread_t		thread;
	void			*earth;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	soul_lock;
}	t_carbon;

typedef struct s_earth
{
	int				max_meals;
	atomic_bool		solar_flare;
	t_carbon		souls[250];
	int				nop;
	int				ttd;
	int				tte;
	int				tts;
	int				notepme;
	pthread_mutex_t	forks[250];
	pthread_mutex_t	write_lock;
}	t_earth;

unsigned long	get_current_time(void);
void			l_taken_fork(t_carbon *c);
void			l_is_eating(t_carbon *c);
void			l_is_sleeping(t_carbon *c);
void			l_is_thinking(t_carbon *c);
void			l_has_died(t_carbon *c);
int				ft_atoi(const char *nptr);
#endif