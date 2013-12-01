class Int: public Term {
public:
  Int (int);

private:
  int val;
}

  Int::Int(int v) {
    val = v;
  }
