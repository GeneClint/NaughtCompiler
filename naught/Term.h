// Looking at class this is an "each of type" as explained in 341,
// there are a lot of shitty ways to represent this in c++, and having
// a class that basically does nothing and then asking typeof seems to
// be the best solution
// reference: http://astitcher.github.io/ACCU2012/slides/algebraic.html
#ifndef __TERM_H
#define __TERM_H

class Term {
public:
  virtual ~Term() {}
};

#endif // __TERM_H
