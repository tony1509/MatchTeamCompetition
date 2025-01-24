#include <gecode/int.hh>
#include <gecode/search.hh>

using namespace Gecode;

class MatchTeam : public Space {
protected:
  IntVarArray l;
  IntVarArray s;
public:
  MatchTeam(void) : l(*this, 40, 0, 10), s(*this, 10, 0, 9999) {

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
        count(*this, l, i, IRT_EQ, 4);

        rel(*this, s[i] == 1000*x[0] + 100*x[1] + 10*x[2] + 1*x[3]);
    }

    distinct(*this, s);

    // post branching
    branch(*this, l, INT_VAR_SIZE_MIN(), INT_VAL_RND());
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
        std::cout << l[4*i + 0] << l[4*i + 1] << l[4*i + 2] << l[4*i + 3] << std::endl;
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
    s->print(); delete s; break;
  }
  return 0;
}