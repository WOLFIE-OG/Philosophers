/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:05:37 by otodd             #+#    #+#             */
/*   Updated: 2024/04/22 18:07:11 by otodd            ###   ########.fr       */
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
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>

# define SEM_FORKS "/forks"
# define SEM_WRITE "/write"
# define SEM_DEAD "/dead"
# define SEM_EATEN "/eaten"

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

typedef struct s_carbon
{
	atomic_int		id;
	atomic_int		meals_eaten;
	atomic_ulong	last_ate;
	atomic_int		state;
	pid_t			pid;
	struct s_earth	*earth;
	atomic_bool		is_dead;
	pthread_t		bigbrother;
}	t_carbon;

typedef struct s_earth
{
	t_carbon	**souls;
	int			nop;
	int			ttd;
	int			tte;
	int			tts;
	int			notepme;
	sem_t		*forks;
	sem_t		*write_lock;
	sem_t		*death;
	sem_t		*eaten;
	pthread_t	eat_trigger;
	pthread_t	death_trigger;
	atomic_bool	has_died;
	atomic_bool	has_max_eat;
	atomic_bool	is_parent;
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
void			eating(t_carbon *carbon);
void			invite_philos(t_earth *earth);
void			hell(t_earth *earth);
void			*bigbrother(void *c);
#endif