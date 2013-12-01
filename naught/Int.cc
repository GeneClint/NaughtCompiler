#include <string>
#include <Term.cc>

class Int: public Term {
public:
  Int (int) : Term ();
  Int (string) : Term ();
  int getValue() const;
private:
  int val;
};

Int::Int(string v) {
  val = std::stoi( v );
}

Int::Int (int v) {
  val = v;
}

Int::int getValue() const {
  return val;
}
