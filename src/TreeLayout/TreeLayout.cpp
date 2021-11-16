#include "IcicleMorphotreeWidget/TreeLayout/TreeLayout.hpp"

#include <morphotree/attributes/areaComputer.hpp>

#include "IcicleMorphotreeWidget/IcicleMorphotreeWidget.hpp"
#include "IcicleMorphotreeWidget/Graphics/Node/GNode.hpp"

namespace IcicleMorphotreeWidget
{
  TreeLayout::TreeLayout(GNodeFactoryPtr nodeFactory,
    float marginTop, float marginBottom):
    gnodeFactory_{std::move(nodeFactory)},
    treeVis_{nullptr},
    marginTop_{marginTop},
    marginBottom_{marginBottom}
  {}


  // ================= FIXED HEIGHT TREE LAYOUT ============================
  FixedHeightTreeLayout::FixedHeightTreeLayout(GNodeFactoryPtr nodeFactory,
    float marginTop,
    float marginBottom, float height):
    TreeLayout{std::move(nodeFactory), marginTop, marginBottom},
    height_{height}
  {}
  
  void FixedHeightTreeLayout::parseTree(const MTree &tree)
  {
    std::vector<float> narea = computeNormalisedArea(tree);
    std::vector<qreal> left(tree.numberOfNodes(), 0);
    std::vector<qreal> bottom(tree.numberOfNodes(), 0);
    QVector<GNode *> &gnodes = treeVis_->gnodes();
    float maxBottom = 0;

    tree.traverseByLevel([&bottom, &narea, &left, &gnodes, &maxBottom, this](NodePtr node) {
      if (node->parent() == nullptr) {
        // Root node rendering
        // GNode *gnode = new GNode{treeVis_, node};
        GNode *gnode = gnodeFactory_->create(node);
        // treeVis_->scene()->addItem(gnode);
        treeVis_->addGNodeToScene(gnode);
        gnodes[node->id()] = gnode;
        gnode->setPos(0, 0);
        gnode->setWidth(treeVis_->sceneRect().width());
        gnode->setHeight(height_);
        left[node->id()] = gnode->pos().x();
        bottom[node->id()] = height_;
        maxBottom = height_;
      } 
      else {
        // TODO: Implement other nodes rendering.
        // GNode *gnode = new GNode{treeVis_, node};
        GNode *gnode = gnodeFactory_->create(node);
        // treeVis_->scene()->addItem(gnode);
        treeVis_->addGNodeToScene(gnode);
        gnodes[node->id()] = gnode;
        qreal leftP = left[node->parent()->id()];
        qreal bottomP = bottom[node->parent()->id()];
        gnode->setPos(leftP, bottomP);
        gnode->setWidth(treeVis_->sceneRect().width() * narea[node->id()]);
        gnode->setHeight(height_);
        
        left[node->id()] = leftP;
        left[node->parent()->id()] = leftP + gnode->width();
        bottom[node->id()] = bottomP + height_;
        if (bottom[node->id()] > maxBottom) 
          maxBottom = bottom[node->id()];
      }
    });

    QRectF sRect = treeVis_->sceneRect();
    sRect.setHeight(maxBottom);
    treeVis_->scene()->setSceneRect(sRect);    
    treeVis_->scene()->update();
    treeVis_->update();
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
  GrayscaleBasedHeightTreeLayout::GrayscaleBasedHeightTreeLayout(
    GNodeFactoryPtr nodeFactory, float marginTop,
    float marginBottom, float unitHeight)
    :TreeLayout{std::move(nodeFactory), marginTop, marginBottom},
     unitHeight_{unitHeight}
  {}

  void GrayscaleBasedHeightTreeLayout::parseTree(const MTree &tree)
  {
    std::vector<float> narea = computeNormalisedArea(tree);
    std::vector<float> left(tree.numberOfNodes(), 0);
    std::vector<qreal> bottom(tree.numberOfNodes(), 0);
    QVector<GNode *> &gnodes = treeVis_->gnodes();
    float maxBottom = 0;

    tree.traverseByLevel([&bottom, &narea, &left, &gnodes, &maxBottom, this](NodePtr node){
      if (node->parent() == nullptr) {
        int levelsToZero = static_cast<int>(node->level() + 1);
        // GNode *gnode = new GNode{treeVis_, node};
        GNode *gnode = gnodeFactory_->create(node);
        treeVis_->addGNodeToScene(gnode);
        gnodes[node->id()] = gnode;
        // treeVis_->scene()->addItem(gnode);
        gnode->setPos(0, 0);
        gnode->setWidth(treeVis_->sceneRect().width());
        gnode->setHeight(unitHeight_ * levelsToZero);
        left[node->id()] = gnode->pos().x();
        bottom[node->id()] = unitHeight_ * levelsToZero;
        maxBottom = bottom[node->id()];
      }
      else {
        int levelsToZero = 
          static_cast<int>(node->level() - node->parent()->level());
        // GNode *gnode = new GNode{treeVis_, node};
        GNode *gnode = gnodeFactory_->create(node);
        treeVis_->addGNodeToScene(gnode);
        gnodes[node->id()] = gnode;
        //treeVis_->scene()->addItem(gnode);
        qreal leftP = left[node->parent()->id()];
        qreal bottomP = bottom[node->parent()->id()];
        gnode->setPos(leftP, bottomP);
        gnode->setWidth(treeVis_->sceneRect().width() * narea[node->id()]);
        gnode->setHeight(unitHeight_ * levelsToZero);

        left[node->id()] = leftP;
        left[node->parent()->id()] = leftP + gnode->width();
        bottom[node->id()] = bottomP + gnode->height();
        if (maxBottom < bottom[node->id()])
          maxBottom = bottom[node->id()];
      }
    });
    QRectF sRect = treeVis_->sceneRect();
    sRect.setHeight(maxBottom);
    treeVis_->scene()->setSceneRect(sRect);
    treeVis_->scene()->update();
    treeVis_->update();
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