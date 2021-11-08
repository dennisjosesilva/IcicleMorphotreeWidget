#pragma once 

#include "IcicleMorphotreeWidget/Filtering/TreeFiltering.hpp"

namespace IcicleMorphotreeWidget 
{
  class AreaTreeFiltering : public TreeFiltering
  {
  public:
    using uint8 = typename TreeFiltering::uint8;
    using uint32 = typename TreeFiltering::uint32;
    using MTree = typename TreeFiltering::MTree;
    using NodePtr = typename TreeFiltering::NodePtr;

    AreaTreeFiltering(uint32 areaThreshold);

    void ifilter(MTree &tree) const override;

    inline uint32 &areaThres() { return areaThres_; }
    inline uint32 areaThres() const { return areaThres_; }
    inline void areaThres(uint32 val) { areaThres_ = val; }

  protected:
    uint32 areaThres_;
  };
}