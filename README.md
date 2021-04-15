# The Vienna Type List Library (VTLL)
The Vienna Type List Library (VTLL) is a collection of C++20 type list algorithms, written by Prof. Helmut Hlavacs, University of Vienna. Such algorithms run at *compile time*, and automatically create types and structs for your C++ programs to compile with. An example library using VTLL is given by the Vienna Entity Component System (VECS) library, a sibling project of VTLL. VECS uses VTLL extensively, and thus also provides concrete examples.

Its starting point is a post from Nils Deppe (https://nilsdeppe.com/posts/tmpl-part2). The static_assert statement from this post and the way name space detail is used are taken from this post.

Using the library simply means to include the single include file VTLL.h, and using the structs in the namespace *vtll*. Examples for its use are given by *static_assert* statements. For example, MSVC immediately indicates whether a *static_assert* evaluates to true, by underlining false statements with red wiggles. So if its not underlined, the statement is true, if it is underlined, something is wrong. This applies to all *static_asserts* in VTLL.

For building the example project for MSVC just run the msvc.bat batch file.

## Algorithms
VTLL contains the following structs and algorithms:

### Conversion Algorithms

* *type_list* and *detail::type_list2*: structures that can be used to hold lists of types. Of course, any other similarly templated struct can be used as type list.
* *value_list*: a list that stores size_t values
* *type_to_value*: turn a list of std::integral_constant<> into a value list
* *value_to_type*: turn a value list into a list of std::integral_constant<>
* *index_to_value*: turn a std::index_sequence into a value_list
* *value_to_index*: turn a value_list into a std::index_sequence

### Type List Algorithms

* *size*: size of a type list
* *Nth_type*: get the Nth element from a type list
* *front*: first element of a type list
* *back*: get the last element from a list
* *index_of*: index of first occurrence of a type within a type list
* *cat*: concatenate two type lists to one big type list, the result is of the first list type
* *to_ref*: turn list elements into references
* *to_ptr*: turn list elements into pointers
* *to_variant*: make a summary variant type of all elements in a list
* *transform*: transform list<types> into list<Function<types>>
* *transform_size_t*: transform list<types> into list<Function<types,size_t>>, e.g. for using std::array<T,size_t>
* *is_same*: test if a list contains the same types as types of a variadic parameter pack
* *is_pow2*: test whether a std::integral_constant<size_t, I> is a power of 2
* *smallest_pow2_larger_eq*: find smallest power of 2 larger or equal than a given number
* *transfer*: transfer a list of types1 into a list of types2
* *substitute*: substitute a type list TYPE with another list type
* *has_type*: check whether a type list contains a type
* *have_type*: check whether all elements of a list of lists contain an element
* *has_any_type*: check whether a type list contains ANY type of a second type list
* *has_all_types*: check whether a type list contains ALL types of a second type list
* *filter_have_type*: keep only those type lists Ts<...> that have a specific type C as member
* *filter_have_all_types*: keep only those type lists Ts<...> that have ALL specified types Cs from another list Seq2<Cs...>
* *filter_have_any_type*: keep only those type lists Ts<...> that have ANY specified type Cs from another list Seq2<Cs...> as member
* *erase_type*: erase a type C from a type list
* *erase_Nth*: erase the Nth element of a list
* *sum*: compute the sum of a list of std::integral_constant<size_t, I>
* *max*: compute the max of a list of std::integral_constant<size_t, I>
* *min*: compute the min of a list of std::integral_constant<size_t, I>
* *function*: compute function on list of std::integral_constant<size_t, I>
* *map*: find a type key in a map, i.e. a list of type key - type value pairs, and retrieve its type value, or a default type if not found
* *apply_map*: apply a list of keys to a map, get the list of their values, or defaults if the keys are not found
* *N_tuple*: make a tuple containing a type T N times
* *remove_duplicates*: remove duplicates from a list
* *flatten*: turn a list LL of lists into one list that holds all elements from LL
* *intersection*: return a list of those elements that are in all given lists
* *static_for*: with this compile time for loop you can loop over any tuple, type list, or variadic argument list

### Tuple Algorithms

* *to_tuple*: turn a list into a tuple
* *to_ref_tuple*: turn a list into a tuple of reference types. When creating such tuples, use std::tie or std::forward_as_tuple
* *to_rvref_tuple*: turn a list into a tuple of prvalue reference types. When creating such tuples, use std::move, std::tie or std::forward_as_tuple
* *to_ptr_tuple*: turn a list into a tuple of pointer types
* *is_same_tuple*: test whether two tuples are the same
* *sub_tuple*: extract a subtuple from a tuple
* *sub_ref_tuple*: extract a subtuple of references from a tuple

### Value List Algorithms

* *size_value*: get the size of a value list
* *Nth_value*: get the Nth value from a value list
* *front_value*: get the first value from a value list
* *back_value*: get the last value from a value list
* *sum_value*: compute the sum of a list of size_t s
* *is_pow2_value*: test whether a value is a power of 2
* *function_value*: compute function on list of size_t s


## Usage

VTLL is a single-header library, just include *VTLL.h*. The main starting points are types and lists of types. In this example, *A* is a type struct:

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

Here, *B* is a synonym for type *A* containing the type *int*. If we want *A* to hold more types, we can demand more template parameters, or more generally define a variadic *type list*:

    template<typename... Ts>
    struct A;

Now, *A* is a type list and can hold any number of types:

  	struct S {
        int i;
        //...
    };

    using B = A<S>;
    using C = A<float, char>;
    using D = A<int, float, S>;

VTLL offers a standard type list type called *type_list*, but as shown any other such templated type is also a type list and can be used with VTLL.

    using E = type_list<int, float, S, S>;

The VTLL algorithms now work on such type lists. They accept types and type lists and others, and produce result type lists, or std::tuples from them, or test whether the lists have a specific property, e.g., contain a specific type or not. As a rule, the first parameter is always a type list, and the following parameters can be variadic parameter packs, types, or other type lists. The results of an algorithm *\<ALGORITHM<...>>* may be used in either of these ways:
* Use the algorithm directly to get a *type*, e.g. *Nth_type\<...>* or *cat\<...>*.
* Use *\<ALGORITHM<...>>::value*, e.g., *has_type<...>::value*, for gaining a *value* like *int*, *bool*, *size_t*, etc., not a type.

A special case is given if the list contains only values, not types. Consider the following struct:

    template <size_t... Is>
    struct value_list {
        using size = std::integral_constant<std::size_t, sizeof...(Is)>;
    };

The template parameters are now integer numbers of type *size_t*, the list can therefore only store unsigned integers. Here we talk about a *value list*:

    using vl = value_list<1,2,3,4,5>;

Though value lists are similar to type lists, they must be treated differently. VTLL thus contains a different set of algorithms for value lists. Note that the type *std::integral_constant<size_t, N>* is a type that can store a value. All value list algorithms result in a *std::integral_constant<size_t, N>*, and its value can be retrieved by using *::value* after the algorithm. Since *size_t* is an *unsigned int*, if a signed type is needed, *size_t* can simply be changed to *int*. However, in most cases, unsigned is enough.

Also note that the algorithms *type_to_value* and *value_to_type* can be used to transform type lists (lists of std::integral_constant<>) to value lists and vice versa. Thus a value list can be quickly transformed into a type list, and all type list algorithms can then be applied. The result can then be transformed back into a value list.



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
        to_ref_tuple<type_list<double, int>>, std::tuple<double&, int&> >
      , "The implementation of to_ref_tuple is bad");

