// Clang stl header outline for unique_ptr
#ifndef _LIBCPP_MEMORY
#define _LIBCPP_MEMORY

namespace std 
{

struct allocator_arg_t { };
constexpr allocator_arg_t allocator_arg = allocator_arg_t();

template <class T, class Alloc> struct uses_allocator;

template <class Ptr>
struct pointer_traits
{
    typedef Ptr pointer;
    typedef <details> element_type;
    typedef <details> difference_type;

    template <class U> using rebind = <details>;

    static pointer pointer_to(<details>);
};

template <class T>
struct pointer_traits<T*>
{
    typedef T* pointer;
    typedef T element_type;
    typedef ptrdiff_t difference_type;

    template <class U> using rebind = U*;

    static pointer pointer_to(<details>) noexcept;
};

template <class Alloc>
struct allocator_traits
{
    typedef Alloc                        allocator_type;
    typedef typename allocator_type::value_type
                                         value_type;

    typedef Alloc::pointer | value_type* pointer;
    typedef Alloc::const_pointer
          | pointer_traits<pointer>::rebind<const value_type>
                                         const_pointer;
    typedef Alloc::void_pointer
          | pointer_traits<pointer>::rebind<void>
                                         void_pointer;
    typedef Alloc::const_void_pointer
          | pointer_traits<pointer>::rebind<const void>
                                         const_void_pointer;
    typedef Alloc::difference_type
          | pointer_traits<pointer>::difference_type
                                         difference_type;
    typedef Alloc::size_type
          | make_unsigned<difference_type>::type
                                         size_type;
    typedef Alloc::propagate_on_container_copy_assignment
          | false_type                   propagate_on_container_copy_assignment;
    typedef Alloc::propagate_on_container_move_assignment
          | false_type                   propagate_on_container_move_assignment;
    typedef Alloc::propagate_on_container_swap
          | false_type                   propagate_on_container_swap;
    typedef Alloc::is_always_equal
          | is_empty                     is_always_equal;

    template <class T> using rebind_alloc  = Alloc::rebind<U>::other | Alloc<T, Args...>;
    template <class T> using rebind_traits = allocator_traits<rebind_alloc<T>>;

    static pointer allocate(allocator_type& a, size_type n);
    static pointer allocate(allocator_type& a, size_type n, const_void_pointer hint);

    static void deallocate(allocator_type& a, pointer p, size_type n) noexcept;

    template <class T, class... Args>
        static void construct(allocator_type& a, T* p, Args&&... args);

    template <class T>
        static void destroy(allocator_type& a, T* p);

    static size_type max_size(const allocator_type& a); // noexcept in C++14

    static allocator_type
        select_on_container_copy_construction(const allocator_type& a);
};

template <>
class allocator<void>
{
public:
    typedef void*                                 pointer;
    typedef const void*                           const_pointer;
    typedef void                                  value_type;

    template <class _Up> struct rebind {typedef allocator<_Up> other;};
};

template <class T>
class allocator
{
public:
    typedef size_t                                size_type;
    typedef ptrdiff_t                             difference_type;
    typedef T*                                    pointer;
    typedef const T*                              const_pointer;
    typedef typename add_lvalue_reference<T>::type       reference;
    typedef typename add_lvalue_reference<const T>::type const_reference;
    typedef T                                     value_type;

    template <class U> struct rebind {typedef allocator<U> other;};

    allocator() noexcept;
    allocator(const allocator&) noexcept;
    template <class U> allocator(const allocator<U>&) noexcept;
    ~allocator();
    pointer address(reference x) const noexcept;
    const_pointer address(const_reference x) const noexcept;
    pointer allocate(size_type, allocator<void>::const_pointer hint = 0);
    void deallocate(pointer p, size_type n) noexcept;
    size_type max_size() const noexcept;
    template<class U, class... Args>
        void construct(U* p, Args&&... args);
    template <class U>
        void destroy(U* p);
};

template <class T, class U>
bool operator==(const allocator<T>&, const allocator<U>&) noexcept;

template <class T, class U>
bool operator!=(const allocator<T>&, const allocator<U>&) noexcept;

template <class OutputIterator, class T>
class raw_storage_iterator
    : public iterator<output_iterator_tag,
                      T,                               // purposefully not C++03
                      ptrdiff_t,                       // purposefully not C++03
                      T*,                              // purposefully not C++03
                      raw_storage_iterator&>           // purposefully not C++03
{
public:
    explicit raw_storage_iterator(OutputIterator x);
    raw_storage_iterator& operator*();
    raw_storage_iterator& operator=(const T& element);
    raw_storage_iterator& operator++();
    raw_storage_iterator  operator++(int);
};

template <class T> pair<T*,ptrdiff_t> get_temporary_buffer(ptrdiff_t n) noexcept;
template <class T> void               return_temporary_buffer(T* p) noexcept;

template <class T> T* addressof(T& r) noexcept;

template <class InputIterator, class ForwardIterator>
ForwardIterator
uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result);

template <class InputIterator, class Size, class ForwardIterator>
ForwardIterator
uninitialized_copy_n(InputIterator first, Size n, ForwardIterator result);

template <class ForwardIterator, class T>
void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& x);

template <class ForwardIterator, class Size, class T>
ForwardIterator
uninitialized_fill_n(ForwardIterator first, Size n, const T& x);

