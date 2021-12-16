/*#include <memory>
#include <iostream>
using namespace std;
void computes(shared_ptr<int> p) {}

int main() {
	shared_ptr<int> ptru(new int);
	computes(ptru);
	return 0;
}*/

#include <iostream>
#include <string>
#include <thread>
void foo() {

	std::cout << "345\n\n";

}



int main() {

	std::thread t(foo);

	foo();

	t.join();

}