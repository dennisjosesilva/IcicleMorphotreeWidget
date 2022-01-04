#include "IcicleMorphotreeWidget/IcicleMorphotreeWidget.hpp"
#include "IcicleMorphotreeWidget/Graphics/Node/GNode.hpp"

#include "IcicleMorphotreeWidget/TreeLayout/AutoSizeTreeLayout.hpp"

#include <morphotree/adjacency/adjacency8c.hpp>

#include <QDebug>

#include <QKeyEvent>

namespace IcicleMorphotreeWidget 
{
  IcicleMorphotreeWidget::IcicleMorphotreeWidget(QWidget *parent,
    TreeLayoutPtr treeLayout)
    :QGraphicsView{parent},
     scaleFactor_{1.0},
     tree_{morphotree::MorphoTreeType::MaxTree},
     treeLayout_{std::move(treeLayout)},
     grayScaleBar_{nullptr},
     colorMap_{std::make_unique<RainbowColorMap>()},
     grayScalerBarBreadth_{0.0f}     
  {
    QGraphicsScene *scene = new QGraphicsScene{this};
    scene->setSceneRect(QRectF{0, 0, 400, 400});
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    setMinimumSize(400, 400);
    setWindowTitle(tr("Icicle Morphotree Widget"));

    treeLayout_->setTreeVis(this);
      
    update();
  }

  void IcicleMorphotreeWidget::loadImage(Box domain, 
    const std::vector<uint8> &f)
  {   
    namespace mt = morphotree; 

    domain_ = domain;
    tree_ = 
      mt::buildMaxTree(f, std::make_unique<mt::Adjacency8C>(domain_));    

    updateTreeRendering();
  }

  void IcicleMorphotreeWidget::loadAttributes(NormAttributesPtr attr)
  {
    attr_ = std::move(attr);
    paintNodesBasedOnNormAttribute();
    viewport()->update();
  }

  void IcicleMorphotreeWidget::clearAttributes()
  {
    attr_ = nullptr;
    resetNodesColor();
    viewport()->update();
  }

  void IcicleMorphotreeWidget::addGNodeToScene(GNode *node)
  {
    if (attr_ && !attr_->empty()) {
      float attrVal = attr_->at(node->mnode()->id());
      node->setBackgroundColor(colorMap_->color(attrVal));
    }

    scene()->addItem(node);    
  }

  void IcicleMorphotreeWidget::drawBackground(QPainter *painter, 
    const QRectF &rect)
  {
    painter->setBrush(Qt::white);
    
    if (grayScaleBar_ != nullptr) {
      const QRectF &s = sceneRect();
      qreal marginLeft = grayScaleBar_->unitWidth()+15;
      QRectF renderRect{ marginLeft, 0, s.width()-marginLeft, s.height() };
      painter->drawRect(sceneRect());
    }
    else {
      painter->drawRect(sceneRect());
    }    
  }

  void IcicleMorphotreeWidget::updateTreeRendering()
  {
    if (grayScaleBar_ != nullptr) {
      // backup grayscaleBar before it is deleted by scene()->clear()
      
      QPointF pos = grayScaleBar_->pos();
      bool showBorders = grayScaleBar_->showBorders();

      grayScaleBar_ =  new GrayScaleBar{grayScaleBar_->unitWidth(), 
        grayScaleBar_->unitHeight(), grayScaleBar_ ->numberOfLevels(),
        grayScaleBar_->orientation()};
      grayScaleBar_->setPos(pos);
      grayScaleBar_->setShowBorders(showBorders);
    }
    
    // It deletes all items including grayscaleBar_
    scene()->clear();    

    gnodes_.clear();
    gnodes_.resize(tree_.numberOfNodes());

    treeLayout_->parseTree(tree_);
    if (grayScaleBar_ != nullptr) {
      scene()->addItem(grayScaleBar_);
    }

    emit treeAboutToBeRedrawn();
    scene()->update();    
  }

  IcicleMorphotreeWidget::MTree 
    IcicleMorphotreeWidget::filter(std::shared_ptr<TreeFiltering>
    treeFiltering)
  {
    MTree copiedTree = tree_.copy();
    
    clearAttributes();
    removeGrayScaleBar();

    treeFiltering->ifilter(tree_);
    updateTreeRendering();
    update();
    return copiedTree;
  }

  void IcicleMorphotreeWidget::ifilter(
    std::shared_ptr<TreeFiltering> treeFiltering)
  {    
    clearAttributes();
    removeGrayScaleBar();
    
    treeFiltering->ifilter(tree_);
    updateTreeRendering();
    update();
  }

  void IcicleMorphotreeWidget::paintNodesBasedOnNormAttribute()
  {
    if (!gnodes_.empty() && !attr_->empty()) {
      for (GNode *gnode : gnodes_) {
        float attrVal = attr_->at(gnode->mnode()->id());
        gnode->setBackgroundColor(colorMap_->color(attrVal));
      }
    }
  }

