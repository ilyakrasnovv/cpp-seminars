#include <iostream>


struct A {
   int a;
};

struct O {
   int o;
};

struct B : virtual O {
   int b;
};

struct C : A, B {
   int c;
};

// Only for exposition
template <class T>
void* getVirtualPointer(T& object) {
   return *reinterpret_cast<void**>(&object);
}

int main() {
   using ssize_t = signed long long int;

   {
      C c;
      A& c_a = c;
      B& c_b = c;
      O& c_o = c;

      std::cout << "C's ptr: " << &c << std::endl;
      std::cout << "C's vptr: " << getVirtualPointer(c) << std::endl;
      std::cout << "C's fields shift: " << (ssize_t)&c.c - (ssize_t)&c << std::endl;
      std::cout << "A's ptr: " << &c_a << std::endl;
      std::cout << "A's fields shift: " << (ssize_t)&c_a.a - (ssize_t)&c << std::endl;
      std::cout << "O's ptr: " << &c_o << std::endl;
      std::cout << "O's fields shift: " << (ssize_t)&c_o.o - (ssize_t)&c << std::endl;
      std::cout << "B's ptr: " << &c_b << std::endl;
      std::cout << "B's vptr: " << getVirtualPointer(c) << std::endl;
      std::cout << "B's fields shift: " << (ssize_t)&c_b.b - (ssize_t)&c << std::endl;
   }
}
