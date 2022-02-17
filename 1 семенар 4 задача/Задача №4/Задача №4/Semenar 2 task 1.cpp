#include <iostream>
#include <vector>

int main(){

	std::vector <int> a;

	/*
	for (int i = 0; i < 30; i++) {
		std::cout << a.size() << " " << a.capacity() << '\n';
		a.push_back(i);
	}
	*/

	//Note that every time the memory is filled, the memory 
	//allocated to the vector increases by the same number of times

	//Let's try to make our coefficient
	
	/*
	a.reserve(10);
	for (int i = 0; i < 30; i++) {
		std::cout << a.size() << " " << a.capacity() << '\n';
		a.push_back(i);
	}
	*/
	//We started multiplying the allocated memory at the beginning by the same factor.

	a.reserve(10000000000000000000);
	// You will get an error std::length_error
    //length_error: исключение, которое возникает при попытке создать объект большего размера, чем допустим для данного типа



	return 0;
}