However, this results only in a *type* of a tuple, not in a tuple itself. When constructing such a tuple, you should use std::ref as a wrapper for the tuple elements:

    using tuple_type = to_ref_tuple<type_list<double, int>>;

    void func( tuple_type & tup ) {
      std::get<0>(tup) = 1.0;         //d = 1.0
    }

    double d;
    int i;
    tuple_type tup = std::make_tuple(std::ref(d), std::ref(i));
    //...
    func(tup);


### Example for a Value List Algorithm

An exampe for a value list algorithm is given by *Nth_value*, which retrieves the Nth value from a value list.

    namespace detail {
      template <typename Seq, size_t N>
      struct Nth_value_impl;

      template < template<size_t...> typename Seq, size_t... Is, size_t N>
      struct Nth_value_impl<Seq<Is...>,N> {
        using type = Nth_type< type_list<std::integral_constant<size_t, Is>...>, N>;
      };
    }

    template <typename Seq, size_t N>
    using Nth_value = typename detail::Nth_value_impl<Seq, N>::type;

    static_assert( std::is_same_v< Nth_value< value_list<1, 2, 3>, 1 >, std::integral_constant<size_t, 2> >,
      "The implementation of Nth_value is bad");

The trick here is to turn a value list into a type list by wrapping the values into types *std::integral_constant<>* (using the parameter pack), and then apply the *Nth_type* algorithm.

