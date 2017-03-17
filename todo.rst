TODO
====

Debug compile errors in vector.h. 

``template <class T, class D = default_delete<T>> class unique_ptr`` has a partial template specialization for arrays
 ``template <class T, class D> class unique_ptr<T[],D>``, which uses a different deleter ( to do ``delete []``), and it has an ``operator[](int)`` method. 

So I can't mix and match ``unique_ptr<T>`` and ``unique_ptr<T[]>`` as they are different types.   

When, say, ``unique_ptr<std::string[]>`` is used, the partial template specialization is preferred.

The tradeoffs of ``unique_ptr<T[]>`` are mentioned here: http://stackoverflow.com/questions/16711697/is-there-any-use-for-unique-ptr-with-array
