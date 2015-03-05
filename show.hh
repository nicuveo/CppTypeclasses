// includes

#pragma once

#include <boost/lexical_cast.hpp>
#include "types.hh"



// class

template <typename A>
class Show
{
  public:
    static String show(A x)
    {
      return boost::lexical_cast<String>(x);
    }
};



// functions

template <typename A>
String show(A x)
{
  return Show<A>::show(x);
}



// instances

template <typename A>
class Show<Vec<A>>
{
  public:
    static String show(Vec<A> xs)
    {
      String res = "";
      for (A x : xs)
        res += ", " + Show<A>::show(x);
      return "[" + res.erase(0, 2) + "]";
    }
};

template <typename A>
class Show<List<A>>
{
  public:
    static String show(List<A> xs)
    {
      String res = "";
      for (A x : xs)
        res += ", " + Show<A>::show(x);
      return "[" + res.erase(0, 2) + "]";
    }
};

template <typename A, typename B>
class Show<Map<A, B>>
{
  public:
    static String show(List<A> xs)
    {
      String res = "";
      for (auto x : xs)
        res += ", " + Show<A>::show(x.first) + ": " + Show<B>::show(x.second);
      return "{" + res.erase(0, 2) + "}";
    }
};

template <typename A>
class Show<Maybe<A>>
{
  public:
    static String show(Maybe<A> x)
    {
      return x ? "Just " + Show<A>::Show::show(*x) : "Nothing";
    }
};

template <typename A, typename B>
class Show<Either<A, B>>
{
  public:
    static String show(Either<A, B> x)
    {
      return boost::apply_visitor(EitherShow(), x);
    }

  private:
    class EitherShow : public boost::static_visitor<String>
    {
      public:
        String operator()(A a) const
        {
          return "Left " + Show<A>::show(a);
        }
        String operator()(B b) const
        {
          return "Right " + Show<B>::show(b);
        }
    };
};