An example for a meta algorithm is given by computing the sum of squares of a value list.

    using vl = vtll::value_list<1, 2, 3, 4>;

    template<typename T>
    struct sqr {
    	using type = std::integral_constant<size_t, T::value * T::value>;
    };

    using sum_squares = vtll::sum< vtll::function< vtll::value_to_type<vl>, sqr> >;
    static_assert( sum_squares::value == 30);

In this example, the value list is first transformed into a type list, then the sqr function is applied, then all list elements are summed up. The result in this case is *std::integral_constant<size_t,30>*. Alternatively, the squaring can be done on a value list directly:

    template<size_t I>
    struct sqr2 {
    	using type = std::integral_constant<size_t, I*I>;
    };

    using sum_squares2 = vtll::sum< vtll::function_value< sqr2, 1, 2, 3, 4 > >;
    static_assert(sum_squares2::value == 30);

Again, the result is *std::integral_constant<size_t,30>*.


### Static For Loop

A particularly useful struct is the static_for struct, to be used inside of functions. In this example, using C++20 type traits, the names of all elements of a type list is printed to the console:

    namespace detail {
      void f() {
      using list = type_list<int, double, bool, float >;

      static_for< int, 0, size<list>::value >(
        [&](auto i) {
          using type = Nth_type<list, i>;
          std::cout << i << " " << typeid(type).name() << std::endl; }
        );
      }
    }

The loop requires a \<BEGIN\> and an \<END\> integer number, then the lambda function is called for i = \<BEGIN> to \<END> - 1 . In the example, the loop runs from index 0 to the last index *size\<list>::value* - 1. When calling vtll::detail::f(), the output looks like this:

    0 int
    1 double
    2 bool
    3 float


### A More Complex Example: Type Dependent Default values

In a more complex example we want to define default values for different entity types. An entity is a collection of components:

    //declare components
    struct VeComponentName {
  		std::string m_name;
  	};

    struct VeComponentPosition {
        glm::vec3 m_position;
    };
    //...

Entities are now type lists of such components:

    template <typename... Ts>
    struct VeEntityType {};

    //declare entities
    using VeEntityTypeNode = VeEntityType<VeComponentName, VeComponentPosition, VeComponentOrientation, VeComponentTransform>;
    using VeEntityTypeDraw = VeEntityType<VeComponentName, VeComponentMaterial, VeComponentGeometry>;
    using VeEntityTypeAnimation = VeEntityType<VeComponentName, VeComponentAnimation>;
    //...

The list *VeEntityTypeList* stores all existing entities:

    using VeEntityTypeList = vtll::type_list<
        VeEntityTypeNode
      , VeEntityTypeDraw
      , VeEntityTypeAnimation
      // ,...
    >;

