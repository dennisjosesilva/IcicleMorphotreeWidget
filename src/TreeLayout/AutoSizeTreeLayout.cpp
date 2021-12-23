#include "IcicleMorphotreeWidget/TreeLayout/AutoSizeTreeLayout.hpp"

#include <morphotree/attributes/areaComputer.hpp>

#include "IcicleMorphotreeWidget/IcicleMorphotreeWidget.hpp"
#include "IcicleMorphotreeWidget/Graphics/Node/GNode.hpp"

namespace IcicleMorphotreeWidget
{ 
  AutoSizeTreeLayout::AutoSizeTreeLayout(GNodeFactoryPtr nodeFactory,
    float marginTop, float marginBottom, qreal marginLeft)
    : TreeLayout{std::move(nodeFactory), marginTop, marginBottom},
      unitHeight_{-1.0f},
      marginLeft_{marginLeft}
  {}

  void AutoSizeTreeLayout::parseTree(const MTree &tree)
  {
    std::vector<float> narea = computeNormalisedArea(tree);
    std::vector<float> left(tree.numberOfNodes(), 0);
    std::vector<float> bottom(tree.numberOfNodes(), 0);
    QVector<GNode *> &gnodes = treeVis_->gnodes();
    float maxBottom = 0;
    unitHeight_ = computeUnitHeightFromTheTree(tree);

    float renderWidth = treeVis_->sceneRect().width() - marginLeft_;

    tree.traverseByLevel([&bottom, &narea, &left, &gnodes, &maxBottom, &renderWidth, this](NodePtr node) {
      if (node->parent() == nullptr) { // root node
        int levelsToZero = static_cast<int>(node->level()) + 1;
        GNode *gnode = gnodeFactory_->create(node);
        treeVis_->addGNodeToScene(gnode);
        gnodes[node->id()] = gnode;
        gnode->setPos(marginLeft_, 0);
        gnode->setWidth(renderWidth);
        gnode->setHeight(unitHeight_ * levelsToZero);
        left[node->id()] = gnode->pos().x();
        bottom[node->id()] = gnode->height(); 
        maxBottom = bottom[node->id()];
      }
      else {
        int levelsToZero = 
          static_cast<int>(node->level()) - static_cast<int>(node->parent()->level());
        GNode *gnode = gnodeFactory_->create(node);
        treeVis_->addGNodeToScene(gnode);
        gnodes[node->id()] = gnode;
        qreal leftP = left[node->parent()->id()];
        qreal bottomP = bottom[node->parent()->id()];
        gnode->setPos(leftP, bottomP);
        gnode->setWidth(renderWidth * narea[node->id()]);
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

  std::vector<float> AutoSizeTreeLayout::computeNormalisedArea(const MTree &tree)
  {
    using AreaComputer = morphotree::AreaComputer<uint8>;
    using uint32 = morphotree::uint32;

    std::vector<uint32> area =
      std::make_unique<AreaComputer>()->computeAttribute(tree);
    
    float largestArea = static_cast<float>(area[tree.root()->id()]);

    std::vector<float> normalisedArea(tree.numberOfNodes(), 0);

    for (uint32 nid = 0; nid < tree.numberOfNodes(); nid++) 
      normalisedArea[nid] = static_cast<float>(area[nid]) / largestArea;

    return normalisedArea;
  }

  qreal AutoSizeTreeLayout::computeUnitHeightFromTheTree(const MTree &tree) const
  {
    uint8 maxLevel = 0;
    tree.tranverse([&maxLevel](NodePtr node) { 
      if (maxLevel < node->level())
        maxLevel = node->level();
    });

    qreal height = treeVis_->sceneRect().height();

    return (height / (static_cast<qreal>(maxLevel)+1.0));
  }
}

