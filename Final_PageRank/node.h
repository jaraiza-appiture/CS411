#include <vector>
using std::vector;

class node
{
public:
    node();
    node(int id); // constructor

    int id;
    int visit_count;
    vector<int> outlinks;
};

// bool operator<(const node& lhs, const node& rhs)
// {
//   return lhs.visit_count < rhs.visit_count;
// }
struct LessThanByVisit
{
  bool operator()(const node& lhs, const node& rhs) const
  {
    return lhs.visit_count < rhs.visit_count;
  }
};