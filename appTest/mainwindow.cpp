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

MainWindow::MainWindow(mt::Box domain, const std::vector<mt::uint8> &f)
  :QMainWindow{nullptr}
{
  setWindowTitle("Main Window");
  resize(400, 700);

  layout_ = new QVBoxLayout;
  widget_ = new QWidget{this};
  widget_->setLayout(layout_);


  if (domain.numberOfPoints() < 500) {
    mtreeVis_ = new imt::IcicleMorphotreeWidget{this, 
      std::make_unique<imt::FixedHeightTreeLayout>(20.f, 20.f, 50.0f)};
  }
  else {
    mtreeVis_ = new imt::IcicleMorphotreeWidget{this};
  }

  mtreeVis_->loadImage(domain, f);
  layout_->addWidget(mtreeVis_);

  connect(imt::GNodeEventHandler::Singleton(), &imt::GNodeEventHandler::mousePress,
    this, &MainWindow::nodeMousePress);

  setCentralWidget(widget_);
}

void MainWindow::nodeMousePress(imt::GNode *node, QGraphicsSceneMouseEvent *e)
{
  using MTree = mt::MorphologicalTree<mt::uint8>;
  using NodePtr = typename MTree::NodePtr;

  NodePtr mnode = node->mnode();

  node->setSelected(!node->isSelected());
  node->update();

  qDebug() << mnode->id();
}