#include "IcicleMorphotreeWidget/Filtering/AreaTreeFiltering.hpp"

#include <morphotree/attributes/areaComputer.hpp>

namespace IcicleMorphotreeWidget
{
  AreaTreeFiltering::AreaTreeFiltering(uint32 areaThreshold)
    :TreeFiltering{}, areaThres_{areaThreshold}
  {}

  void AreaTreeFiltering::ifilter(MTree &tree) const
  {
    using AreaComputer = morphotree::AreaComputer<uint8>;

    std::vector<uint32> area = std::make_unique<AreaComputer>()
      ->computeAttribute(tree);

    tree.idirectFilter([this, &area](NodePtr node){ 
      return area[node->id()] >= areaThres_;
    });
  }
}