// includes

#pragma once

#include <boost/lexical_cast.hpp>
#include "types.hh"



// class

template <typename A>
class Show
{
  public:
    static String show(A const& x)
    {
      return boost::lexical_cast<String>(x);
    }
};



// functions

template <typename A>
inline String show(A const& x)
{
  return Show<A>::show(x);
}



// instances

template <>
class Show<String>
{
  public:
  static String show(String const& s)
  {
    return '"' + s + '"';
  }
};

template <typename A>
class Show<Vec<A>>
{
  public:
    static String show(Vec<A> const& xs)
    {
      String res = "";
      for (auto const& x : xs)
        res += ", " + Show<A>::show(x);
      return "[" + res.erase(0, 2) + "]";
    }
};

template <typename A>
class Show<List<A>>
{
  public:
    static String show(List<A> const& xs)
    {
      String res = "";
      for (auto const& x : xs)
        res += ", " + Show<A>::show(x);
      return "[" + res.erase(0, 2) + "]";
    }
};

template <typename A, typename B>
class Show<Map<A, B>>
{
  public:
    static String show(List<A> const& xs)
    {
      String res = "";
      for (auto const& x : xs)
        res += ", " + Show<A>::show(x.first) + ": " + Show<B>::show(x.second);
      return "{" + res.erase(0, 2) + "}";
    }
};

template <typename A>
class Show<Maybe<A>>
{
  public:
    static String show(Maybe<A> const& x)
    {
      return x ? "Just " + Show<A>::Show::show(*x) : "Nothing";
    }
};

template <typename A, typename B>
class Show<Either<A, B>>
{
  public:
    static String show(Either<A, B> const& x)
    {
      return boost::apply_visitor(EitherShow(), x);
    }

  private:
    class EitherShow : public boost::static_visitor<String>
    {
      public:
        String operator()(A const& a) const
        {
          return "Left " + Show<A>::show(a);
        }
        String operator()(B const& b) const
        {
          return "Right " + Show<B>::show(b);
        }
    };
};
