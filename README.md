# C++ Typeclasses

Haskell's typeclasses are akin to what OO languages call *interfaces*,
or even to *abstract classes*: they define a "contract", sometimes offer
a default implementation, and even share some common vocabulary: a type
that is an instance of a typeclass is said to be "deriving" it.

However, there's one big difference: one can implement a typeclass for
an existing type without modifying it, while a class has to explicitly
declare which interfaces it implements (except in Go, AFAIK).

This repository is an experiment: trying to come up with a working way
to have Haskell-like typeclasses in C++. It... kinda works.

Of course, don't use that in real life.

## Types

``` c++
// "template <typename A>" omitted for readability

using Vec          = std::vector<A>;
using List         = std::list<A>;
using Map          = std::map<A, B>;
using Maybe        = boost::optional<A>;
using Either       = boost::variant<A, B>;
using Function     = std::function<B(A)>;
using Endomorphism = Function<A, A>;

typedef std::string String;
```

Either can't handle having the same type for A and B, due to the use of
`boost::variant`.

## Show

``` Haskell
show :: a -> String
```

Works by default for any type that works with `boost::lexical_cast`.
Implemented for all types except Function and Endomorphism.

## Monoid

``` Haskell
empty  :: a
append :: a -> a -> a
concat :: Container c => c a -> a
```

Implemented for Vec, List, Map, String, and Endomorphism.  Containers
accepted by `concat` are all standard containers that have a `begin` and
an `end` method.

## Functor

``` Haskell
fmap :: (a -> b) -> f a -> f b
```

Implemented for all types except Endomorphism and String.
Function composition is handled via `std::bind`.

## Monad

``` Haskell
mreturn :: a -> m a
(>>=)   :: m a -> (a -> m b) -> m b
(>>)    :: m a -> m b -> m b
```

Yes, both are valid and overloadable C++ operators. :)

However, `(>>=)` is right-associative, which means we have to add parens
everywhere. And `fail` is yet to be implemented: I haven't yet found a
proper way to specify a default implementation for one function only.
