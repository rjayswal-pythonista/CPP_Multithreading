#include <iostream>
#include <string>
#include <vector>

using namespace std;

void func(int&& x) {
	cout << "Rvalue reference" << endl;
}

int main() {
	int y{2};
	
	func(std::move(y));
	func(2);
}