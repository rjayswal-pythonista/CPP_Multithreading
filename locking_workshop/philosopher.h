#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include "fork.h"

#include <sstream>

enum class philo_state { thinking, eating };

class Philosopher {
	std::string name;
	const int thinktime{1};
	const int eattime{1};
	Fork *lfork;            // Lower numbered fork
	Fork *hfork;            // Higher numbered fork
	philo_state state;
  public:
	Philosopher(std::string name, Fork *lfork, Fork *rfork);
	void dine();
	void print(std::ostringstream& os);
};

#endif //PHILOSOPHER_H

