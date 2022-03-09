#pragma once 

#include "IcicleMorphotreeWidget/Graphics/Node/GNode.hpp"
#include <morphotree/tree/mtree.hpp>

namespace IcicleMorphotreeWidget 
{
  // Forward declaration
  class IcicleMorphotreeWidget;

  enum GNodeStyle 
  {
    GradientColor,
    BilinearGradientColor,
    FixedColor    
  };

  class GNodeFactory
  {
  public:
    using uint8 = morphotree::uint8;
    using MTree = morphotree::MorphologicalTree<uint8>;
    using MTreeNodePtr = typename MTree::NodePtr;

    GNodeFactory(IcicleMorphotreeWidget *treeVis=nullptr);

    inline void setTreeVisualiser(IcicleMorphotreeWidget *t) { treeVis_ = t; }

    virtual GNodeStyle style() const = 0;

    virtual GNode *create(MTreeNodePtr mnode=nullptr) = 0;

  protected:
    IcicleMorphotreeWidget *treeVis_;
  };

  class FixedColorGNodeFactory : public GNodeFactory
  {
  public:
    FixedColorGNodeFactory(IcicleMorphotreeWidget *treeVis=nullptr);
    
    GNodeStyle style() const override { return FixedColor; }

    GNode *create(MTreeNodePtr mnode=nullptr) override;  
  };

  class GradientGNodeFactory : public GNodeFactory
  {
  public:
    GradientGNodeFactory(IcicleMorphotreeWidget *treeVis=nullptr,
      float gradientProportion=0.6f);
        
    inline float  gradientProportion() const { return gradientProportion_; }
    inline float& gradientProportion() { return gradientProportion_; }
    inline void setGradientProportion(float val) { gradientProportion_ = val; }

    GNodeStyle style() const override { return GradientColor; }

  protected:
    float gradientProportion_;
  };


  class HGradientGNodeFactory : public GradientGNodeFactory
  {
  public:
    HGradientGNodeFactory(IcicleMorphotreeWidget *treeVis = nullptr, 
      float gradientProportion = 0.6f);
    
    GNode *create(MTreeNodePtr mnode=nullptr) override;
  };

  class VGradientGNodeFactory : public GradientGNodeFactory
  {
  public:
    VGradientGNodeFactory(IcicleMorphotreeWidget *treeVis = nullptr, 
      float gradientProportion = 0.6f);

    GNode *create(MTreeNodePtr mnode = nullptr) override;
  };
}