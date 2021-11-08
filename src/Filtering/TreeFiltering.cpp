#include "IcicleMorphotreeWidget/Filtering/TreeFiltering.hpp"

namespace IcicleMorphotreeWidget
{
  TreeFiltering::TreeFiltering()
  {}

  TreeFiltering::MTree 
  TreeFiltering::filter(const MTree &tree) const 
  {
    MTree copiedTree = tree.copy();
    ifilter(copiedTree);
    return copiedTree;
  }
}