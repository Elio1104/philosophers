#include "../includes/philo.h"

int main(int argc, char **argv)
{
    t_rules rules;

    if (argc != 5 && argc != 6)
        error();//changer
    if (init_all(&rules, argv))
        error();//changer
    if (ft_philo())
        error();//changer
    return (0);
}