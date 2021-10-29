#pragma once

#include <morphotree/tree/mtree.hpp>
#include <morphotree/core/alias.hpp>

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

    TreeLayout(float marginTop = 20.f,
      float marginBottom = 20.f);

    virtual void parseTree(const MTree &tree) = 0;

    inline void setTreeVis(IcicleMorphotreeWidget *t) { treeVis_ = t; }

  protected:
    IcicleMorphotreeWidget *treeVis_;
    float marginBottom_;
    float marginTop_;
  };

  class FixedHeightTreeLayout : public TreeLayout
  {
  public:
    using uint8 = morphotree::uint8;
    using MTree = morphotree::MorphologicalTree<uint8>;
    using NodePtr = typename MTree::NodePtr;

    FixedHeightTreeLayout(float marginTop = 20.f,
      float marginBotton = 20.f,
      float height = 5.0f);

    void parseTree(const MTree &tree);

    std::vector<float> computeNormalisedArea(const MTree &tree);

  private:
    float height_;   
  };
}