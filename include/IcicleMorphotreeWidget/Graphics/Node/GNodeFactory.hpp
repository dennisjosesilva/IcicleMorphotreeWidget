#pragma once 

#include "IcicleMorphotreeWidget/Graphics/Node/GNode.hpp"
#include <morphotree/tree/mtree.hpp>

namespace IcicleMorphotreeWidget 
{
  // Forward declaration
  class IcicleMorphotreeWidget;

  class GNodeFactory
  {
  public:
    using uint8 = morphotree::uint8;
    using MTree = morphotree::MorphologicalTree<uint8>;
    using MTreeNodePtr = typename MTree::NodePtr;

    GNodeFactory(IcicleMorphotreeWidget *treeVis=nullptr);

    inline void setTreeVisualiser(IcicleMorphotreeWidget *t) { treeVis_ = t; }

    virtual GNode *create(MTreeNodePtr mnode=nullptr) = 0;

  protected:
    IcicleMorphotreeWidget *treeVis_;
  };

  class FixedColorGNodeFactory : public GNodeFactory
  {
  public:
    FixedColorGNodeFactory(IcicleMorphotreeWidget *treeVis=nullptr);
    
    GNode *create(MTreeNodePtr mnode=nullptr) override;  
  };

  class GradientGNodeFactory : public GNodeFactory
  {
  public:
    GradientGNodeFactory(IcicleMorphotreeWidget *treeVis=nullptr,
      float gradientProportion=0.4f);
    
    GNode *create(MTreeNodePtr mnode=nullptr) override;

    inline float  gradientProportion() const { return gradientProportion_; }
    inline float& gradientProportion() { return gradientProportion_; }
    inline void gradientProportion(float val) { gradientProportion_ = val; }

  protected:
    float gradientProportion_;
  };
}