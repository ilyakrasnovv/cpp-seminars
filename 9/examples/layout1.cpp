#include <iostream>


struct Granny {
   int g;
};

struct Dad : virtual Granny {
   int d;
};

struct Mom : virtual Granny {
   int m;
};

struct Son : Dad, Mom {
   int s;
};


// Only for exposition
template <class T>
void* getVirtualPointer(T& object) {
   return *reinterpret_cast<void**>(&object);
}

int main() {
   using ssize_t = signed long long int;

   {
      Granny granny;
      std::cout << "Granny ptr: " << &granny << std::endl;
      std::cout << "Granny's fields shift: " << (ssize_t)&granny.g - (ssize_t)&granny << std::endl;
   }
   std::cout << std::endl;
   {
      Dad dad;
      std::cout << "Dad ptr: " << &dad << std::endl;
      std::cout << "Dad's vptr: " << getVirtualPointer(dad) << std::endl;
      std::cout << "Dad's fields shift: " << (ssize_t)&dad.d - (ssize_t)&dad << std::endl;
      std::cout << "Dad's granny shift: " << (ssize_t)&static_cast<Granny&>(dad) - (ssize_t)&dad << std::endl;
      std::cout << "Dad's granny fields shift: " << (ssize_t)&static_cast<Granny&>(dad).g - (ssize_t)&dad << std::endl;
   }
   std::cout << std::endl;
   {
      Mom mom;
      std::cout << "Mom ptr: " << &mom << std::endl;
      std::cout << "Mom's vptr: " << getVirtualPointer(mom) << std::endl;
      std::cout << "Mom's fields shift: " << (ssize_t)&mom.m - (ssize_t)&mom << std::endl;
      std::cout << "Mom's granny shift: " << (ssize_t)&static_cast<Granny&>(mom) - (ssize_t)&mom << std::endl;
      std::cout << "Mom's granny fields shift: " << (ssize_t)&static_cast<Granny&>(mom).g - (ssize_t)&mom << std::endl;
   }
   std::cout << std::endl;
   {
      Son son;
      Dad& son_dad = son;
      Mom& son_mom = son;
      Granny& son_granny = son;

      std::cout << "Son ptr: " << &son << std::endl;
      std::cout << "Son's vptr: " << getVirtualPointer(son) << std::endl;
      std::cout << "Son's fields shift: " << (ssize_t)&son.s - (ssize_t)&son << std::endl;
      std::cout << "Son's dad shift: " << (ssize_t)&son_dad - (ssize_t)&son << std::endl;
      std::cout << "Son's dad vptr: " << getVirtualPointer(son_dad) << std::endl;
      std::cout << "Son's dad fields shift: " << (ssize_t)&son_dad.d - (ssize_t)&son << std::endl;
      std::cout << "Son's mom shift: " << (ssize_t)&son_mom - (ssize_t)&son << std::endl;
      std::cout << "Son's mom vptr: " << getVirtualPointer(son_mom) << std::endl;
      std::cout << "Son's mom fields shift: " << (ssize_t)&son_mom.m - (ssize_t)&son << std::endl;
      std::cout << "Son's granny shift: " << (ssize_t)&son_granny - (ssize_t)&son << std::endl;
      std::cout << "Son's granny fields shift: " << (ssize_t)&son_granny.g - (ssize_t)&son << std::endl;
   }
}