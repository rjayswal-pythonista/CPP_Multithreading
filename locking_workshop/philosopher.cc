#include <iostream>
#include <thread>
#include <sstream>

#include "philosopher.h"

using namespace std;

mutex print_mutex;

void Philosopher::print(ostringstream& os) {
	lock_guard<mutex> print_lock(print_mutex);
	cout << os.str() << endl;
	os.str("");
}

Philosopher::Philosopher(string name, Fork *lfork, Fork *hfork) : name(name), lfork(lfork), hfork(hfork) {
	ostringstream os;
	os << "Philosopher " << name << " with left fork " << lfork->number << " and right fork number " << hfork->number;
	print(os);
}

void Philosopher::dine() { 
	for (int i = 0; i < 1; ++i) {
		ostringstream os;

		os << "Philosopher " << name << " reaches for fork " << lfork->number;
		print(os);
		
		if (lfork->m.try_lock_for(chrono::seconds(lfork->timeout))) {
			os << "Philosopher " << name << " picks up fork " << lfork->number;
			print(os);
			this_thread::sleep_for(chrono::seconds(thinktime));
			
			os << "Philosopher " << name << " reaches for fork " << hfork->number;
			print(os);
			
			if (hfork->m.try_lock_for(chrono::seconds(hfork->timeout))) {
				os << "Philosopher " << name << " picks up fork " << hfork->number;
				print(os);
				
				os << "Philosopher " << name << " eating";
				print(os);
				this_thread::sleep_for(chrono::seconds(eattime));
				hfork->m.unlock();
				
				os << "Philosopher " << name << " puts down fork " << hfork->number;
				print(os);
			}
			lfork->m.unlock();
			
			os << "Philosopher " << name << " puts down fork " << lfork->number;
			print(os);
		}
		
		os << "Philosopher " << name << " thinking";
		print(os);
		this_thread::sleep_for(chrono::seconds(thinktime));
	}
}