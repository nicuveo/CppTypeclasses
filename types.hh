// includes

#pragma once

#include <boost/optional.hpp>
#include <boost/variant.hpp>
#include <string>
#include <vector>
#include <list>
#include <map>



// types

template <typename A>
using Vec = std::vector<A>;

template <typename A>
using List = std::list<A>;

template <typename A, typename B>
using Map = std::map<A, B>;

template <typename A>
using Maybe = boost::optional<A>;

template <typename A, typename B>
using Either = boost::variant<A, B>;

template <typename A, typename B>
using Function = std::function<B(A)>;

template <typename A>
using Endomorphism = Function<A, A>;

typedef std::string String;



// functions

template <typename A, typename B, typename C>
Function<A, C> compose(Function<B, C> f, Function<A, B> g)
{
  using namespace std::placeholders;
  return std::bind(f, std::bind(g, _1));
}
