#include <iostream>
#include <string>
#include <memory>
#include <utility>
#include "include/vector.h"

using namespace std;

class A { // trivial example class
   std::string str;
  public:
    A(std::string& lhs) : str(lhs)
    {
      cout << " A::A(std::string& lhs) invoked." << endl;
    }

    A(std::string&& lhs) 
    {
      cout << " A::A(std::string&& lhs) invoked." << endl;
    }
};

template<class T> struct template_parameter_type {
  static void describe()
  {
    std::cout <<  "In non-specialized struct template_parameter_type<T>" << endl; 
  }
};

template<class T> struct template_parameter_type<T&> {
  static void describe()
  {
   std::cout <<  "In partial template specialization struct template_parameter_type<T&>"  << std::endl; 
  }
};

template<class T> struct template_parameter_type<T&&> {
  static void describe()
  {
   std::cout <<  "In partial template specialization struct template_parameter_type<T&&>"  << std::endl; 
  }
};

template<class T> void zigzag(T&& arg)
{
   template_parameter_type<T>::describe();
}

template<class T, class ARG> std::shared_ptr<T> factory(ARG&& arg)
{
   template_parameter_type<ARG>::describe();

   // Line below fails to invoke A(string&&) because arg is an lvalue. 
   // T( static_cast<ARG&&>(arg) ) should be used.
   return std::shared_ptr<T>{new T(arg)};  
}

struct Y {};

using namespace std;

int main(int argc, char *argv[])
{
   Y y;

   zigzag(y);
   zigzag(Y{}); 

   string lvaluestr{"lvaluestr"};

   shared_ptr<A> ptr1 { factory<A>(lvaluestr) };

   shared_ptr<A> ptr2 { factory<A>(string{"rvaluestr"}) };
   
   Vector<int> v1;
   Vector<int> v2;
   
   for (auto i = 0; i < 10; ++i) {
       
       v1.push_back(i);
   }
   
 
   return 0;

}
