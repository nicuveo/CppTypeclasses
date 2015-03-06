// includes

#pragma once

#include "types.hh"



// class

template <typename A>
class Monoid;

// static A empty();
// static A append(A, A);



// functions

template <typename A>
inline A empty()
{
  return Monoid<A>::empty();
}

template <typename A>
inline A append(A const& x, A const& y)
{
  return Monoid<A>::append(x, y);
}

template <typename A, typename I>
inline A concat(I b, I e)
{
  return std::accumulate(b, e, empty<A>(), append<A>);
}

template <typename A, typename C>
inline A concat(C const& xs)
{
  return concat<A>(xs.begin(), xs.end());
}



// instances

template <typename A>
class Monoid<Vec<A>>
{
  public:
    static Vec<A> empty()
    {
      return Vec<A>();
    }

    static Vec<A> append(Vec<A> const& x, Vec<A> const& y)
    {
      Vec<A> res;
      res.reserve(x.size() + y.size());
      res.insert(res.end(), x.begin(), x.end());
      res.insert(res.end(), y.begin(), y.end());
      return res;
    }
};

template <typename A>
class Monoid<List<A>>
{
  public:
    static List<A> empty()
    {
      return List<A>();
    }

    static List<A> append(List<A> const& x, List<A> const& y)
    {
      List<A> res;
      res.insert(res.end(), x.begin(), x.end());
      res.insert(res.end(), y.begin(), y.end());
      return res;
    }
};

template <typename A, typename B>
class Monoid<Map<A, B>>
{
  public:
    static Map<A, B> empty()
    {
      return Map<A, B>();
    }

    static Map<A, B> append(Map<A, B> const& x, Map<A, B> const& y)
    {
      Map<A, B> res;
      res.insert(x.begin(), x.end());
      res.insert(y.begin(), y.end());
      return res;
    }
};

template <typename A>
class Monoid<Endomorphism<A>>
{
  public:
    static Endomorphism<A> empty()
    {
      return id;
    }

    static Endomorphism<A> append(Endomorphism<A> const& f, Endomorphism<A> const& g)
    {
      return compose(f, g);
    }
};

template <>
class Monoid<String>
{
  public:
    static String empty()
    {
      return String();
    }

    static String append(String const& a, String const& b)
    {
      return a + b;
    }
};
