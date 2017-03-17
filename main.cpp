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

class Employee {

     std::string name;
     int age;
     int salary;
  public:

     Employee() {}
     Employee(const std::string& _name, int _age, int _salary) :\
             name{_name}, age{_age}, salary{_salary} {}
     
     Employee(Employee&& e) : name{std::move(e.name)}, age{e.age}, salary{e.salary} {}

     Employee& operator=(const Employee& lhs)
     {
       if (this != &lhs) {
          name = lhs.name;
          age = lhs.age;
          salary = lhs.salary;
       }
       return *this;
     }

     Employee& operator=(Employee&& lhs)
     {
       if (this != &lhs) {
          name = std::move(lhs.name);
          age = lhs.age;
          salary = lhs.salary;
       }
       return *this;
     }
}; 

using namespace std;

int main(int argc, char *argv[])
{
   Y y;

   zigzag(y);
   zigzag(Y{}); 

   string lvaluestr{"lvaluestr"};

   shared_ptr<A> ptr1 { factory<A>(lvaluestr) };

   shared_ptr<A> ptr2 { factory<A>(string{"rvaluestr"}) };
   
   Vector<Employee> v1;

   for (auto i = 0; i < 5; ++i) {
       
       v1.push_back(Employee{});
   }

   v1.push_back(Employee{"John Smith", 25, 100000});

   v1.emplace_back("John Smith", 25, 100000);

    
   return 0;

}
