/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:05:37 by otodd             #+#    #+#             */
/*   Updated: 2024/03/21 19:01:43 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include "colour_codes.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>

typedef enum e_state
{
	NONE = 0,
	DEAD = 1,
	GOT_FIRST_FORK = 2,
	GOT_SECOND_FORK = 3,
	EATING = 4,
	SLEEPING = 5,
	THINKING = 6
}	t_state;

typedef struct s_carbon
{
	int				id;
	int				meals_eaten;
	unsigned long	last_ate;
	t_state			state;
	pthread_t		thread;
	void			*earth;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	soul_lock;
}	t_carbon;

typedef struct s_earth
{
	bool			done;
	t_carbon		*souls;
	int				nop;
	int				ttd;
	int				tte;
	int				tts;
	int				notepme;
	int				counter;
	unsigned long	big_bang;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	done_lock;
	pthread_mutex_t	eat_lock;
}	t_earth;

unsigned long	get_current_time(void);
void			l_taken_fork(t_carbon *c);
void			l_is_eating(t_carbon *c);
void			l_is_sleeping(t_carbon *c);
void			l_is_thinking(t_carbon *c);
void			l_has_died(t_carbon *c);
int				ft_atoi(const char *nptr);
#endif