We now store entities and their components in a data structure that is a list of segments. Since the number of entities needed can vary drastically, we need some way to define default values for the segment sizes and the maximum number of each entity type. For this case we define a *map*, i.e., a type list of key-value pairs, including a "default default" value:

    using VeTableSizeDefault = vtll::value_list< 10, 16 >; //default default value

    using VeTableSizeMap = vtll::type_list<
        vtll::type_list< VeEntityTypeNode,		  vtll::value_list< 12, 20 > >
      , vtll::type_list< VeEntityTypeDraw,		  vtll::value_list< 12, 20 > >
      , vtll::type_list< VeEntityTypeAnimation,	vtll::value_list< 8, 10 > >
      //, ...
    >;

The numbers in the value_list<A,B> are powers of 2, the default values are thus segment size = 2^A, and max number = 2^B. This can easily be computed with the left shift operator *<<*, i.e., segm size = 1 << A and max num = 1 << B:

    template<typename E = void>
    class VecsRegistry : public VecsRegistryBaseClass {

      static const size_t c_segment_size = vtll::front_value< vtll::map< VecsTableSizeMap, E, VeTableSizeDefault > >::value;
      static const size_t c_max_size     = vtll::back_value<  vtll::map< VecsTableSizeMap, E, VeTableSizeDefault > >::value;

    public:
      //use either a given value or the default value from the map
      //if there is not default value in the map, use the default default value
      VecsRegistry(size_t r = 1 << c_max_size) noexcept : VecsRegistryBaseClass() { VecsComponentTable<E>{r}; };
      //...

    };

For a given template entity type *E*, the command *vtll::map< VecsTableSizeMap, E, VeTableSizeDefault >* retrieves the value list from the map. If there is no entry in the map, then the default default value is returned. For the segment size we need the first value which is returned using *vtll::front_value<>*, the maximum size is retrieved using *vtll::back_value<>*. We can use e.g. the max value as default size in the constructor of the class:

    //use either a given value or the default value from the map
    //if there is not default value in the map, use the default default value
    VecsRegistry(size_t r = 1 << c_max_size) noexcept : VecsRegistryBaseClass() { VecsComponentTable<E>{r}; };

Additionally we want the sum of all max sizes to size a list of all entities regardless of their type. So we want to sum up all 1 << c_max_size for all entity types. For turning the exponent into a size we need a function *left_shift_1<exponent>* to do this:

    template<typename T>
  	struct left_shift_1 {
  		using type = std::integral_constant<size_t, 1 << T::value>;
  	};

Also we want a list of all max sizes, which we get through

    vtll::apply_map<VecsTableSizeMap, VecsEntityTypeList, VeTableSizeDefault>

This gives us a list of value lists, which we can turn into type lists using *vtll::transform < ..., vtll::value_to_type >*:

  	using VecsTableMaxSizes = vtll::transform < vtll::apply_map<VecsTableSizeMap, VecsEntityTypeList, VeTableSizeDefault>, vtll::value_to_type>;

We get a list with the second value using *vtll::transform< VecsTableMaxSizes, vtll::back >*, for which we apply the *left_shift_1* function to get the powers of two. Finally we apply the *vtll::sum<>* function to sum up the numbers:

  	using VecsTableMaxSize = vtll::sum< vtll::function< vtll::transform< VecsTableMaxSizes, vtll::back >, left_shift_1 > >;

This is already a number and we can now use this as default value for storing a list of all entities:

    class VecsRegistryBaseClass {

    public:
      VecsRegistryBaseClass( size_t r = VecsTableMaxSize::value ) noexcept; //use as default value

    //...
    };


## Implementation

Implementations use mostly either recursions, parameter packs and/or C++ folding expressions. Some use special command like tuple commands or sizeof...

### Recursions

An example for a recursion is *index_of*:

    namespace detail {
      template<typename, typename>
      struct index_of_impl {};

      template <typename T, template <typename...> typename Seq, typename... Ts>
      struct index_of_impl<Seq<T, Ts...>,T> : std::integral_constant<std::size_t, 0> {};

      template <typename T, typename TOther, template <typename...> typename Seq, typename... Ts>
      struct index_of_impl<Seq<TOther, Ts...>,T>
        : std::integral_constant<std::size_t, 1 + index_of_impl<Seq<Ts...>,T>::value> {};
    }

    template <typename Seq, typename T>
    using index_of = typename detail::index_of_impl<Seq,T>::type; //definition !

    static_assert(index_of< type_list<double, char, bool, double>, char >::value == 1);

