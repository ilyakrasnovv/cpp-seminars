#include <iostream>


struct VBase {
   VBase() {
      std::cout << "Called VBase()" << std::endl;
   }

   VBase(int) {
      std::cout << "Called VBase(int)" << std::endl;
   }
};

struct Base1 : virtual VBase {
   Base1() : VBase(1) {
      std::cout << "Called Base1()" << std::endl;
   }
};

struct Base2 : virtual VBase {
   Base2() : VBase(2) {
      std::cout << "Called Base2()" << std::endl;
   }
};

struct Derived : Base1, Base2 {
   Derived() {
      std::cout << "Called Derived()" << std::endl;
   }
};

int main() {
   Derived d;
}
