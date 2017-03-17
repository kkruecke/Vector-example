#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <memory>
using namespace std;

class Employee { 
    
  string fname;  
  string lname;
  int ssn;
  
public: 
    
  void* operator new(size_t sz)
  {
        cout << "Employee::new(size_t)  " << sz << " bytes\n";
        return ::operator new(sz);
  }
  
  void* operator new(size_t sz, void* where) throw() 
  { 
      cout << "Employee::new(size_t, void *)  " << sz << " bytes\n";
      return ::operator new(sz, where);; 
  }
  
  Employee() :  ssn{-1111111111} 
  { 
     cout << "\tEmployee() called " << endl;
  } 
  
  Employee(const string& fn, const string& ln, int nu) : fname{fn}, lname{ln}, ssn{nu}
  {
    cout << "\tEmployee(const string& fn, const string& ln, int nu) called " << endl;
  }
  
  Employee(Employee&& lhs) : fname{move(lhs.fname)}, lname{move(lhs.lname)}, ssn{lhs.ssn}
  {
    cout << "\tEmployee(Employee&& lhs) called " << endl;
  }
  
  Employee& operator=(const Employee& lhs) 
  {
      cout << "\tEmployee::operator=(const Employee& lhs) called " << endl;

      if (this != &lhs) {

          fname = lhs.fname;
          lname = lhs.lname;
    	  ssn = lhs.ssn;  
      }
         
      return *this;
   } T>
  
  Employee& operator=(Employee&& lhs)  
  {
    cout << "\tEmployee::operator=(Employee&& lhs) called " << endl;

    if (this != &lhs) {

        fname = move(lhs.fname);
        lname = move(lhs.lname);
         ssn = lhs.ssn;  
    }   

    return *this;
  }
};


void *p = new char[sizeof(T)];

template<class T, class Args...> void *do_emplace(void *p, Args&... args)
{
   new(p) T(std::forward<Args...>(args
}

new(p) T(std::forward<T>

int main(int argc, char *argv[])
{
   vector<Employee> vec;
   
   cout <<  R"(vec.push_back(Employee("John", "Smith", 999999999));)" << endl;
   
   vec.push_back(Employee("John", "Smith", 999999999));
   
   cout <<  R"(vec.emplace_back("John", "Doe", 1111111111);)" << endl;

   vec.emplace_back("John", "Doe", 1111111111);
    
   cout << "\n---------------" << endl;

   map<int, Employee> mp;
   
   cout << R"(mp.insert(make_pair(1, Employee("Jane", "Smith", 222222222)));)" << endl;

   mp.insert(make_pair(1, Employee("Jane", "Smith", 222222222)));
   
   cout << R"(mp.insert(make_pair(1, Employee("Jane", "Smith", 222222222)));)" << endl;
   
   mp.insert(pair<int, Employee>(2, Employee{"Jane", "Smith", 222222222}));

   auto iter = mp.begin();
   
   // should be easier for the optimizer
   //mp.emplace(4, "Laura", "Jones", 3333333333);
   
   cout << R"(mp.emplace_hint(iter, pair<int, Employee>(12, Employee("Jane", "Doe", 44444444)));)" << endl;

   mp.emplace_hint(iter, pair<int, Employee>(12, Employee("Jane", "Doe", 44444444)));
   
   return 0;
}