The main definition of *index_of* is at the bottom, it is a *struct* taking two parameters. The struct then passes on the parameters to a special implementation version, *index_of_impl* that exists in three versions. The first version

    template<typename, typename>
    struct index_of_impl;

is the *primary template*, a first, incomplete announcement that this type exists and that it uses two template parameters. For the primary template,  two *specializations* are then defined. The first specialization is the special case that the type *T* we were looking for is the *first type* of the current list. Notice that there is only one *typename T* as template parameter, occurring two times. Thus, both must be the same.

    template <typename T, template <typename...> typename Seq, typename... Ts>
    struct index_of_impl<Seq<T, Ts...>,T> : std::integral_constant<std::size_t, 0> {}; //T occurs two times, must be identical

Notice that since this struct uses less template parameters than the next, for *overload resolution*, the compiler will always prefer it (more spezialized) to the next, more general template. So whenever the first template parameter is the one we look for, this struct is chosen.
Also, for storing actual integer values, we derive the struct from a type *std::integral_constant* storing the value 0. This is the start for counting up! The second specialization is the general recursion case, where the first type of the current type list is *not* the type we are looking for, but some other type.

    template <typename T, typename TOther, template <typename...> typename Seq, typename... Ts>
    struct index_of_impl<Seq<TOther, Ts...>,T>
      : std::integral_constant<std::size_t, 1 + index_of_impl<Seq<Ts...>,T>::value> {};

We derive this struct from a std::integral_constant that stores a number that is 1 + the number for the rest of the list. This defines the *recursion*.
In this example we derive the struct itself from std::integral_constant, but usually we use some kind of local type or value to construct the result.

### Parameter Packs

An example for using a C++ parameter pack is given by *to_variant*.

    namespace detail {
      template <typename Seq>
      struct to_variant_impl;

      template <template <typename...> typename Seq, typename... Ts>
      struct to_variant_impl<Seq<Ts...>> {
        using type = std::variant<Ts...>;
      };
    }

    template <typename Seq>
    using to_variant = typename detail::to_variant_impl<Seq>::type;

    static_assert(
      std::is_same_v< to_variant< type_list<double, int, char> >, std::variant<double, int, char> >,
      "The implementation of to_variant is bad");

Here all types are put into a summary variant type, a union like struct that can store all of the given types, and always knows which type it stores. The type list is passed to the impl version, which can map it to a parameter pack Ts..., which can directly be put into the type declaration of std::variant.

    template <template <typename...> typename Seq, typename... Ts> //template parameters
    struct variant_type_impl<Seq<Ts...>> {    //map type list to parameter pack Ts...
      using type = std::variant<Ts...>;       //put parameter pack into std::variant
    };


### Folding Expressions

An example for the use of folding expressions is *has_type*. This tests whether a type list contains a given type *T*.

    namespace detail {
      template<typename Seq, typename T>
      struct has_type_impl;

      template<template <typename...> typename Seq, typename T>
      struct has_type_impl<Seq<>, T> {
        static const bool value = false;
      };

      template<template <typename...> typename Seq, typename... Ts, typename T>
      struct has_type_impl<Seq<Ts...>, T> {
        static const bool value = (std::is_same_v<T, Ts> || ... );  //folding expr
      };
    }

    template <typename Seq, typename T>
    struct has_type {
      static const bool value = detail::has_type_impl<Seq, T>::value;
    };

    static_assert(
      has_type<type_list<double, int, char, double>, char>::value,
        "The implementation of has_type is bad");

The type list arguments are mapped to the parameter pack Ts..., which is used in the folding expression

    static const bool value = (std::is_same_v<T, Ts> || ... );  //folding expr

This compares each type in the pack Ts to the target type T, each comparison is linked to the next with a logical or ||. If at least one of the comparisons evaluates to true, then the whole statement is true, otherwise it is false.
