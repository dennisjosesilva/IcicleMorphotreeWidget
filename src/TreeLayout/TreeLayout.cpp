#include "IcicleMorphotreeWidget/TreeLayout/TreeLayout.hpp"

#include <morphotree/attributes/areaComputer.hpp>

#include "IcicleMorphotreeWidget/IcicleMorphotreeWidget.hpp"
#include "IcicleMorphotreeWidget/Graphics/Node/GNode.hpp"

namespace IcicleMorphotreeWidget
{
  TreeLayout::TreeLayout(GNodeFactoryPtr nodeFactory,
    float marginTop, float marginBottom, MorphoTreeType mtreeType):
    gnodeFactory_{std::move(nodeFactory)},
    treeVis_{nullptr},
    marginTop_{marginTop},
    marginBottom_{marginBottom},
    orientation_{TreeLayoutOrientation::Vertical},
    mtreeType_{mtreeType}
  {}

  void TreeLayout::parseTree(const MTree &tree) 
  {
    switch (orientation_)
    {
    case TreeLayoutOrientation::Horizontal:
      parseHorizontal(tree);
      break;

    case TreeLayoutOrientation::Vertical:
      parseVertical(tree);
      break;
    }    
  }

  TreeLayout::~TreeLayout()
  {}

  // ================= FIXED HEIGHT TREE LAYOUT ============================
  FixedHeightTreeLayout::FixedHeightTreeLayout(GNodeFactoryPtr nodeFactory,
    float marginTop, float marginBottom, float height,
    MorphoTreeType mtreeType):
    TreeLayout{std::move(nodeFactory), marginTop, marginBottom, mtreeType},
    height_{height}
  {}
  
  void FixedHeightTreeLayout::parseVertical(const MTree &tree)
  {
    std::vector<float> narea = computeNormalisedArea(tree);
    std::vector<qreal> left(tree.numberOfNodes(), 0);
    std::vector<qreal> bottom(tree.numberOfNodes(), 0);
    QVector<GNode *> &gnodes = treeVis_->gnodes();
    float maxBottom = 0;

    tree.traverseByLevel([&bottom, &narea, &left, &gnodes, &maxBottom, this](NodePtr node) {
      if (node->parent() == nullptr) {
        // Root node rendering        
        GNode *gnode = gnodeFactory_->create(node);        
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
        GNode *gnode = gnodeFactory_->create(node);
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

  void FixedHeightTreeLayout::parseHorizontal(const MTree &tree)
  {
    std::vector<float> narea = computeNormalisedArea(tree);
    std::vector<qreal> top(tree.numberOfNodes(), 0);
    std::vector<qreal> right(tree.numberOfNodes(), 0);
    QVector<GNode *> &gnodes = treeVis_->gnodes();
    float maxRight = 0.0f;
    float uniWidth = height_;

    tree.traverseByLevel([&right, &narea, &top, &gnodes, &maxRight, &uniWidth, this](NodePtr node) {
      if (node->parent() == nullptr) {
        // Root node rendering
        GNode *gnode = gnodeFactory_->create(node);
        treeVis_->addGNodeToScene(gnode);
        gnodes[node->id()] = gnode;
        gnode->setPos(0,0);
        gnode->setWidth(uniWidth);
        gnode->setHeight(treeVis_->sceneRect().height());
        top[node->id()] = 0;
        right[node->id()] = uniWidth;
        maxRight = height_;
      }
      else {
        // other nodes rendering
        GNode *gnode = gnodeFactory_->create(node);
        treeVis_->addGNodeToScene(gnode);
        gnodes[node->id()] = gnode;
        qreal topP = top[node->parent()->id()];
        qreal rightP = right[node->parent()->id()];
        gnode->setPos(rightP, topP);
        gnode->setHeight(treeVis_->sceneRect().height() * narea[node->id()]);
        gnode->setWidth(uniWidth);

        top[node->id()] = topP;
        top[node->parent()->id()] = topP + gnode->height();
        right[node->id()] = rightP + gnode->width();
        if (right[node->id()] > maxRight)
          maxRight = right[node->id()];
      }      
    });

    QRectF sRect = treeVis_->sceneRect();
    sRect.setWidth(maxRight);
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
    float marginBottom, float unitHeight, MorphoTreeType mtreeType)
    :TreeLayout{std::move(nodeFactory), marginTop, marginBottom, mtreeType},
     unitHeight_{unitHeight}
  {}

  void GrayscaleBasedHeightTreeLayout::parseVertical(const MTree &tree)
  {
    std::vector<float> narea = computeNormalisedArea(tree);
    std::vector<float> left(tree.numberOfNodes(), 0);
    std::vector<qreal> bottom(tree.numberOfNodes(), 0);
    QVector<GNode *> &gnodes = treeVis_->gnodes();
    float maxBottom = 0;

    tree.traverseByLevel([&bottom, &narea, &left, &gnodes, &maxBottom, this](NodePtr node){
      if (node->parent() == nullptr) {
        int levelsToZero = static_cast<int>(node->level() + 1);        
        GNode *gnode = gnodeFactory_->create(node);
        treeVis_->addGNodeToScene(gnode);
        gnodes[node->id()] = gnode;
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
        GNode *gnode = gnodeFactory_->create(node);
        treeVis_->addGNodeToScene(gnode);
        gnodes[node->id()] = gnode;
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

  void GrayscaleBasedHeightTreeLayout::parseHorizontal(const MTree &tree)
  {
    std::vector<float> narea = computeNormalisedArea(tree);
    std::vector<qreal> top(tree.numberOfNodes(), 0);
    std::vector<qreal> right(tree.numberOfNodes(), 0);
    QVector<GNode *> &gnodes = treeVis_->gnodes();
    float maxRight = 0.0f;
    float uniWidth = unitHeight_;
    
    tree.traverseByLevel([&right, &narea, &top, &gnodes, &maxRight, &uniWidth, this](NodePtr node){
      if (node->parent() == nullptr) {              
        int levelsToZero = static_cast<int>(node->level()) + 1;
        GNode *gnode = gnodeFactory_->create(node);
        treeVis_->addGNodeToScene(gnode);
        gnodes[node->id()] = gnode;
        gnode->setPos(0, 0);
        gnode->setWidth(uniWidth * levelsToZero);
        gnode->setHeight(treeVis_->sceneRect().height());
        right[node->id()] = gnode->width();
        top[node->id()] = 0;
        maxRight = right[node->id()];
      }
      else {
        // Other node rendering
        int levelsToZero = qAbs(static_cast<int>(node->level()) - node->parent()->level());
        GNode *gnode = gnodeFactory_->create(node);
        treeVis_->addGNodeToScene(gnode);
        gnodes[node->id()] = gnode;
        qreal rightP = right[node->parent()->id()];
        qreal topP = top[node->parent()->id()];
        gnode->setPos(rightP, topP);
        gnode->setWidth(uniWidth * levelsToZero);
        gnode->setHeight(treeVis_->sceneRect().height() * narea[node->id()]);

        top[node->id()] = topP;
        top[node->parent()->id()] = topP + gnode->height();
        right[node->id()] = rightP + gnode->width();
        if (maxRight < right[node->id()]) 
          maxRight = right[node->id()];
      }
    });

    QRectF sRect = treeVis_->sceneRect();
    sRect.setWidth(maxRight);
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