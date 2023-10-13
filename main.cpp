#include <iostream>
#include <string>
#include <Windows.h>

template <typename T> concept ComplexConcept = requires(T value)
{
	{value.toString() } -> std::same_as<std::string>;
	{value.hash()} -> std::convertible_to<long>;
		requires !std::has_virtual_destructor<T>::value;
};

class MyComplexType {
private:
	short _num = 0;
public:
	MyComplexType(short n) : _num(n) {};
	~MyComplexType() {};

	std::string toString() const { return std::to_string(_num); }

	long hash() const { return (long)_num; }
};

class MyVirtualComplexType {
private:
	short _num = 0;
public:
	MyVirtualComplexType(short n) : _num(n) {};
	virtual ~MyVirtualComplexType() {};

	std::string toString() const { return std::to_string(_num); }

	long hash() const { return (long)_num; }
};

int main() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");

	std::cout << ">>Проверяем, соответствует ли концепту MyComplexType...\n" << std::endl;
	MyComplexType t1(17);
	if constexpr (ComplexConcept<decltype(t1)>) {
		std::cout << "MyComplexType соответствует концепту ComplexConcept\n" << std::endl;
	}
	else {
		std::cout << "MyComplexType не соответствует концепту ComplexConcept\n" << std::endl;
	}

	std::cout << "\n\n>>Проверяем, соответствует ли концепту MyVirtualComplexType...\n" << std::endl;
	MyVirtualComplexType t2(17);
	if constexpr (ComplexConcept<decltype(t2)>) {
		std::cout << "MyVirtualComplexType соответствует концепту ComplexConcept\n" << std::endl;
	}
	else {
		std::cout << "MyVirtualComplexType не соответствует концепту ComplexConcept\n" << std::endl;
	}

	return 0;
}