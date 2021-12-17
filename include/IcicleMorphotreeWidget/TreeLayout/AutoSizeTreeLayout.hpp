#pragma once 

#include <morphotree/tree/mtree.hpp>
#include <morphotree/core/alias.hpp>

#include "IcicleMorphotreeWidget/Graphics/Node/GNodeFactory.hpp"
#include "IcicleMorphotreeWidget/TreeLayout/TreeLayout.hpp"

#include <vector>

namespace IcicleMorphotreeWidget
{
  class IcicleMorphotreeWidget;

  class AutoSizeTreeLayout : public TreeLayout 
  {
  public:
    using uint8 = morphotree::uint8;
    using MTree = morphotree::MorphologicalTree<uint8>;
    using NodePtr = typename MTree::NodePtr;

    AutoSizeTreeLayout(
      GNodeFactoryPtr nodeFactory=std::make_unique<GradientGNodeFactory>(),
      float marginTop = 20.f,
      float marginBottom = 20.f);
    
    void parseTree(const MTree &tree);
    std::vector<float> computeNormalisedArea(const MTree &tree);

    inline float unitHeight() const { return unitHeight_; }

    qreal computeUnitHeightFromTheTree(const MTree &tree) const;

    inline TreeLayoutType type() const override { return TreeLayoutType::AutoSize; }

  private:
    qreal unitHeight_;
  };

}