  void IcicleMorphotreeWidget::resetNodesColor()
  {
    for (GNode *gnode : gnodes_) {
      gnode->setBackgroundColor(Qt::lightGray);
    }
  }


  void IcicleMorphotreeWidget::scaleView(qreal scaleFactor)
  {
    qreal factor = transform().scale(scaleFactor, scaleFactor)
      .mapRect(QRectF{0, 0, 1, 1}).width();
    
    if (factor < 0.07f || factor > 100.0f)
      return;
    scaleFactor_ *= scaleFactor;
    scale(scaleFactor, scaleFactor);
  }

  void IcicleMorphotreeWidget::visZoomIn()
  {
    scaleView(qreal(1.2));
  }

  void IcicleMorphotreeWidget::visZoomOut()
  {
    scaleView(1.0 / qreal(1.2));
  }

  void IcicleMorphotreeWidget::addGrayScaleBar(unsigned int numberOfLevels, 
    qreal breadth)
  {
    using FixedHeightTreeLayoutPtr = std::shared_ptr<FixedHeightTreeLayout>;
    using GrayscaleBasedHeightTreeLayoutPtr = std::shared_ptr<GrayscaleBasedHeightTreeLayout>;
    using AutoSizeTreeLayoutPtr = std::shared_ptr<AutoSizeTreeLayout>;

    if (grayScaleBar_ == nullptr)  {    
      float unitWidth = 0.0f;
      float unitHeight = 0.0f;
      grayScalerBarBreadth_ = breadth;

      if (treeLayout_->orientation() == TreeLayoutOrientation::Horizontal) {        
        switch (treeLayout_->type()) {
          case TreeLayoutType::GrayScaleBasedHeight:
          {
            GrayscaleBasedHeightTreeLayoutPtr l = 
              std::dynamic_pointer_cast<GrayscaleBasedHeightTreeLayout>(treeLayout_);
            unitHeight = breadth;
            unitWidth = l->uniHeight();
            break;
          }
        
          case TreeLayoutType::FixedHeight:
          {
            FixedHeightTreeLayoutPtr l = 
              std::dynamic_pointer_cast<FixedHeightTreeLayout>(treeLayout_);
            unitHeight = breadth;
            unitWidth = l->height();
            break;
          }
        
          case TreeLayoutType::AutoSize:
          {
            AutoSizeTreeLayoutPtr l =
              std::dynamic_pointer_cast<AutoSizeTreeLayout>(treeLayout_);
            unitHeight = breadth;
            unitWidth = l->unitWidth();
            l->setMarginLeft(0.0);
            l->setMarginTop(unitHeight + 15);
            break;
          }
        }
      }
      else { // when orientation == Vertical
        switch (treeLayout_->type())
        {
          case TreeLayoutType::GrayScaleBasedHeight:
          {
            GrayscaleBasedHeightTreeLayoutPtr l = 
              std::dynamic_pointer_cast<GrayscaleBasedHeightTreeLayout>(treeLayout_);
            unitHeight = l->uniHeight();
            unitWidth = breadth;
            break;
          }
          case TreeLayoutType::FixedHeight:
          {
            FixedHeightTreeLayoutPtr l = 
              std::dynamic_pointer_cast<FixedHeightTreeLayout>(treeLayout_);
            unitHeight = l->height();
            unitWidth = breadth;
            break;
          }
          case TreeLayoutType::AutoSize:
          {
            AutoSizeTreeLayoutPtr l = 
              std::dynamic_pointer_cast<AutoSizeTreeLayout>(treeLayout_);
            unitHeight = l->unitHeight();
            unitWidth = breadth;
            l->setMarginTop(0.0);
            l->setMarginLeft(unitWidth + 15);
            break;
          }        
        }
      }

      grayScaleBar_ = new GrayScaleBar{unitWidth, unitHeight, numberOfLevels,
        treeLayout_->orientation()};
      grayScaleBar_->setPos(0, 0);      
      
      updateTreeRendering();
    }
  }

  void IcicleMorphotreeWidget::removeGrayScaleBar()
  {
    if (grayScaleBar_ != nullptr) {
      scene()->removeItem(grayScaleBar_);
      qreal unitWidth = grayScaleBar_->unitWidth();
      grayScaleBar_ = nullptr;
            
      if (treeLayout_->type() == AutoSize) {
        std::shared_ptr<AutoSizeTreeLayout> treeLayout =
          std::dynamic_pointer_cast<AutoSizeTreeLayout>(treeLayout_);
        
        treeLayout->setMarginLeft(0);
        treeLayout_->setMarginTop(0);
      }
      updateTreeRendering();
      scene()->update();
      update();
    }
  }

  void IcicleMorphotreeWidget::renderGrayScaleBar()
  {    
    // const QRectF &sceneRect = scene()->sceneRect();      
    // scene()->setSceneRect(-grayScaleBar_->unitWidth(), 0, 
    //   sceneRect.width()+grayScaleBar_->unitWidth(), sceneRect.height());        
    scene()->update();
    update();
  }

