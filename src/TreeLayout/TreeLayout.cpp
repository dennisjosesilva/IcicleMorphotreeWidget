#include "IcicleMorphotreeWidget/TreeLayout/TreeLayout.hpp"

#include <morphotree/attributes/areaComputer.hpp>

#include "IcicleMorphotreeWidget/IcicleMorphotreeWidget.hpp"
#include "IcicleMorphotreeWidget/Graphics/GNode.hpp"

namespace IcicleMorphotreeWidget
{
  TreeLayout::TreeLayout(float marginTop, float marginBottom):
    treeVis_{nullptr},
    marginTop_{marginTop},
    marginBottom_{marginBottom}
  {}


  // ================= FIXED HEIGHT TREE LAYOUT ======================
  FixedHeightTreeLayout::FixedHeightTreeLayout(float marginTop,
     float marginBottom, float height):
    TreeLayout{marginTop, marginBottom},
    height_{height}
  {}
  
  void FixedHeightTreeLayout::parseTree(const MTree &tree)
  {
    std::vector<float> narea = computeNormalisedArea(tree);
    std::vector<qreal> left(tree.numberOfNodes(), 0);
    std::vector<qreal> bottom(tree.numberOfNodes(), 0);

    tree.traverseByLevel([&bottom, &narea, &left, this](NodePtr node) {
      if (node->parent() == nullptr) {
        // Root node rendering
        GNode *gnode = new GNode{treeVis_, node};
        treeVis_->scene()->addItem(gnode);
        gnode->setPos(0, 0);
        gnode->setWidth(treeVis_->width());
        gnode->setHeight(height_);
        left[node->id()] = gnode->pos().x();
        bottom[node->id()] = height_;
      } 
      else {
        // TODO: Implement other nodes rendering.
        GNode *gnode = new GNode{treeVis_, node};
        treeVis_->scene()->addItem(gnode);
        qreal leftP = left[node->parent()->id()];
        qreal bottomP = bottom[node->parent()->id()];
        gnode->setPos(leftP, bottomP);
        gnode->setWidth(treeVis_->width() * narea[node->id()]);
        gnode->setHeight(height_);
        
        left[node->id()] = leftP;
        left[node->parent()->id()] = leftP + gnode->width();
        bottom[node->id()] = bottomP + height_;
      }
    });

  }

  std::vector<float> FixedHeightTreeLayout::computeNormalisedArea(
    const MTree &tree)
  {
    using AreaComputer = morphotree::AreaComputer<uint8>;
    using uint32 = morphotree::uint32;

    std::vector<uint32> area = 
      std::make_unique<AreaComputer>()->computeAttribute(tree);
    
    float largestArea = static_cast<float>(area[tree.root()->id()]);

    std::vector<float> normalisedArea(tree.numberOfNodes(), 0);

    for (uint32 nid = 0; nid < tree.numberOfNodes(); ++nid) {
      normalisedArea[nid] = static_cast<float>(area[nid]) / largestArea;
    }

    return normalisedArea;
  }

  // ========= GRAYSCALE BASED HEIGHT TREE LAYOUT ============================
  GrayscaleBasedHeightTreeLayout::GrayscaleBasedHeightTreeLayout(float marginTop,
    float marginBottom, float unitHeight)
    :TreeLayout{marginTop, marginBottom},
     unitHeight_{unitHeight}
  {}

  void GrayscaleBasedHeightTreeLayout::parseTree(const MTree &tree)
  {
    std::vector<float> narea = computeNormalisedArea(tree);
    std::vector<float> left(tree.numberOfNodes(), 0);
    std::vector<qreal> bottom(tree.numberOfNodes(), 0);

    tree.traverseByLevel([&bottom, &narea, &left, this](NodePtr node){
      if (node->parent() == nullptr) {
        int levelsToZero = static_cast<int>(node->level() + 1);
        GNode *gnode = new GNode{treeVis_, node};
        treeVis_->scene()->addItem(gnode);
        gnode->setPos(0, 0);
        gnode->setWidth(treeVis_->width());
        gnode->setHeight(unitHeight_ * levelsToZero);
        left[node->id()] = gnode->pos().x();
        bottom[node->id()] = unitHeight_ * levelsToZero;
      }
      else {
        int levelsToZero = 
          static_cast<int>(node->level() - node->parent()->level());
        GNode *gnode = new GNode{treeVis_, node};
        treeVis_->scene()->addItem(gnode);
        qreal leftP = left[node->parent()->id()];
        qreal bottomP = bottom[node->parent()->id()];
        gnode->setPos(leftP, bottomP);
        gnode->setWidth(treeVis_->width() * narea[node->id()]);
        gnode->setHeight(unitHeight_ * levelsToZero);

        left[node->id()] = leftP;
        left[node->parent()->id()] = leftP + gnode->width();
        bottom[node->id()] = bottomP + gnode->height();
      }
    });
  }

  std::vector<float> GrayscaleBasedHeightTreeLayout::computeNormalisedArea(
    const MTree &tree)
  {
    using AreaComputer = morphotree::AreaComputer<uint8>;
    using uint32 = morphotree::uint32;

    std::vector<uint32> area = 
      std::make_unique<AreaComputer>()->computeAttribute(tree);
    
    float largestArea = static_cast<float>(area[tree.root()->id()]);

    std::vector<float> normalisedArea(tree.numberOfNodes(), 0);

    for (uint32 nid = 0; nid < tree.numberOfNodes(); ++nid) {
      normalisedArea[nid] = static_cast<float>(area[nid]) / largestArea;
    }

    return normalisedArea;
  }
}