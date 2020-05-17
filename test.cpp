#include <iostream>
#include <map>
#include <unordered_map>
#include <string>
#include <memory>
#include <typeinfo>

using namespace std;


class Object {
	public:
		int x;
		int y;
};

unordered_map<char, Object (*)()> Fns;
class God {
	public:
		virtual void method() = 0;
};

class Derived1 : public God {
	public:
		void method() override;
};

class Derived2 : public God {
	public:
		void method() override;
};

Object swag() {
	cout << "SUP JOE";
}

void Derived1::method() {
	cout << "in Derived1";
}

void Derived2::method() {
	cout << "in Derived2";
}

int main() {
	Fns[0] = swag;

	auto d1 = Derived1();
	auto d2 = Derived2();

	Fns[0]();

}
