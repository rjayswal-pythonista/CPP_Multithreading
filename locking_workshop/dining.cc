#include <iostream>
#include <thread>
#include <vector>

#include "philosopher.h"
#include "fork.h"

int main() {
	const int nForks{5};
	const int nPhils{nForks};

	std::vector<Fork *> forks;
	for (int i = 0; i < nForks; ++i) {
		forks.push_back(new Fork(i+1));
	}

	std::vector<Philosopher *> phils;
	phils.push_back(new Philosopher("A", forks[0], forks[1]));
	phils.push_back(new Philosopher("B", forks[1], forks[2]));
	phils.push_back(new Philosopher("C", forks[2], forks[3]));
	phils.push_back(new Philosopher("D", forks[3], forks[4]));
	// Livelock - no philosopher can lock both forks
	// phils.push_back(new Philosopher("E", forks[4], forks[0]));
	// Impose ordering - philosopher must lock lower numbered fork before higher numbered
	phils.push_back(new Philosopher("E", forks[0], forks[4]));

	std::vector<std::thread> tasks;
		
	for (auto phil : phils) {
		tasks.push_back(std::move(std::thread(&Philosopher::dine, phil)));
	}
	for (auto& task : tasks) {
		task.join();
	}
	
}