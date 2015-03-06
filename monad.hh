// includes

#pragma once

#include "monoid.hh"



// class

template <typename MA>
class Monad;
//    typedef A Type;
//
//    template <typename B>
//    using M = ...;
//
//    template <typename B>
//    M<B> bind(M<A>, Function<A, M<B>>);
//    M<A> mreturn(A);



// functions

template <typename MA, typename A>
MA mreturn(A a)
{
  return Monad<MA>::mreturn(a);
}

template <typename MA, typename MB, typename A>
MB operator >>= (MA ma, Function<A, MB> f)
{
  return Monad<MA>::bind(ma, f);
}

template <typename MA, typename MB>
MB operator >> (MA ma, MB mb)
{
  typedef typename Monad<MA>::Type A;
  Function<A, MB> f = [=](A){ return mb; };
  return ma >>= f;
}



// instances

template <typename A>
class Monad<Vec<A>>
{
  public:
    typedef A Type;

    static Vec<A> mreturn(A a)
    {
      return Vec<A> { a };
    }

    template <typename B>
    static Vec<B> bind(Vec<A> as, Function<A, Vec<B>> f)
    {
      Vec<Vec<B>> bs;
      std::back_insert_iterator<Vec<Vec<B>>> bi(bs);
      std::transform(as.begin(), as.end(), bi, f);
      return concat<Vec<A>>(bs);
    }
};

template <typename A>
class Monad<List<A>>
{
  public:
    typedef A Type;

    static List<A> mreturn(A a)
    {
      return List<A> { a };
    }

    template <typename B>
    static List<B> bind(List<A> as, Function<A, List<B>> f)
    {
      List<List<B>> bs;
      std::back_insert_iterator<List<List<B>>> bi(bs);
      std::transform(as.begin(), as.end(), bi, f);
      return concat<List<A>>(bs);
    }
};

template <typename A>
class Monad<Maybe<A>>
{
  public:
    typedef A Type;

    static Maybe<A> mreturn(A a)
    {
      return Maybe<A>(a);
    }

    template <typename B>
    static Maybe<B> bind(Maybe<A> ma, Function<A, Maybe<B>> f)
    {
      return ma ? f(*ma) : Maybe<B>();
    }
};

template <typename A, typename B>
class Monad<Either<A, B>>
{
  public:
    typedef B Type;

    static Either<A, B> mreturn(B b)
    {
      return Either<A, B>(b);
    }

    template <typename C>
    static Either<A, C> bind(Either<A, B> mb, Function<B, Either<A, C>> f)
    {
      A* a = boost::get<A>(&mb);
      B* b = boost::get<B>(&mb);
      return a ? *a : f(*b);
    }
};

template <typename A, typename B>
class Monad<Function<A, B>>
{
  public:
    typedef B Type;

    static Function<A, B> mreturn(B b)
    {
      return [=](A){ return b; };
    }

    template <typename C>
    static Function<A, C> bind(Function<A, B> mb, Function<B, Function<A, C>> f)
    {
      return [=](A a){ return f(mb(a))(a); };
    }
};
