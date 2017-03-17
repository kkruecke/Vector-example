Overview
========

This is a sample class used to explain pefect forwarding and its us to do emplace construction within a container. It is under development.

TODO
----

The template class ``template <class T, class D = default_delete<T>> class unique_ptr`` has a partial template specialization for arrays:

.. code-block:: cpp 

    template <class T, class D> class unique_ptr<T[],D>

which uses a different deleter ( to do ``delete []``), and it has an ``operator[](int)`` method. See details on `MSDN <https://msdn.microsoft.com/en-us/library/ee410601.aspx>`_. 

So when, say, ``unique_ptr<std::string[]>`` is used, the partial template specialization is preferred. So one can't mix and match ``unique_ptr<T>`` and ``unique_ptr<T[]>``
as they are different types.   

See this excellent discussion of the tradeoffs of ``unique_ptr<T[]>``: http://stackoverflow.com/questions/16711697/is-there-any-use-for-unique-ptr-with-array
