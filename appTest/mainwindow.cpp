#include "mainwindow.hpp"

#include "IcicleMorphotreeWidget/Graphics/GNodeEventHandler.hpp"
#include "IcicleMorphotreeWidget/TreeLayout/TreeLayout.hpp"

#include <morphotree/attributes/areaComputer.hpp>
#include <morphotree/attributes/volumeComputer.hpp>
#include <morphotree/attributes/perimeterComputer.hpp>

#include <morphotree/tree/mtree.hpp>

#include <QMessageBox>
#include <QLabel>

#include <memory>
#include <algorithm>

#include <QToolBar>

#include <QDebug>
#include <QKeyEvent>

#include <QPushButton>

#include <algorithm>

MainWindow::MainWindow(mt::Box domain, const std::vector<mt::uint8> &f)
  :QMainWindow{nullptr}
{
  setWindowTitle("Main Window");
  resize(400, 700);

  layout_ = new QVBoxLayout;
  widget_ = new QWidget{this};
  widget_->setLayout(layout_);

  QHBoxLayout *hlayout = new QHBoxLayout;

  qreal unitHeight = 2.0f;
  qreal unitWidth = 20.f;

  if (domain.numberOfPoints() < 500) {
    // mtreeVis_ = new imt::IcicleMorphotreeWidget{this, 
    //   std::make_unique<imt::FixedHeightTreeLayout>(20.f, 20.f, 50.0f)};

    mtreeVis_ = new imt::IcicleMorphotreeWidget{this, 
      std::make_unique<imt::GrayscaleBasedHeightTreeLayout>(20.f, 20.f, 30.0f)};
      unitHeight = 30.f;
  }
  else {
    // mtreeVis_ = new imt::IcicleMorphotreeWidget{this};
    mtreeVis_ = new imt::IcicleMorphotreeWidget{this, 
      std::make_unique<imt::GrayscaleBasedHeightTreeLayout>(20.f, 20.f, 2.0f)};
      unitWidth= 5.f;
  }

  mtreeVis_->loadImage(domain, f);

  mt::uint8 maxLevel = *std::max_element(f.begin(), f.end());
  // mtreeVis_->addGrayScaleBar(static_cast<unsigned int>(maxLevel)+1, unitWidth,
  //   unitHeight);

  QPushButton *btnPan = new QPushButton{tr("Switch Pan"), this};
  connect(btnPan, &QPushButton::clicked, [this]{ 
    if (mtreeVis_->dragMode() == QGraphicsView::NoDrag) 
      mtreeVis_->setDragMode(QGraphicsView::ScrollHandDrag);
    else
      mtreeVis_->setDragMode(QGraphicsView::NoDrag);
  });

  QPushButton *btnAddGrayScaleBar = new QPushButton{tr("Add GrayScale Bar"), this};
  connect(btnAddGrayScaleBar, &QPushButton::clicked, [unitWidth, unitHeight, maxLevel, this](){
    mtreeVis_->addGrayScaleBar(maxLevel+1, unitWidth, unitHeight);
  });

  QPushButton *btnRemoveGrayScaleBar = new QPushButton{tr("Remove GrayScale Bar"), this};
  connect(btnRemoveGrayScaleBar, &QPushButton::clicked, [unitWidth, unitHeight, maxLevel, this](){
    mtreeVis_->removeGrayScaleBar();
  });
  
  hlayout->addWidget(btnPan);
  hlayout->addWidget(btnAddGrayScaleBar);
  hlayout->addWidget(btnRemoveGrayScaleBar);
  layout_->addItem(hlayout);

  // mtreeVis_->setDragMode(QGraphicsView::DragMode::ScrollHandDrag);
  layout_->addWidget(mtreeVis_);

  connect(imt::GNodeEventHandler::Singleton(), &imt::GNodeEventHandler::mousePress,
    this, &MainWindow::nodeMousePress);

  setCentralWidget(widget_);
}

void MainWindow::nodeMousePress(imt::GNode *node, QGraphicsSceneMouseEvent *e)
{
  using MTree = mt::MorphologicalTree<mt::uint8>;
  using NodePtr = typename MTree::NodePtr;  

  if (mtreeVis_->dragMode() == QGraphicsView::NoDrag) {
    NodePtr mnode = node->mnode();

    node->setSelected(!node->isSelected());
    node->update();

    qDebug() << mnode->id();
  }
}