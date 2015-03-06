// includes

#include "show.hh"
#include "monoid.hh"
#include "functor.hh"
#include "monad.hh"



// functions

int ef0(int x)
{
  return x + 1;
}

Vec<int> ef1(int x)
{
  return Vec<int> { x - 1, x, x + 1 };
}

Maybe<int> ef2(int x)
{
  return x % 2 ? x : Maybe<int>();
}

Either<String, int> ef3(int x)
{
  return x % 2 == 0
    ? Either<String, int>(x)
    : Either<String, int>("not even");
}



// main

int main()
{
  Vec<int> va = mreturn<Vec<int>>(10);
  Maybe<int> ma = 3;
  Maybe<int> mb;
  Either<String, int> ea = 42;
  Either<String, int> eb = 43;
  Function<int const&, int                 > f0 = ef0;
  Function<int const&, Vec<int>            > f1 = ef1;
  Function<int const&, Maybe<int>          > f2 = ef2;
  Function<int const&, Either<String, int> > f3 = ef3;
  auto f = fmap(f3, f0);

  std::cout << show(fmap(f0, va))       << std::endl
            << show(fmap(f0, ma))       << std::endl
            << show(fmap(f0, mb))       << std::endl
            << show(ma >> mb)           << std::endl
            << show(ea >>= f3)          << std::endl
            << show(eb >>= f3)          << std::endl
            << show((ma >>= f2) >>= f2) << std::endl
            << show((va >>= f1) >>= f1) << std::endl;
}
