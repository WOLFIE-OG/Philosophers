/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:05:37 by otodd             #+#    #+#             */
/*   Updated: 2024/03/20 18:00:36 by otodd            ###   ########.fr       */
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
	DEAD = 0,
	EATING = 1,
	SLEEPING = 2,
	THINKING = 3
}	t_state;

typedef struct s_carbon
{
	int			id;
	int			meals_eaten;
	t_state		state;
	int			nop;
	int			ttd;
	int			tte;
	int			tts;
	int			notepme;
	pthread_t	*thread;
	void		*earth;
}	t_carbon;

typedef struct s_earth
{
	t_carbon		**souls;
	int				nop;
	int				ttd;
	int				tte;
	int				tts;
	int				notepme;
	int				counter;
	pthread_mutex_t	lock;
	pthread_mutex_t	**forks;
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