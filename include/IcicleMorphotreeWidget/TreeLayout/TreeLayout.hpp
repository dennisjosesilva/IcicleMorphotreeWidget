#pragma once

#include <morphotree/tree/mtree.hpp>
#include <morphotree/core/alias.hpp>

#include "IcicleMorphotreeWidget/Graphics/Node/GNodeFactory.hpp"
#include "IcicleMorphotreeWidget/MorphoTreeType.hpp"

#include <vector>

namespace IcicleMorphotreeWidget
{
  class IcicleMorphotreeWidget;    

  enum TreeLayoutType {
    FixedHeight,
    GrayScaleBasedHeight,
    AutoSize
  };

  enum TreeLayoutOrientation {
    Horizontal,
    Vertical
  };

  class TreeLayout
  {
  public:
    using uint8 = morphotree::uint8;
    using MTree = morphotree::MorphologicalTree<uint8>;
    using NodePtr = typename MTree::NodePtr;
    using GNodeFactoryPtr = std::shared_ptr<GNodeFactory>;

    TreeLayout(
      GNodeFactoryPtr nodeFactory=std::make_shared<HGradientGNodeFactory>(),
      float marginTop = 20.f,
      float marginBottom = 20.f,
      MorphoTreeType mtreeType = MorphoTreeType::MAX_TREE_8C);

    void parseTree(const MTree &tree);

    virtual TreeLayoutType type() const = 0;
    GNodeStyle style() const { return gnodeFactory_->style();  }

    virtual float unitHeight() const = 0;
    virtual float unitWidth() const = 0;

    inline void setTreeVis(IcicleMorphotreeWidget *t) { gnodeFactory_->setTreeVisualiser(t); treeVis_ = t; }

    inline void setGNodeFactory(GNodeFactoryPtr f) { gnodeFactory_ = std::move(f); }
    inline GNodeFactoryPtr gnodeFactory() { return gnodeFactory_; }

    inline float  marginTop() const { return marginTop_; }
    inline float& marginTop() { return marginTop_; }
    inline void setMarginTop(float val) { marginTop_ = val; }

    inline float  marginBottom() const { return marginBottom_; }
    inline float& marginBottom() { return marginBottom_; }
    inline void setMarginBottom(float val) { marginBottom_ = val; }

    inline TreeLayoutOrientation orientation() const { return orientation_; }
    inline TreeLayoutOrientation &orientation() { return orientation_; }
    inline void setOrientation(TreeLayoutOrientation orientation) { orientation_ = orientation; }

    inline MorphoTreeType mtreeType() const { return mtreeType_; }
    inline void setMTreeType(MorphoTreeType val) { mtreeType_ = val; }

    virtual ~TreeLayout();

  protected:
    virtual void parseHorizontal(const MTree &tree) = 0;
    virtual void parseVertical(const MTree &tree) = 0;

  protected:
    IcicleMorphotreeWidget *treeVis_;
    GNodeFactoryPtr gnodeFactory_;
    float marginBottom_;
    float marginTop_;

    MorphoTreeType mtreeType_;
    TreeLayoutOrientation orientation_;    
  };

  class FixedHeightTreeLayout : public TreeLayout
  {
  public:
    using uint8 = morphotree::uint8;
    using MTree = morphotree::MorphologicalTree<uint8>;
    using NodePtr = typename MTree::NodePtr;

    FixedHeightTreeLayout(
      GNodeFactoryPtr nodeFactory=std::make_unique<HGradientGNodeFactory>(),
      float marginTop = 20.f,
      float marginBotton = 20.f,
      float height = 5.0f,
      MorphoTreeType mtreeType = MorphoTreeType::MAX_TREE_8C);
    
    std::vector<float> computeNormalisedArea(const MTree &tree);

    float unitWidth() const override { return 0.0f; }
    float unitHeight() const override { return 0.0f; }
    
    inline float& height() { return height_; }
    inline float height() const { return height_; }
    inline void setHeight(float height) { height_ = height; }

    inline TreeLayoutType type() const override { return FixedHeight; }
 
  protected:
    void parseVertical(const MTree &tree) override;
    void parseHorizontal(const MTree &tree) override;

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
      GNodeFactoryPtr nodeFactory=std::make_unique<HGradientGNodeFactory>(),
      float marginTop = 20.f,
      float marginBottom = 20.f,
      float unitHeight = 5.0f,
      MorphoTreeType mtreeType = MorphoTreeType::MAX_TREE_8C);
    
    inline float unitHeight() const override { return unitHeight_; }
    inline float unitWidth() const override { return unitHeight_; }

    inline float& uniHeight() { return unitHeight_; }
    inline float  uniHeight() const { return unitHeight_; }
    inline void setUniHeight(float uniHeight) { unitHeight_ = uniHeight; }

    inline TreeLayoutType type() const override { return TreeLayoutType::GrayScaleBasedHeight; }
 
    std::vector<float> computeNormalisedArea(const MTree &tree);

    int greyLevelDifference(NodePtr mnode) const;

  protected:
    void parseHorizontal(const MTree &tree) override;
    void parseVertical(const MTree &tree) override;

  private:
    float unitHeight_;
  };
}