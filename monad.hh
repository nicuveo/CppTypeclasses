// includes

#pragma once

#include "monoid.hh"



// class

template <typename MA>
class Monad;

// typedef A Type;
// M<A> mreturn(A);
// template <typename B> using M = ...;
// template <typename B> static M<B> bind(M<A>, Function<A, M<B>>);



// functions

template <typename MA, typename A>
MA mreturn(A const& a)
{
  return Monad<MA>::mreturn(a);
}

template <typename MA, typename MB, typename A>
MB operator >>= (MA const& ma, Function<A const&, MB> const& f)
{
  return Monad<MA>::bind(ma, f);
}

template <typename MA, typename MB>
MB operator >> (MA const& ma, MB const& mb)
{
  typedef typename Monad<MA>::Type A;
  Function<A const&, MB> f = [=](A const&){ return mb; };
  return ma >>= f;
}



// instances

template <typename A>
class Monad<Vec<A>>
{
  public:
    typedef A Type;

    static Vec<A> mreturn(A const& a)
    {
      return Vec<A> { a };
    }

    template <typename B>
    static Vec<B> bind(Vec<A> const& as,
                       Function<A const&, Vec<B>> const& f)
    {
      Vec<Vec<B>> bs;
      bs.reserve(as.size());
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

    static List<A> mreturn(A const& a)
    {
      return List<A> { a };
    }

    template <typename B>
    static List<B> bind(List<A> const& as,
                        Function<A const&, List<B>> const& f)
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

    static Maybe<A> mreturn(A const& a)
    {
      return Maybe<A>(a);
    }

    template <typename B>
    static Maybe<B> bind(Maybe<A> const& ma,
                         Function<A const&, Maybe<B>> const& f)
    {
      return ma ? f(*ma) : Maybe<B>();
    }
};

template <typename A, typename B>
class Monad<Either<A, B>>
{
  public:
    typedef B Type;

    static Either<A, B> mreturn(B const& b)
    {
      return Either<A, B>(b);
    }

    template <typename C>
    static Either<A, C> bind(Either<A, B> const& mb,
                             Function<B const&, Either<A, C>> const& f)
    {
      A const* a = boost::get<A>(&mb);
      B const* b = boost::get<B>(&mb);
      return a ? *a : f(*b);
    }
};

template <typename A, typename B>
class Monad<Function<A const&, B>>
{
  public:
    typedef B Type;

    static Function<A const&, B> mreturn(B const& b)
    {
      return [=](A const&){ return b; };
    }

    template <typename C>
    static Function<A const&, C> bind(Function<A const&, B> const& mb,
                                      Function<B const&, Function<A const&, C>> const& f)
    {
      return [=](A a){ return f(mb(a))(a); };
    }
};
