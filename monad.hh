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
MB
operator >>= (MA ma, Function<A, MB> f)
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

    template <typename B>
    using M = Vec<B>;

    static M<A> mreturn(A a)
    {
      return M<A> { a };
    }

    template <typename B>
    static M<B> bind(Vec<A> as, Function<A, M<B>> f)
    {
      M<M<B>> bs;
      std::back_insert_iterator<M<M<B>>> bi(bs);
      std::transform(as.begin(), as.end(), bi, f);
      return concat<M<A>>(bs);
    }
};

template <typename A>
class Monad<List<A>>
{
  public:
    typedef A Type;

    template <typename B>
    using M = List<B>;

    static M<A> mreturn(A a)
    {
      return M<A> { a };
    }

    template <typename B>
    static M<B> bind(M<A> as, Function<A, M<B>> f)
    {
      M<M<B>> bs;
      std::back_insert_iterator<M<M<B>>> bi(bs);
      std::transform(as.begin(), as.end(), bi, f);
      return concat<M<A>>(bs);
    }
};

template <typename A>
class Monad<Maybe<A>>
{
  public:
    typedef A Type;

    template <typename B>
    using M = Maybe<B>;

    static M<A> mreturn(A a)
    {
      return M<A>(a);
    }

    template <typename B>
    static M<B> bind(M<A> ma, Function<A, M<B>> f)
    {
      return ma ? f(*ma) : M<B>();
    }
};

template <typename A, typename B>
class Monad<Either<A, B>>
{
  public:
    typedef B Type;

    template <typename C>
    using M = Either<A, C>;

    static M<B> mreturn(B b)
    {
      return M<B>(b);
    }

    template <typename C>
    static M<C> bind(M<B> mb, Function<B, M<C>> f)
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

    template <typename C>
    using M = Function<A, C>;

    static M<B> mreturn(B b)
    {
      return [=](A){ return b; };
    }

    template <typename C>
    static M<C> bind(M<B> mb, Function<B, M<C>> f)
    {
      return [=](A a){ return f(mb(a))(a); };
    }
};
