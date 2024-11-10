#include <iostream>
#include <cstdint>


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
   int sn;
};

struct Daughter : Mom, Dad {  // Attention!
   int dr;
};

struct Grandson : Son, Daughter {
   int gs;
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
      Granny& dad_granny = dad;

      std::cout << "Dad ptr: " << &dad << std::endl;
      std::cout << "Dad's vptr: " << getVirtualPointer(dad) << std::endl;
      std::cout << "Dad's fields shift: " << (ssize_t)&dad.d - (ssize_t)&dad << std::endl;
      std::cout << "Dad's granny shift: " << (ssize_t)&dad_granny - (ssize_t)&dad << std::endl;
      std::cout << "Dad's granny fields shift: " << (ssize_t)&dad_granny.g - (ssize_t)&dad << std::endl;
   }
   std::cout << std::endl;
   {
      Mom mom;
      Granny& mom_granny = mom;

      std::cout << "Mom ptr: " << &mom << std::endl;
      std::cout << "Mom's vptr: " << getVirtualPointer(mom) << std::endl;
      std::cout << "Mom's fields shift: " << (ssize_t)&mom.m - (ssize_t)&mom << std::endl;
      std::cout << "Mom's granny shift: " << (ssize_t)&mom_granny - (ssize_t)&mom << std::endl;
      std::cout << "Mom's granny fields shift: " << (ssize_t)&mom_granny.g - (ssize_t)&mom << std::endl;
   }
   std::cout << std::endl;
   {
      Son son;
      Dad& son_dad = son;
      Mom& son_mom = son;
      Granny& son_granny = son;

      std::cout << "Son ptr: " << &son << std::endl;
      std::cout << "Son's vptr: " << getVirtualPointer(son) << std::endl;
      std::cout << "Son's fields shift: " << (ssize_t)&son.sn - (ssize_t)&son << std::endl; 

      std::cout << "Son's dad shift: " << (ssize_t)&static_cast<Dad&>(son) - (ssize_t)&son << std::endl;
      std::cout << "Son's dad vptr: " << getVirtualPointer(son_dad) << std::endl;
      std::cout << "Son's dad fields shift: " << (ssize_t)&static_cast<Dad&>(son).d - (ssize_t)&son << std::endl;

      std::cout << "Son's mom shift: " << (ssize_t)&static_cast<Mom&>(son) - (ssize_t)&son << std::endl;
      std::cout << "Son's mom vptr: " << getVirtualPointer(son_mom) << std::endl;
      std::cout << "Son's mom fields shift: " << (ssize_t)&static_cast<Mom&>(son).m - (ssize_t)&son << std::endl;

      std::cout << "Son's granny shift: " << (ssize_t)&static_cast<Granny&>(son) - (ssize_t)&son << std::endl;
      std::cout << "Son's granny fields shift: " << (ssize_t)&static_cast<Granny&>(son).g - (ssize_t)&son << std::endl;
   } 
   std::cout << std::endl;
   {
      Daughter daughter;
      Dad& daughter_dad = daughter;
      Mom& daughter_mom = daughter;
      Granny& daughter_granny = daughter;

      std::cout << "Daughter ptr: " << &daughter << std::endl;
      std::cout << "Daughter's vptr: " << getVirtualPointer(daughter) << std::endl;
      std::cout << "Daughter's fields shift: " << (ssize_t)&daughter.dr - (ssize_t)&daughter << std::endl;

      std::cout << "Daughter's dad shift: " << (ssize_t)&daughter_dad - (ssize_t)&daughter << std::endl;
      std::cout << "Daughter's dad vptr: " << getVirtualPointer(daughter_dad) << std::endl;
      std::cout << "Daughter's dad fields shift: " << (ssize_t)&daughter_dad.d - (ssize_t)&daughter << std::endl;

      std::cout << "Daughter's mom shift: " << (ssize_t)&daughter_mom - (ssize_t)&daughter << std::endl;
      std::cout << "Daughter's mom vptr: " << getVirtualPointer(daughter_mom) << std::endl;
      std::cout << "Daughter's mom fields shift: " << (ssize_t)&daughter_mom.m - (ssize_t)&daughter << std::endl;

      std::cout << "Daughter's granny shift: " << (ssize_t)&daughter_granny - (ssize_t)&daughter << std::endl;
      std::cout << "Daughter's granny fields shift: " << (ssize_t)&daughter_granny.g - (ssize_t)&daughter << std::endl;std::cout << "Daughter's mom fields shift: " << (ssize_t)&static_cast<Mom&>(daughter).m - (ssize_t)&daughter << std::endl;
   } 
   std::cout << std::endl;
   {
      Grandson grandson;
      Son& grandson_son = grandson;
      Daughter& grandson_daughter = grandson;

      std::cout << "Grandson ptr: " << &grandson << std::endl;
      std::cout << "Grandson's vptr: " << getVirtualPointer(grandson) << std::endl;
      std::cout << "Grandson's fields shift: " << (ssize_t)&grandson.gs - (ssize_t)&grandson << std::endl;

      std::cout << "Grandson's son shift: " << (ssize_t)&grandson_son - (ssize_t)&grandson << std::endl;
      std::cout << "Grandson's son vptr: " << getVirtualPointer(grandson_son) << std::endl;
      std::cout << "Grandson's son fields shift: " << (ssize_t)&grandson_son.sn - (ssize_t)&grandson << std::endl;

      std::cout << "Grandson's son dad shift: " << (ssize_t)&static_cast<Dad&>(grandson_son) - (ssize_t)&grandson << std::endl;
      std::cout << "Grandson's son dad vptr: " << getVirtualPointer(static_cast<Dad&>(grandson_son)) << std::endl;
      std::cout << "Grandson's son dad fields shift: " << (ssize_t)&static_cast<Dad&>(grandson_son).d - (ssize_t)&grandson << std::endl;

      std::cout << "Grandson's son mom shift: " << (ssize_t)&static_cast<Mom&>(grandson_son) - (ssize_t)&grandson << std::endl;
      std::cout << "Grandson's son mom vptr: " << getVirtualPointer(static_cast<Mom&>(grandson_son)) << std::endl;
      std::cout << "Grandson's son mom fields shift: " << (ssize_t)&static_cast<Mom&>(grandson_son).m - (ssize_t)&grandson << std::endl;

      std::cout << "Grandson's daughter shift: " << (ssize_t)&grandson_daughter - (ssize_t)&grandson << std::endl;
      std::cout << "Grandson's daughter vptr: " << getVirtualPointer(grandson_daughter) << std::endl;
      std::cout << "Grandson's daughter fields shift: " << (ssize_t)&grandson_daughter.dr - (ssize_t)&grandson << std::endl;

      std::cout << "Grandson's daughter dad shift: " << (ssize_t)&static_cast<Dad&>(grandson_daughter) - (ssize_t)&grandson << std::endl;
      std::cout << "Grandson's daughter dad vptr: " << getVirtualPointer(static_cast<Dad&>(grandson_daughter)) << std::endl;
      std::cout << "Grandson's daughter dad fields shift: " << (ssize_t)&static_cast<Dad&>(grandson_daughter).d - (ssize_t)&grandson << std::endl;

      std::cout << "Grandson's daughter mom shift: " << (ssize_t)&static_cast<Mom&>(grandson_daughter) - (ssize_t)&grandson << std::endl;
      std::cout << "Grandson's daughter mom vptr: " << getVirtualPointer(static_cast<Mom&>(grandson_daughter)) << std::endl;
      std::cout << "Grandson's daughter mom fields shift: " << (ssize_t)&static_cast<Mom&>(grandson_daughter).m - (ssize_t)&grandson << std::endl;

      std::cout << "Grandson's granny shift: " << (ssize_t)&static_cast<Granny&>(grandson) - (ssize_t)&grandson << std::endl;
      std::cout << "Grandson's granny fields shift: " << (ssize_t)&static_cast<Granny&>(grandson).g - (ssize_t)&grandson << std::endl;
   } 
}
