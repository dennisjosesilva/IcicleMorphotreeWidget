#include "IcicleMorphotreeWidget/TreeLayout/AutoSizeTreeLayout.hpp"

#include <morphotree/attributes/areaComputer.hpp>

#include "IcicleMorphotreeWidget/IcicleMorphotreeWidget.hpp"
#include "IcicleMorphotreeWidget/Graphics/Node/GNode.hpp"

namespace IcicleMorphotreeWidget
{ 
  AutoSizeTreeLayout::AutoSizeTreeLayout(GNodeFactoryPtr nodeFactory,
    const GrayScaleProfile &grayscaleProfile,
    float marginTop, float marginBottom, qreal marginLeft,
    MorphoTreeType mtreeType)
    : TreeLayout{std::move(nodeFactory), marginTop, marginBottom, mtreeType},
      unitHeight_{-1.0f},
      marginLeft_{marginLeft},
      grayscaleProfile_{grayscaleProfile}
  {}

  void AutoSizeTreeLayout::parseVertical(const MTree &tree)
  {
    std::vector<float> narea = computeNormalisedArea(tree);
    std::vector<float> left(tree.numberOfNodes(), 0);
    std::vector<float> bottom(tree.numberOfNodes(), 0);
    QVector<GNode *> &gnodes = treeVis_->gnodes();
    float maxBottom = 0;
    unitHeight_ = grayscaleProfile_.computeUnitBlock(treeVis_->sceneRect().height());  // computeUnitHeightFromTheTree(tree);

    float renderWidth = treeVis_->sceneRect().width() - marginLeft_;

    tree.traverseByLevel([&bottom, &narea, &left, &gnodes, &maxBottom, &renderWidth, this](NodePtr node) {
      if (node->parent() == nullptr) { // root node        
        int levelsToZero; 
        if(isMaxTree())
          levelsToZero = grayscaleProfile_.irange().min - static_cast<int>(node->level())+1;
        else 
          levelsToZero = grayscaleProfile_.irange().max - static_cast<int>(node->level())+1;
        
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
          qAbs(static_cast<int>(node->level()) - static_cast<int>(node->parent()->level()));
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

  void AutoSizeTreeLayout::parseHorizontal(const MTree &tree)
  {
    std::vector<float> narea = computeNormalisedArea(tree);
    std::vector<float> top(tree.numberOfNodes(), 0);
    std::vector<float> right(tree.numberOfNodes(), 0);
    QVector<GNode *> &gnodes = treeVis_->gnodes();
    float maxRight = 0.0f;
    unitWidth_ =  grayscaleProfile_.computeUnitBlock(treeVis_->sceneRect().width());  // computeUnitWidthFromTheTree(tree);

    float renderHeight = treeVis_->sceneRect().height() - marginTop_;

    tree.traverseByLevel([&right, &narea, &top, &gnodes, &maxRight, &renderHeight, this](NodePtr node){
      if (node->parent() == nullptr) { 
        // root node
        // ---------
        int levelsToZero = static_cast<int>(node->level()) + 1;
        GNode *gnode = gnodeFactory_->create(node);
        treeVis_->addGNodeToScene(gnode);
        gnodes[node->id()] = gnode;
        gnode->setPos(0, marginTop_);
        gnode->setWidth(unitWidth_ * levelsToZero);
        gnode->setHeight(renderHeight);
        right[node->id()] = gnode->width();
        top[node->id()] = marginTop_;
        maxRight = right[node->id()];
      }
      else {
        // other nodes of the tree
        // -----------------------
        int levelsToZero = static_cast<int>(node->level()) - 
          static_cast<int>(node->parent()->level());
        GNode *gnode = gnodeFactory_->create(node);
        treeVis_->addGNodeToScene(gnode);
        gnodes[node->id()] = gnode;
        qreal topP = top[node->parent()->id()];
        qreal rightP = right[node->parent()->id()];
        gnode->setPos(rightP, topP);
        gnode->setWidth(unitWidth_ * levelsToZero);
        gnode->setHeight(renderHeight * narea[node->id()]);

        top[node->id()] = topP;
        top[node->parent()->id()] = topP + gnode->height();
        right[node->id()] = rightP + gnode->width();
        if (maxRight < right[gnode->width()])
          maxRight = right[node->id()];
      }
    });

    QRectF sRect = treeVis_->sceneRect();
    sRect.setWidth(maxRight);
    treeVis_->scene()->setSceneRect(sRect);
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

  bool AutoSizeTreeLayout::isMaxTree() const
  {
    return mtreeType_ == MAX_TREE_8C || mtreeType_ == MAX_TREE_4C;
  }
  
  bool AutoSizeTreeLayout::isMinTree() const
  {
    return mtreeType_ == MIN_TREE_4C || mtreeType_ == MIN_TREE_8C;
  }
}

