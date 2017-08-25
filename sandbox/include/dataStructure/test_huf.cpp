#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

static const int MAXCHAR = 256;

int wc[MAXCHAR];
vector<char> input;

class Node {
friend class Cmp;
protected:
  char c;
  int w;
  Node *l, *r;
  
  
public:
  Node(char c_, int w_) : c(c_), w(w_) {
    l = NULL;
    r = NULL;
  };

  Node(Node *l_, Node *r_) : l(l_), r(r_) {
    w = l->w + r->w;
  };

  ~Node() {
    delete l;
    delete r;
  };

  void print(string s) {
    if (l) {
      l->print(s + '0');
      r->print(s + '1');
    } else {
      cout << s << " :: '" << c << "' (" << w << ")" << endl;
    }
  };
};

class Cmp {
  public:
    bool operator() (const Node * lhs, const Node * rhs) const {
      return (lhs->w > rhs->w);
    };
};

priority_queue<Node*, vector<Node*>, Cmp> heap;

int main(){
  string s;
  Node *l, *r;

  while(getline(cin, s)) {
    if (!s.empty()) {
      input.push_back('\n');
    }
    for(auto c : s) {
      input.push_back(c);
    }
  }

  for(auto c : input) {
    wc[c]++;
  }

  for(int i = 0; i < MAXCHAR; ++i) {
    if (wc[i] > 0) {
      heap.push(new Node((char) i, wc[i]));
    }
  }

  while(heap.size() > 1) {
    l = heap.top();
    heap.pop();
    r = heap.top();
    heap.pop();
    heap.push(new Node(l, r));
  }


  heap.top()->print("");

  l = heap.top();
  heap.pop();
  delete l;

  return 0;
}

