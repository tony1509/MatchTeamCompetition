#include <gecode/int.hh>
#include <gecode/search.hh>

using namespace Gecode;

class MatchTeam : public Space {
protected:
  IntVarArray l;
public:
  MatchTeam(void) : l(*this, 40, 0, 10) {

    IntVarArgs s(10);

    for (int i = 0; i < 10; i++)
    {
        // every column distinct
        IntVarArgs x(4);
        x[0] = l[4*i + 0];
        x[1] = l[4*i + 1];
        x[2] = l[4*i + 2];
        x[3] = l[4*i + 3];
        distinct(*this, x);

        // each element appears 4 times
        Gecode::count(*this, l, i, IRT_EQ, 4);

        IntArgs c({1000, 100, 10, 1});
        // Save finger print for each column
        linear(*this, c, x, IRT_EQ, s[i]);
    }

    distinct(*this, s);

    // post branching
    branch(*this, l, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
  }
  // search support
  MatchTeam(MatchTeam& s) : Space(s) {
    l.update(*this, s.l);
  }
  virtual Space* copy(void) {
    return new MatchTeam(*this);
  }
  // print solution
  void print(void) const {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << l[4*i+j] << std::endl;
        }
    }
  }
};

// main function
int main(int argc, char* argv[]) {
  // create model and search engine
  MatchTeam* m = new MatchTeam;
  BAB<MatchTeam> e(m);
  delete m;
  // search and print all solutions
  while (MatchTeam* s = e.next()) {
    s->print(); delete s;
  }
  return 0;
}