template <class T>
struct default_delete
{
    constexpr default_delete() noexcept = default;
    template <class U> default_delete(const default_delete<U>&) noexcept;

    void operator()(T*) const noexcept;
};

template <class T>
struct default_delete<T[]>
{
    constexpr default_delete() noexcept = default;
    void operator()(T*) const noexcept;
    template <class U> void operator()(U*) const = delete;
};

template <class T, class D = default_delete<T>>
class unique_ptr
{
public:
    typedef see below pointer;
    typedef T element_type;
    typedef D deleter_type;

    // constructors
    constexpr unique_ptr() noexcept;
    explicit unique_ptr(pointer p) noexcept;
    unique_ptr(pointer p, see below d1) noexcept;
    unique_ptr(pointer p, see below d2) noexcept;
    unique_ptr(unique_ptr&& u) noexcept;
    unique_ptr(nullptr_t) noexcept : unique_ptr() { }
    template <class U, class E>
        unique_ptr(unique_ptr<U, E>&& u) noexcept;
    template <class U>
        unique_ptr(auto_ptr<U>&& u) noexcept;

    // destructor
    ~unique_ptr();

    // assignment
    unique_ptr& operator=(unique_ptr&& u) noexcept;
    template <class U, class E> unique_ptr& operator=(unique_ptr<U, E>&& u) noexcept;
    unique_ptr& operator=(nullptr_t) noexcept;

    // observers
    typename add_lvalue_reference<T>::type operator*() const;
    pointer operator->() const noexcept;
    pointer get() const noexcept;
    deleter_type& get_deleter() noexcept;
    const deleter_type& get_deleter() const noexcept;
    explicit operator bool() const noexcept;

    // modifiers
    pointer release() noexcept;
    void reset(pointer p = pointer()) noexcept;
    void swap(unique_ptr& u) noexcept;
};

template <class T, class D>
class unique_ptr<T[], D>
{
public:
    typedef implementation-defined pointer;
    typedef T element_type;
    typedef D deleter_type;

    // constructors
    constexpr unique_ptr() noexcept;
    explicit unique_ptr(pointer p) noexcept;
    unique_ptr(pointer p, see below d) noexcept;
    unique_ptr(pointer p, see below d) noexcept;
    unique_ptr(unique_ptr&& u) noexcept;
    unique_ptr(nullptr_t) noexcept : unique_ptr() { }

    // destructor
    ~unique_ptr();

    // assignment
    unique_ptr& operator=(unique_ptr&& u) noexcept;
    unique_ptr& operator=(nullptr_t) noexcept;

    // observers
    T& operator[](size_t i) const;
    pointer get() const noexcept;
    deleter_type& get_deleter() noexcept;
    const deleter_type& get_deleter() const noexcept;
    explicit operator bool() const noexcept;

    // modifiers
    pointer release() noexcept;
    void reset(pointer p = pointer()) noexcept;
    void reset(nullptr_t) noexcept;
    template <class U> void reset(U) = delete;
    void swap(unique_ptr& u) noexcept;
};

template <class T, class D>
    void swap(unique_ptr<T, D>& x, unique_ptr<T, D>& y) noexcept;

template <class T1, class D1, class T2, class D2>
    bool operator==(const unique_ptr<T1, D1>& x, const unique_ptr<T2, D2>& y);
template <class T1, class D1, class T2, class D2>
    bool operator!=(const unique_ptr<T1, D1>& x, const unique_ptr<T2, D2>& y);
template <class T1, class D1, class T2, class D2>
    bool operator<(const unique_ptr<T1, D1>& x, const unique_ptr<T2, D2>& y);
template <class T1, class D1, class T2, class D2>
    bool operator<=(const unique_ptr<T1, D1>& x, const unique_ptr<T2, D2>& y);
template <class T1, class D1, class T2, class D2>
    bool operator>(const unique_ptr<T1, D1>& x, const unique_ptr<T2, D2>& y);
template <class T1, class D1, class T2, class D2>
    bool operator>=(const unique_ptr<T1, D1>& x, const unique_ptr<T2, D2>& y);

template <class T, class D>
    bool operator==(const unique_ptr<T, D>& x, nullptr_t) noexcept;
template <class T, class D>
    bool operator==(nullptr_t, const unique_ptr<T, D>& y) noexcept;
template <class T, class D>
    bool operator!=(const unique_ptr<T, D>& x, nullptr_t) noexcept;
template <class T, class D>
    bool operator!=(nullptr_t, const unique_ptr<T, D>& y) noexcept;

template <class T, class D>
    bool operator<(const unique_ptr<T, D>& x, nullptr_t);
template <class T, class D>
    bool operator<(nullptr_t, const unique_ptr<T, D>& y);
template <class T, class D>
    bool operator<=(const unique_ptr<T, D>& x, nullptr_t);
template <class T, class D>
    bool operator<=(nullptr_t, const unique_ptr<T, D>& y);
template <class T, class D>
    bool operator>(const unique_ptr<T, D>& x, nullptr_t);
template <class T, class D>
    bool operator>(nullptr_t, const unique_ptr<T, D>& y);
template <class T, class D>
    bool operator>=(const unique_ptr<T, D>& x, nullptr_t);
template <class T, class D>
    bool operator>=(nullptr_t, const unique_ptr<T, D>& y);

}
#endif
