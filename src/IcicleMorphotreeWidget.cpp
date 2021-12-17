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
     tree_{morphotree::MorphoTreeType::MaxTree},
     treeLayout_{std::move(treeLayout)},
     grayScaleBar_{nullptr},
     colorMap_{std::make_unique<RainbowColorMap>()}     
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
    painter->drawRect(sceneRect());
  }

  void IcicleMorphotreeWidget::updateTreeRendering()
  {
    if (grayScaleBar_ != nullptr) {
      // backup grayscaleBar before it is deleted by scene()->clear()
      
      QPointF pos = grayScaleBar_->pos();
      bool showBorders = grayScaleBar_->showBorders();

      grayScaleBar_ =  new GrayScaleBar{grayScaleBar_->unitWidth(), 
        grayScaleBar_->unitHeight(), grayScaleBar_ ->numberOfLevels()};      
      grayScaleBar_->setPos(pos);
      grayScaleBar_->setShowBorders(showBorders);
    }
    
    // It deletes all items including grayscaleBar_
    scene()->clear();    

    gnodes_.clear();
    gnodes_.resize(tree_.numberOfNodes());

    treeLayout_->parseTree(tree_);
    scene()->update();

    if (grayScaleBar_ != nullptr) {
      scene()->addItem(grayScaleBar_);
      renderGrayScaleBar();
    }
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
    qreal unitWidth, qreal unitHeight)
  {
    if (grayScaleBar_ == nullptr)  {
      grayScaleBar_ = new GrayScaleBar{unitWidth, unitHeight, numberOfLevels};
      grayScaleBar_->setPos(-unitWidth-5, 0);
      scene()->addItem(grayScaleBar_);
      renderGrayScaleBar();
    }
  }

  void IcicleMorphotreeWidget::removeGrayScaleBar()
  {
    if (grayScaleBar_ != nullptr) {
      scene()->removeItem(grayScaleBar_);
      qreal unitWidth = grayScaleBar_->unitWidth();
      grayScaleBar_ = nullptr;
      const QRectF &sceneRect = scene()->sceneRect();      
      scene()->setSceneRect(0, 0, sceneRect.width()-unitWidth, sceneRect.height());
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

      scene()->setSceneRect(-grayScaleBar_->unitWidth()-20, 0, s.width(), s.height());
      updateTreeRendering();
      if (treeLayout_->type() == TreeLayoutType::AutoSize) {
        AutoSizeTLPtr t = std::dynamic_pointer_cast<AutoSizeTreeLayout>(treeLayout_);
        grayScaleBar_->setUnitHeight(t->unitHeight());
        renderGrayScaleBar();
      }
    }
    else {
      scene()->setSceneRect(0, 0, s.width(), s.height());
      updateTreeRendering();
    }
        
    QWidget::resizeEvent(e);
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