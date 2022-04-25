#ifndef FORK_H
#define FORK_H

#include <mutex>

struct Fork {
	int number{0};
	int timeout{2};
	std::timed_mutex m;
	Fork(int number) : number(number) {}
};

#endif //FORK_H