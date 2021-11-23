#pragma once

#include <morphotree/tree/mtree.hpp>
#include <morphotree/core/alias.hpp>

#include "IcicleMorphotreeWidget/Graphics/Node/GNodeFactory.hpp"

#include <vector>

namespace IcicleMorphotreeWidget
{
  class IcicleMorphotreeWidget;    

  class TreeLayout
  {
  public:
    using uint8 = morphotree::uint8;
    using MTree = morphotree::MorphologicalTree<uint8>;
    using NodePtr = typename MTree::NodePtr;
    using GNodeFactoryPtr = std::unique_ptr<GNodeFactory>;

    TreeLayout(
      GNodeFactoryPtr nodeFactory=std::make_unique<GradientGNodeFactory>(),
      float marginTop = 20.f,
      float marginBottom = 20.f);

    virtual void parseTree(const MTree &tree) = 0;

    inline void setTreeVis(IcicleMorphotreeWidget *t) { gnodeFactory_->setTreeVisualiser(t); treeVis_ = t; }

    inline void setGNodeFactory(GNodeFactoryPtr f) { gnodeFactory_ = std::move(f); }

  protected:
    IcicleMorphotreeWidget *treeVis_;
    GNodeFactoryPtr gnodeFactory_;
    float marginBottom_;
    float marginTop_;
  };

  class FixedHeightTreeLayout : public TreeLayout
  {
  public:
    using uint8 = morphotree::uint8;
    using MTree = morphotree::MorphologicalTree<uint8>;
    using NodePtr = typename MTree::NodePtr;

    FixedHeightTreeLayout(
      GNodeFactoryPtr nodeFactory=std::make_unique<GradientGNodeFactory>(),
      float marginTop = 20.f,
      float marginBotton = 20.f,
      float height = 5.0f);

    void parseTree(const MTree &tree);

    std::vector<float> computeNormalisedArea(const MTree &tree);

    inline float& height() { return height_; }
    inline float height() const { return height_; }
    inline void setHeight(float height) { height_ = height; }

  private:
    float height_;   
  };

  class GrayscaleBasedHeightTreeLayout : public TreeLayout
  {
  public:
    using uint8 = morphotree::uint8;
    using MTree = morphotree::MorphologicalTree<uint8>;
    using NodePtr = typename MTree::NodePtr;

    GrayscaleBasedHeightTreeLayout(
      GNodeFactoryPtr nodeFactory=std::make_unique<GradientGNodeFactory>(),
      float marginTop = 20.f,
      float marginBottom = 20.f,
      float unitHeight = 5.0f);
    
    inline float& uniHeight() { return unitHeight_; }
    inline float  uniHeight() const { return unitHeight_; }
    inline void setUniHeight(float uniHeight) { unitHeight_ = uniHeight; }

    void parseTree(const MTree &tree);

    std::vector<float> computeNormalisedArea(const MTree &tree);
  private:
    float unitHeight_;
  };
}