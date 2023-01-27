#include "../includes/philo.h"

int main(int argc, char **argv)
{
	int error;
    t_rules rules;

    if (argc != 5 && argc != 6)
        return (error_manager(ERROR));
    error = init_all(&rules, argv);
	if (error != GOOD)
        return (error_manager(error));
    if (ft_philo(&rules))
        return (write_error("PHILO ERROR"));
    return (0);
}
