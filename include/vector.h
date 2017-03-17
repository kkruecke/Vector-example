#ifndef  Vector_h
#define  Vector_h

#include <memory>
#include <utility>
#include <algorithm>
#include <stdexcept>

template<class T> 
class Vector {

   std::unique_ptr<T[]> p;

   int size;

   int next_index;

   void grow(); 
   void free();

   static const int growth_factor = 2;
   static const int default_sz = 2;

   public:
    Vector()
    {
      p.reset( new T[Vector::default_sz] );  
      next_index = 0;
    }

    Vector(const Vector& lhs);

    void push_back(const T& t);

    void push_back(T&& t);

    template<class... ARGS> void emplace_back(ARGS&& ... args);

    T& operator[](int);

    const T& operator[](int) const;

    Vector& operator=(const Vector& lhs);

    Vector& operator=(Vector&& lhs);

    void* operator new (std::size_t size, void* ptr) noexcept;
};

template<class T> void Vector<T>::grow()
{
  auto new_size = size * Vector<T>::growth_factor; 

  //--T *pp = reinterpret_cast<T*>( new char[new_size * sizeof(T) ] ); 
  T *pp = reinterpret_cast<T[]>( new char[new_size * sizeof(T) ] ); 
  
  std::unique_ptr<T[]> ptr { pp }; 

  //--T *dest = ptr.get();
  
  for (auto i = 0; i < size; ++i) {
      
      ptr[i] = std::move(p[i]); 
  }
  
  size = new_size;
  
  p.reset(ptr); // Q: Does unique_ptr have a partial template specialization for unique_ptr of array type?

  ++next_index;
} 

template<class T> void Vector<T>::free()
{
  p.reset();
  size = 0;
}

template<class T> Vector<T>::Vector(const Vector& lhs)
{
  p.reset(); 

  p = new T[lhs.size];

  std::copy(p, lhs.p, lhs.p + lhs.size);

  size = lhs.size;

  next_index = lhs.next_index;
}

template<class T> void Vector<T>::push_back(const T& t)
{
  if (next_index == size) {
      
     grow();
  }

  p[next_index++] = t;
}

template<class T> void  Vector<T>::push_back(T&& t)
{
  if (next_index == size) {
     grow();
  }
  
  p[next_index++] = std::move( t );
}

template<class T> template<class... ARGS> void Vector<T>::emplace_back(ARGS&& ... args)
{
   new(p + next_index) T{std::forward<ARGS>(args)...};
   
   next_index++; 
}

template<class T> T& Vector<T>::operator[](int pos)
{
  if (pos < size && pos > 0) {
      
     return p[pos];

  } else {

    throw(std::out_of_range("pos not in range."));
  }
}

template<class T> const T&    Vector<T>::operator[](int pos) const
{
  if (pos < size && pos > 0) {
      
     return const_cast<const T&>(p[pos]);

  } else {

    throw(std::out_of_range("pos not in range."));
  }

}
                 
template<class T> Vector<T>&  Vector<T>::operator=(const Vector& lhs)
{
   if (this != &lhs) {

       delete [] p;

       size = lhs.size;

       p = new char[size * sizeof(T)];

       copy(p, lhs.p, lhs.p + lhs.size);
   }     

   return *this;
}
                 
template<class T> Vector<T>&  Vector<T>::operator=(Vector&& lhs)
{
   if (this != &lhs)  {

       delete [] p;

       p = lhs.p; 

       lhs.p = nullptr;

       size = lhs.size;
   }     

   return *this;
}
#endif