  void IcicleMorphotreeWidget::setTreeLayout(TreeLayoutPtr treeLayout)
  {
    treeLayout_ = treeLayout;
    updateTreeRendering();    
  }

  void IcicleMorphotreeWidget::setOrientation(TreeLayoutOrientation val)
  {
    treeLayout_->setOrientation(val);
    
    if (treeLayout_->style() == GNodeStyle::GradientColor) {
      if (val == TreeLayoutOrientation::Horizontal)
        treeLayout_->setGNodeFactory(std::make_unique<VGradientGNodeFactory>(this));
      else
        treeLayout_->setGNodeFactory(std::make_unique<HGradientGNodeFactory>(this));
    }

    if (grayScaleBar_ != nullptr) {
      float unitWidth = grayScaleBar_->unitWidth();
      float unitHeight = grayScaleBar_->unitHeight();
      unsigned int numberOfLevels = grayScaleBar_->numberOfLevels();      
      bool showBorders = grayScaleBar_->showBorders();
      removeGrayScaleBar();
      addGrayScaleBar(numberOfLevels, grayScalerBarBreadth_);
      grayScaleBar_->setShowBorders(showBorders);
    }
    else {
      updateTreeRendering();
    }
  }

  void IcicleMorphotreeWidget::keyPressEvent(QKeyEvent *e)
  {
    switch (e->key())
    {
    case Qt::Key_Plus:
      visZoomIn();
      break;
    
    case Qt::Key_Minus:
      visZoomOut();
      break;

    case Qt::Key_0:
      fitToWidget();
      break;

    case Qt::Key_Alt:
      isDownSpace_ = true; 
      setDragMode(QGraphicsView::ScrollHandDrag);      
      break;

    default:
      break;
    }
  }

  void IcicleMorphotreeWidget::keyReleaseEvent(QKeyEvent *e)
  {
    switch (e->key())
    {
    case Qt::Key_Alt:
      isDownSpace_ = false;
      setDragMode(QGraphicsView::NoDrag);      
      break;
    
    default:
      break;
    }
  }

  void IcicleMorphotreeWidget::resizeEvent(QResizeEvent *e) 
  {    
    const QSize& s = e->size();
    if (grayScaleBar_ != nullptr) {
      using AutoSizeTLPtr = std::shared_ptr<AutoSizeTreeLayout>;

      // scene()->setSceneRect(0, 0, s.width(), s.height());
      setSceneRect(0, 0, s.width(), s.height());
      QGraphicsView::resizeEvent(e);
      updateTreeRendering();
      if (treeLayout_->type() == TreeLayoutType::AutoSize) {
        AutoSizeTLPtr t = std::dynamic_pointer_cast<AutoSizeTreeLayout>(treeLayout_);
        
        if (treeLayout_->orientation() == TreeLayoutOrientation::Horizontal)
          grayScaleBar_->setUnitWidth(t->unitWidth());
        else 
          grayScaleBar_->setUnitHeight(t->unitHeight());
        
        renderGrayScaleBar();
      }
    }
    else {
      // scene()->setSceneRect(0, 0, s.width(), s.height());
      setSceneRect(0, 0, s.width(), s.height());
      QGraphicsView::resizeEvent(e);
      updateTreeRendering();
    }
  }

  GNode *IcicleMorphotreeWidget::gnode(const I32Point &p)
  {
    using NodePtr = typename MTree::NodePtr;

    NodePtr mnode = tree_.smallComponent(domain_.pointToIndex(p));
    return gnodes_[mnode->id()];
  }

  GNode *IcicleMorphotreeWidget::gnode(const QPoint &p)
  {
    return gnode(I32Point{p.x(), p.y()});
  }

  GNode *IcicleMorphotreeWidget::gnode(int x, int y)
  {
    return gnode(I32Point{x, y});
  }

  GNode* IcicleMorphotreeWidget::gnode(const I32Point &p, const QVector<bool> &mask)
  {
    using NodePtr = typename MTree::NodePtr;
    NodePtr node = tree_.smallComponent(domain_.pointToIndex(p), mask.toStdVector());
    return gnodes_[node->id()];
  }

  GNode *IcicleMorphotreeWidget::gnode(const QPoint &p, const QVector<bool> &mask)
  {
    return gnode(I32Point{p.x(), p.y()}, mask);
  }

  GNode *IcicleMorphotreeWidget::gnode(int x, int y, const QVector<bool> &mask)
  {
    return gnode(I32Point{x, y}, mask);
  }

  void IcicleMorphotreeWidget::setGNodeFactory(GNodeFactoryPtr f) 
  {
    f->setTreeVisualiser(this);
    treeLayout_->setGNodeFactory(std::move(f)); 
    updateTreeRendering();
  }
  
}