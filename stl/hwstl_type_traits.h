#ifndef _HWTYPE_TRAITS_H 
#define _HWTYPE_TRAITS_H 
 
 
namespace hwstl{ 
 
struct __true_type{}; 
struct __false_type{}; 
 
template<class T> 
struct __hwtype_traits{ 
    typedef __false_type has_trivial_default_constructor; 
    typedef __false_type has_trivial_copy_constructor; 
    typedef __false_type has_trivial_assignment_operator; 
    typedef __false_type has_trivial_destructor; 
    typedef __false_type is_POD_type; 
}; 
 
template<> 
struct __hwtype_traits<char>{ 
    typedef __true_type has_trivial_default_constructor; 
    typedef __true_type has_trivial_copy_constructor; 
    typedef __true_type has_trivial_assignment_operator; 
    typedef __true_type has_trivial_destructor; 
    typedef __true_type is_POD_type; 
}; 
 
template<> 
struct __hwtype_traits<signed char>{ 
    typedef __true_type has_trivial_default_constructor; 
    typedef __true_type has_trivial_copy_constructor; 
    typedef __true_type has_trivial_assignment_operator; 
    typedef __true_type has_trivial_destructor; 
    typedef __true_type is_POD_type; 
}; 
 
 
template<> 
struct __hwtype_traits<unsigned char>{ 
    typedef __true_type has_trivial_default_constructor; 
    typedef __true_type has_trivial_copy_constructor; 
    typedef __true_type has_trivial_assignment_operator; 
    typedef __true_type has_trivial_destructor; 
    typedef __true_type is_POD_type; 
}; 
 
 
template<> 
struct __hwtype_traits<short>{ 
    typedef __true_type has_trivial_default_constructor; 
    typedef __true_type has_trivial_copy_constructor; 
    typedef __true_type has_trivial_assignment_operator; 
    typedef __true_type has_trivial_destructor; 
    typedef __true_type is_POD_type; 
}; 
 
template<> 
struct __hwtype_traits<unsigned short>{ 
    typedef __true_type has_trivial_default_constructor; 
    typedef __true_type has_trivial_copy_constructor; 
    typedef __true_type has_trivial_assignment_operator; 
    typedef __true_type has_trivial_destructor; 
    typedef __true_type is_POD_type; 
}; 
 
template<> 
struct __hwtype_traits<int>{ 
    typedef __true_type has_trivial_default_constructor; 
    typedef __true_type has_trivial_copy_constructor; 
    typedef __true_type has_trivial_assignment_operator; 
    typedef __true_type has_trivial_destructor; 
    typedef __true_type is_POD_type; 
}; 
 
template<> 
struct __hwtype_traits<unsigned int>{ 
    typedef __true_type has_trivial_default_constructor; 
    typedef __true_type has_trivial_copy_constructor; 
    typedef __true_type has_trivial_assignment_operator; 
    typedef __true_type has_trivial_destructor; 
    typedef __true_type is_POD_type; 
}; 
 
template<> 
struct __hwtype_traits<long>{ 
    typedef __true_type has_trivial_default_constructor; 
    typedef __true_type has_trivial_copy_constructor; 
    typedef __true_type has_trivial_assignment_operator; 
    typedef __true_type has_trivial_destructor; 
    typedef __true_type is_POD_type; 
}; 
 
template<> 
struct __hwtype_traits<unsigned long>{ 
    typedef __true_type has_trivial_default_constructor; 
    typedef __true_type has_trivial_copy_constructor; 
    typedef __true_type has_trivial_assignment_operator; 
    typedef __true_type has_trivial_destructor; 
    typedef __true_type is_POD_type; 
}; 
 
template<> 
struct __hwtype_traits<float>{ 
    typedef __true_type has_trivial_default_constructor; 
    typedef __true_type has_trivial_copy_constructor; 
    typedef __true_type has_trivial_assignment_operator; 
    typedef __true_type has_trivial_destructor; 
    typedef __true_type is_POD_type; 
}; 
 
template<> 
struct __hwtype_traits<double>{ 
    typedef __true_type has_trivial_default_constructor; 
    typedef __true_type has_trivial_copy_constructor; 
    typedef __true_type has_trivial_assignment_operator; 
    typedef __true_type has_trivial_destructor; 
    typedef __true_type is_POD_type; 
}; 
 
template<> 
struct __hwtype_traits<long double>{ 
    typedef __true_type has_trivial_default_constructor; 
    typedef __true_type has_trivial_copy_constructor; 
    typedef __true_type has_trivial_assignment_operator; 
    typedef __true_type has_trivial_destructor; 
    typedef __true_type is_POD_type; 
}; 
 
template<class T> 
struct __hwtype_traits<T*>{ 
    typedef __true_type has_trivial_default_constructor; 
    typedef __true_type has_trivial_copy_constructor; 
    typedef __true_type has_trivial_assignment_operator; 
    typedef __true_type has_trivial_destructor; 
    typedef __true_type is_POD_type; 
}; 
 
 
 
 
 
} 
#endif
