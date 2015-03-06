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
fmap(Function<A const&, B> const& f, FA const& fa)
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
    static Vec<B> fmap(Function<A const&, B> const& f, Vec<A> const& as)
    {
      Vec<B> bs;
      bs.reserve(as.size());
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
    static List<B> fmap(Function<A const&, B> const& f, List<A> const& as)
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
    static Map<K, B> fmap(Function<A const&, B> const& f, Map<K, A> const& as)
    {
      Map<K, B> bs;
      for (auto const& ka : as)
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
    static F<B> fmap(Function<A const&, B> const& f, Maybe<A> const& ma)
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
    static F<C> fmap(Function<B const&, C> const& f, Either<A, B> const& ab)
    {
      A const* a = boost::get<A>(ab);
      B const* b = boost::get<B>(ab);
      return a ? *a : f(*b);
    }
};

template <typename A, typename B>
class Functor<Function<A const&, B>>
{
  public:
    template <typename C>
    using F = Function<A const&, C>;

    template <typename C>
    static F<C> fmap(Function<B const&, C> const& f, Function<A const&, B> const& ab)
    {
      return compose(f, ab);
    }
};
