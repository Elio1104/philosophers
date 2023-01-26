#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>

//ALL_ATE
# define NO = 0
# define YES = 1
//ERROR
# define GOOD = 0
# define ERROR = 1
# define ERROR_MUTEX = 2
//STATUS
# define ALIVE = 1
# define DEAD = 0

struct  s_rules;

typedef struct  s_philo
{
    int             id;
    int             nb_meal;
    int             right_fork;
    int             left_fork;
    long long       last_meal;
    pthread_t       thread_id;
    struct s_rules  *rules;
}t_philo;

typedef struct  s_rules
{
    int                 nb_philo;
    int                 time_death;
    int                 time_eat;
    int                 time_sleep;
    int                 nb_eat;
    int                 status;
    int                 all_ate;
    long long           t0;
    pthread_mutex_t     forks[250];
    pthread_mutex_t     writing;
    pthread_mutex_t     eating;
    t_philo             philo[250];
}t_rules;

#endif