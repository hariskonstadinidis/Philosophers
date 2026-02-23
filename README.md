# philosophers

42 dining philosophers problem implementation in C using threads and mutexes.

## about

each philosopher sits at a round table, thinks, eats, and sleeps. they need two forks to eat and share forks with their neighbors. if a philosopher doesn't eat in time, they die.

## usage

make
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]

### example

./philo 5 800 200 200
./philo 4 410 200 200 10

## rules

- philosophers alternate between eating, sleeping, and thinking
- a philosopher needs both left and right forks to eat
- simulation stops when a philosopher dies or all philosophers have eaten enough times (if specified)

## build

make        # compile
make clean  # remove object files
make fclean # remove everything
make re     # recompile
