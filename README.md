# The Vienna Type List Library (VTLL)
The Vienna Type List Library (VTLL) is a collection of C++20 type list algorithms, written by Prof. Helmut Hlavacs, University of Vienna. Such algorithms run at *compile time*, and automatically create types and structs for your C++ programs to compile with. An example library using VTLL is given by the Vienna Entity Component System (VECS) library, a sibling project of VTLL. VECS uses VTLL extensively, and thus also provides concrete examples.

Its starting point is a post from Nils Deppe (https://nilsdeppe.com/posts/tmpl-part2). The static_assert statement from this post and the way name space detail is used are taken from this post.

Using the library simply means to include the single include file VTLL.h, and using the structs in the namespace *vtll*. Examples for its use are given by *static_assert* statements. For example, MSVC immediately indicates whether a *static_assert* evaluates to true, by underlining false statements with red wiggles. So if its not underlined, the statement is true, if it is underlined, something is wrong. This applies to all *static_asserts* in VTLL.

For building the example project for MSVC just run the msvc.bat batch file.

## Algorithms
VTLL contains the following structs and algorithms:

* *type_list* and *detail::type_list2*: structures that can be used to hold lists of types. Of course, any other similarly templated struct can be used as type list.
* *size*: size of a type list
* *Nth_type*: get the Nth element from a type list
* *front*: first element of a type list
* *back*: get the last element from a list
* *index_of*: index of a type within a type list
* *cat*: concatenate two type lists to one big type list, the result is of the first list type
* *to_ptr*: turn list elements into pointers
* *variant_type*: make a summary variant type of all elements in a list
* *transform*: transform list<types> into list<Function<types>>
* *is_same*: test if a list contains the same types as types of a variadic parameter pack
* *transfer*: transfer a list of types1 into a list of types2
* *substitute*: substitute a type list TYPE with another list type
* *to_tuple*: turn a list into a tuple
* *to_ref_tuple*: turn a list into a tuple of reference types. When creating such tuples, use std::ref as a wrapper for the elements!
* *to_ptr_tuple*: turn a list into a tuple of pointer types
* *has_type*: check whether a type list contains a type
* *has_any_type*: check whether a type list contains ANY type of a second typelist
* *erase_type*: erase a type C from a type list
* *erase_Nth*: erase the Nth element of a list
* *has_all_types*: check whether a type list contains ALL types of a second typelist
* *filter_have_type*: keep only those type lists Ts<...> that have a specific type C as member
* *filter_have_all_type*: keep only those type lists Ts<...> that have ALL specified type Cs from another list Seq2<Cs...> as member
* *N_tuple*: make a tuple containing a type T N times
* *static_for*: with this compile time for loop you can loop over any tuple, type list, or variadic argument list

## Usage

The main starting points are types and lists of types. In this example, *A* is a type struct:

    struct A;

In this case, since its members are not defined at this point, *A* is an incomplete type. This is already enough to use *A* as type in VTLL! A complete type could look something like this:

    struct B {
      int i;
    };

Both versions of types are fine for VTLL. In order to create type lists, we have to specify template parameters that can be added:

    template<typename T>
    struct A;

*A* is now a type that must *contain* exactly one other type parameter:

    using B = A<int>;

Here, *B* is a synonym for type *A* containing the type *int*. If we want *A* to hold more types, we define a variadic type list:

    template<typename... Ts>
    struct A;

Now, *A* can hold any number of types:

    using B = A<int>;
    using C = A<float>;
    using D = A<int, float, double>;

VTLL offers a standard type list type called *type_list*, but as shown any other such templated type is also a type list and can be used with VTLL.

The VTLL algorithms now work on such type lists. They accept types and type lists and others, and produce result type lists, or std::tuples from them, or test whether the lists have a specific property, e.g., contain a specific type or not. As a rule, the first parameter is always a type list, and the following parameters can be variadic parameter packs, types, or other type lists. The results of an algorithm *<STRUCTNAME<...>>* may be used in either of these ways:
* Use just the struct directly, e.g. *Nth_type<...>* or *cat<...>*
* Use *typename <STRUCTNAME<...>>::type*, e.g. *typename to_ptr_tuple<...>::type*
* Use *\<STRUCTNAME<...>>::value*, e.g. *has_type<...>::value* for gaining a *value* (e.g. *bool*, *size_t*, ...), not a type


### Example for Testing Properties

An example for testing properties is *has_type*. It tests whether the list contains a given type. The following static_assert must always evaluate to true:

    static_assert(
      has_type< type_list<double, int, char, double>, char >::value
      , "The implementation of has_type is bad");

The main part here is the boolean *value*

    has_type< type_list<double, int, char, double>, char >::value

which should always by true. This means that the type list  *type_list<double, int, char, double>* contains the type *char*, which is the case. Conversely, the following static assert is also true:

    static_assert(
      !has_type< type_list<double, int, char, double>, float >::value
      , "The implementation of has_type is bad");

since the type list *type_list<double, int, char, double>* does *not* contain the type *float* (Notice the ! operator).

### Example for Extracting Types

An example for extracting types is given by *Nth_type*. The following static assert is always true:

    static_assert(
      std::is_same_v<
        Nth_type<type_list<double, char, bool, double>, 1>, char>
      , "The implementation of Nth_type is bad");

which means that the type with index 1 (i.e., the 2nd element, indexing starts with 0) of *type_list<double, char, bool, double>* is *char*.

### Example for Creating New Type Lists

An example for creating new type lists from old ones is given by *cat*, which concatenates two type lists into one big list.

    static_assert(
      std::is_same_v<
        cat< type_list<double, int>, detail::type_list2<char, float> >
        , type_list<double, int, char, float> >
      , "The implementation of cat is bad");

Here two type lists (one of type *type_list* and one of type *detail::type_list2*) are joined, resulting in another *type_list*. The result here is always of type of the first type list.

Another example is *erase_Nth*, which removes an indexed element from a list. Consider the following examples:

    //pop the element with index 1 (i.e., the 2nd element, indexing starts with 0)
    static_assert(
      std::is_same_v<
        erase_Nth< type_list<double, char, bool, double>, 1>
        , type_list<double, bool, double > > );

    //pop front (first) element
    static_assert(
      std::is_same_v<
        erase_Nth< type_list<double, char, bool, double>, 0>
        , type_list<char, bool, double > >);

    //pop back (last) element
    namespace detail {
      using example_list = type_list<double, char, bool, double>;
    }
    static_assert(
      std::is_same_v<
        erase_Nth< detail::example_list
          , size<detail::example_list>::value -1 > //index of last element
        , type_list<double, char, bool > >);


### Example for Creating Tuples

An example for creating tuples is given by *to_ref_tuple*, which turns a type list <STRUCT<Cs...>>into a *std::tuple<Cs&...>* of references.

    static_assert(
      std::is_same_v<
        typename to_ref_tuple<type_list<double, int>>::type
        , std::tuple<double&, int&> >
      , "The implementation of to_ref_tuple is bad");

However, this results only in a *type* of a tuple, not in a tuple itself. When constructing such a tuple, you should use std::ref as a wrapper for the tuple elements:

    using tuple_type = typename to_ref_tuple<type_list<double, int>>::type;

    void func( tuple_type & tup ) {
      std::get<0>(tup) = 1.0;         //d = 1.0
    }

    double d;
    int i;
    tuple_type tup = std::make_tuple(std::ref(d), std::ref(i));
    //...
    func(tup);


### Static For Loop

A particularly useful struct is the static_for struct, to be used inside of functions. In this example, using C++20 type traits, the names of all elements of a type list is printed to the console:

    namespace detail {
      void f() {
      using list = type_list<int, double, bool, float >;

      static_for< int, 0, size<list>::value >(
        [&](auto i) {
          using type = Nth_type<list, i>;

          std::cout << i << " " << typeid(type).name(); }
        );
      }
    }

The loop requires a \<BEGIN\> and an \<END\> integer number, then the lambda function is called for i = \<BEGIN> to \<END> - 1 . In the example, the loop runs from index 0 to the last index *size\<list>::value* - 1.
