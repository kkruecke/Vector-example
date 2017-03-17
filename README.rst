Overview
========

This is a sample class used to explain pefect forwarding and its us to do emplace construction within a container. It is under development.

TODO
----

The template class ``template <class T, class D = default_delete<T>> class unique_ptr`` has a partial template specialization for arrays:

.. code-block:: cpp 

    template <class T, class D> class unique_ptr<T[],D>

which uses a different deleter ( to do ``delete []``), and it has an ``operator[](int)`` method. See details on `MSDN <https://msdn.microsoft.com/en-us/library/ee410601.aspx>`_. 

So when, for example, ``unique_ptr<std::string[]>`` is used, the partial template specialization for arrays is preferred. To understand the tradeoffs and restrictions
for the array specialization see:

#. This excellent discussion of the tradeoffs on `stackoverflow <http://stackoverflow.com/questions/16711697/is-there-any-use-for-unique-ptr-with-array>`_.
#. For explanation of "see below d..." comment(s), see these excellent unique_ptr header `annotations and comments <https://timsong-cpp.github.io/cppwp/unique.ptr.runtime>`_. 
