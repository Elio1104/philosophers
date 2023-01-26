#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

struct  s_rules;

typedef struct  s_philo
{
    int             id;
    int             nb_ate;
    int             right_fork;
    int             left_fork;
    long long       last_meal;
    //struct s_rules  *rules;
}t_philo;


typedef struct  s_rules
{
    int                 nb_philo;
    int                 time_death;
    int                 time_eat;
    int                 time_sleep;
    int                 nb_eat;
    long long           t0;
    pthread_mutex_t     forks[250];
    t_philo             philo[250];
}t_rules;

#endif