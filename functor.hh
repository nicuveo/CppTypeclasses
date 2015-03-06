// includes

#pragma once

#include "types.hh"



// class

template <typename FA>
class Functor;

// template <typename B> using F = ...;
// template <typename B> static F<B> fmap(Fun<B>, FA);



// functions

template <typename FA, typename A, typename B>
typename Functor<FA>::template F<B>
fmap(Function<A, B> f, FA fa)
{
  return Functor<FA>::template fmap<B>(f, fa);
}



// instances

template <typename A>
class Functor<Vec<A>>
{
  public:
    template <typename B>
    using F = Vec<B>;

    template <typename B>
    static Vec<B> fmap(Function<A, B> f, Vec<A> as)
    {
      Vec<B> bs;
      std::back_insert_iterator<Vec<B>> bi(bs);
      std::transform(as.begin(), as.end(), bi, f);
      return bs;
    }
};

template <typename A>
class Functor<List<A>>
{
  public:
    template <typename B>
    using F = List<B>;

    template <typename B>
    static List<B> fmap(Function<A, B> f, List<A> as)
    {
      List<B> bs;
      std::back_insert_iterator<List<B>> bi(bs);
      std::transform(as.begin(), as.end(), bi, f);
      return bs;
    }
};

template <typename K, typename A>
class Functor<Map<K, A>>
{
  public:
    template <typename B>
    using F = Map<K, B>;

    template <typename B>
    static Map<K, B> fmap(Function<A, B> f, Map<K, A> as)
    {
      Map<K, B> bs;
      for (auto ka : as)
        bs.insert(ka.first, f(ka.second));
      return bs;
    }
};

template <typename A>
class Functor<Maybe<A>>
{
  public:
    template <typename B>
    using F = Maybe<B>;

    template <typename B>
    static F<B> fmap(Function<A, B> f, Maybe<A> ma)
    {
      return ma ? f(*ma) : F<B>();
    }
};

template <typename A, typename B>
class Functor<Either<A, B>>
{
  public:
    template <typename C>
    using F = Either<A, C>;

    template <typename C>
    static F<C> fmap(Function<B, C> f, Either<A, B> ab)
    {
      A* a = boost::get<A>(ab);
      B* b = boost::get<B>(ab);
      return a ? *a : f(*b);
    }
};

template <typename A, typename B>
class Functor<Function<A, B>>
{
  public:
    template <typename C>
    using F = Function<A, C>;

    template <typename C>
    static F<C> fmap(Function<B, C> f, Function<A, B> ab)
    {
      return compose(f, ab);
    }
};
