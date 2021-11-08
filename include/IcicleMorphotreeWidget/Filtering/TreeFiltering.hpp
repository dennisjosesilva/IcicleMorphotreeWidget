#pragma once 

#include <morphotree/core/alias.hpp>
#include <morphotree/tree/mtree.hpp>

namespace IcicleMorphotreeWidget
{
  class TreeFiltering
  {
  public:
    using uint8 = morphotree::uint8;
    using uint32 = morphotree::uint32;
    using MTree = morphotree::MorphologicalTree<uint8>;
    using NodePtr = typename MTree::NodePtr;

    TreeFiltering();
    MTree filter(const MTree &tree) const;
    virtual void ifilter(MTree &tree) const = 0;
  };
}