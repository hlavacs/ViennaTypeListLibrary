# The Vienna Type List Library (VTLL)
The Vienna Type List Library (VTLL) is a collection of C++20 type list algorithms, mostly written by Prof. Helmut Hlavacs, University of Vienna.

Its starting point is a post from Nils Deppe (https://nilsdeppe.com/posts/tmpl-part2). The static_assert statement from this post and the way name space detail is used.

Using the library simply means to include the single include file VTLL.h, and using the structs in the namespace vtll. Examples for its use are given by static_assert statements. For example the MSVC immediately indicates whether a static_assert evaluates to true, by unserlining false statements with red wiggles. So if its not underlined, the statement is true. This applies to all static_asserts in the library. Interestingly, this may fail if  you use requires instead of std::conditional, an example for this follows below.

For building the project for MSVC just run the msvc.bat batch file.
