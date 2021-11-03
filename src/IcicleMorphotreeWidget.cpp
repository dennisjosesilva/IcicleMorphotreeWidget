#include "IcicleMorphotreeWidget/IcicleMorphotreeWidget.hpp"

#include <morphotree/adjacency/adjacency8c.hpp>

#include <QKeyEvent>

namespace IcicleMorphotreeWidget 
{
  IcicleMorphotreeWidget::IcicleMorphotreeWidget(QWidget *parent,
    TreeLayoutPtr treeLayout)
    :QGraphicsView{parent},
     tree_{morphotree::MorphoTreeType::MaxTree},
     treeLayout_{std::move(treeLayout)},
     grayScaleBar_{nullptr}     
  {
    QGraphicsScene *scene = new QGraphicsScene{this};
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

  void IcicleMorphotreeWidget::drawBackground(QPainter *painter, 
    const QRectF &rect)
  {
    painter->setBrush(Qt::white);
    painter->drawRect(sceneRect());
  }

  void IcicleMorphotreeWidget::updateTreeRendering()
  {
    scene()->clear();
    treeLayout_->parseTree(tree_);
    scene()->update();
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
      grayScaleBar_->setPos(-unitWidth, 0);
      const QRectF &sceneRect = scene()->sceneRect();      
      scene()->setSceneRect(-unitWidth, 0, sceneRect.width()+unitWidth, sceneRect.height());
      scene()->addItem(grayScaleBar_);
      scene()->update();
      update();
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

    default:
      break;
    }
  }
}