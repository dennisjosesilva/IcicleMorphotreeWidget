#pragma once 

#include <morphotree/tree/mtree.hpp>
#include <morphotree/core/alias.hpp>

#include "IcicleMorphotreeWidget/Graphics/Node/GNodeFactory.hpp"
#include "IcicleMorphotreeWidget/TreeLayout/TreeLayout.hpp"
#include "IcicleMorphotreeWidget/Graphics/GrayScaleBar/GrayScaleProfile.hpp"

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
      GNodeFactoryPtr nodeFactory=std::make_unique<HGradientGNodeFactory>(),      
      const GrayScaleProfile &grayScaleProfile=GrayScaleProfile{Range{0,255}, Range{0, 255}},
      float marginTop = 0.0f,
      float marginBottom = 0.0f,
      qreal marginLeft = 0.0f,
      MorphoTreeType mtreeType = MorphoTreeType::MAX_TREE_8C);
        
    std::vector<float> computeNormalisedArea(const MTree &tree);

    inline float unitHeight() const override { return unitHeight_; }
    inline float unitWidth() const override { return unitWidth_; }

    inline qreal marginLeft() const { return marginLeft_; }
    inline qreal &marginLeft() { return marginLeft_; }
    inline void setMarginLeft(qreal val) { marginLeft_ = val; }

    qreal computeUnitHeightFromTheTree(const MTree &tree) const;
    qreal computeUnitWidthFromTheTree(const MTree &tree) const;

    inline TreeLayoutType type() const override { return TreeLayoutType::AutoSize; }    

    inline const GrayScaleProfile &grayscaleProfile() const { return grayscaleProfile_; }
    inline void setGrayscaleProfile(const GrayScaleProfile &val) { grayscaleProfile_ = val; }

  protected:
    void parseVertical(const MTree &tree) override;
    void parseHorizontal(const MTree &tree) override;    

  private:
    qreal unitHeight_;
    qreal marginLeft_;
    qreal unitWidth_;

    GrayScaleProfile grayscaleProfile_;
  };
}