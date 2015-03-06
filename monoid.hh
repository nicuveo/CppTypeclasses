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
A empty()
{
  return Monoid<A>::empty();
}

template <typename A>
A append(A x, A y)
{
  return Monoid<A>::append(x, y);
}

template <typename A, typename I>
A concat(I b, I e)
{
  return std::accumulate(b, e, empty<A>(), append<A>);
}

template <typename A, typename C>
A concat(C xs)
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

    static Vec<A> append(Vec<A> x, Vec<A> y)
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

    static List<A> append(List<A> x, List<A> y)
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

    static Map<A, B> append(Map<A, B> x, Map<A, B> y)
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

    static Endomorphism<A> append(Endomorphism<A> f, Endomorphism<A> g)
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

    static String append(String a, String b)
    {
      return a + b;
    }
};
