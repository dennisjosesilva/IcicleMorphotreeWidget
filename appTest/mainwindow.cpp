#include "mainwindow.hpp"

#include "IcicleMorphotreeWidget/Graphics/Node/GNodeEventHandler.hpp"
#include "IcicleMorphotreeWidget/TreeLayout/TreeLayout.hpp"
#include "IcicleMorphotreeWidget/TreeLayout/AutoSizeTreeLayout.hpp"

#include "IcicleMorphotreeWidget/Graphics/Node/OpenGLGNodeFactory.hpp"
#include "IcicleMorphotreeWidget/Graphics/Node/TessBLGradientNodeFactory.hpp"
#include "IcicleMorphotreeWidget/Filtering/AreaTreeFiltering.hpp"

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
#include <memory>
#include <algorithm>

#include "RenderingPanel/RenderingPanel.hpp"

MainWindow::MainWindow(mt::Box domain, const std::vector<mt::uint8> &f)
  : QMainWindow{nullptr}, colorBar_{nullptr}, 
    gradientNodeStyle_{imt::GNodeStyle::BilinearGradientColor}
{
  using AreaTreeFiltering = IcicleMorphotreeWidget::AreaTreeFiltering;

  setWindowTitle("Main Window");
  resize(400, 700);

  layout_ = new QHBoxLayout;
  
  QLayout *treeVisLayout = new QVBoxLayout; 

  QLayout *nodeRenderingLayout = new QVBoxLayout;

  widget_ = new QWidget{this};
  widget_->setLayout(layout_);

  QHBoxLayout *hlayout = new QHBoxLayout;

  qreal unitHeight = 2.0f;
  qreal unitWidth = 20.f;

  if (domain.numberOfPoints() < 500) {
    // mtreeVis_ = new imt::IcicleMorphotreeWidget{this, 
    //   std::make_unique<imt::FixedHeightTreeLayout>(20.f, 20.f, 50.0f)};

    // mtreeVis_ = new imt::IcicleMorphotreeWidget{this, 
    //   std::make_unique<imt::GrayscaleBasedHeightTreeLayout>(
    //     std::make_unique<imt::GradientGNodeFactory>(), 20.f, 20.f, 30.0f)};
    //   unitHeight = 30.f;

    // mtreeVis_ = new imt::IcicleMorphotreeWidget{this,
    //   std::make_unique<imt::AutoSizeTreeLayout>(
    //     std::make_unique<imt::HGradientGNodeFactory>(), 0.0f, 0.0f)};
    
    auto gminmax =  std::minmax_element(f.begin(), f.end());
    imt::GrayScaleProfile gp{imt::Range{*gminmax.first, *gminmax.second}, 
      imt::Range{*gminmax.first, *gminmax.second}};

    //imt::GrayScaleProfile gp;

    // mtreeVis_ = new imt::IcicleMorphotreeWidget{
    //   gp, this, 
    //   std::make_shared<imt::AutoSizeTreeLayout>(
    //     std::make_shared<imt::TessBLGradientNodeFactory>(), gp)};
    mtreeVis_ = new imt::IcicleMorphotreeWidget{
      gp, this, std::make_shared<imt::AutoSizeTreeLayout>(
        std::make_shared<imt::FixedColorGNodeFactory>(), gp)};
    unitHeight = 30.f;
  }
  else {
    // mtreeVis_ = new imt::IcicleMorphotreeWidget{this};
    // mtreeVis_ = new imt::IcicleMorphotreeWidget{this, 
    //   std::make_unique<imt::GrayscaleBasedHeightTreeLayout>(
    //     std::make_unique<imt::GradientGNodeFactory>(), 20.f, 20.f, 2.0f)};
    // mtreeVis_ = new imt::IcicleMorphotreeWidget{this, 
    //   std::make_unique<imt::AutoSizeTreeLayout>(
    //     std::make_unique<imt::HGradientGNodeFactory>(), 0.0f, 0.0f)};
    imt::GrayScaleProfile gp;
    // mtreeVis_ = new imt::IcicleMorphotreeWidget{gp, this, 
    //   std::make_shared<imt::AutoSizeTreeLayout>(
    //     std::make_shared<imt::OpenGLGNodeFactory>(), gp)};

    // mtreeVis_ = new imt::IcicleMorphotreeWidget{gp, this, 
    //   std::make_shared<imt::AutoSizeTreeLayout>(
    //     std::make_shared<imt::TessBLGradientNodeFactory>(), gp)};
    mtreeVis_ = new imt::IcicleMorphotreeWidget{gp, this, 
      std::make_shared<imt::AutoSizeTreeLayout>(
          std::make_shared<imt::FixedColorGNodeFactory>(), gp)};
    unitWidth= 5.f;
  }


  // std::unique_ptr<imt::Preset> preset = 
    //std::make_unique<imt::DefaultPreset>();
    //std::make_unique<imt::FlatPreset>();
    //std::make_unique<imt::VerticalPreset>();
    //std::make_unique<imt::HorinzontalPreset>();
    //std::make_unique<imt::SymmetricTentLikeCushion>();
    // std::make_unique<imt::AsymetricTentLikeCushion>();
  
  // preset->setUpFactory(std::dynamic_pointer_cast<imt::OpenGLGNodeFactory>(mtreeVis_->gnodeFactory()));

  // imt::GrayScaleProfile gp;
  // mtreeVis_->setGrayScaleProfile(gp);
  mtreeVis_->loadImage(domain, f, imt::MorphoTreeType::MAX_TREE_8C);
  
  mtreeVis_->setNodeSelectionColor(Qt::red);
  connect(mtreeVis_, &imt::IcicleMorphotreeWidget::treeAboutToBeRedrawn, [](){
    qDebug() << "about to be drawn";
  });
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
  connect(btnAddGrayScaleBar, &QPushButton::clicked, [unitWidth, unitHeight, this](){
    std::vector<mt::uint8> frec = mtreeVis_->recImage();    
    mt::uint8 maxLevel = *std::max_element(frec.begin(), frec.end());

    std::shared_ptr<imt::AutoSizeTreeLayout> treeLayout = 
      std::dynamic_pointer_cast<imt::AutoSizeTreeLayout>(mtreeVis_->treeLayout());

    mtreeVis_->addGrayScaleBar(maxLevel+1, unitWidth);

    if (gradientNodeStyle_ == imt::GNodeStyle::FixedColor)
      mtreeVis_->grayscaleBar()->setShowBorders(false);
    else 
      mtreeVis_->grayscaleBar()->setShowBorders(true);
  });

  QPushButton *btnRemoveGrayScaleBar = new QPushButton{tr("Remove GrayScale Bar"), this};
  connect(btnRemoveGrayScaleBar, &QPushButton::clicked, [unitWidth, unitHeight, this](){
    mtreeVis_->removeGrayScaleBar();
  });

  QPushButton *btnShowAttribute = new QPushButton{tr("Toggle attribute visualisation"), this};
  connect(btnShowAttribute, &QPushButton::clicked, this, &MainWindow::visualiseAttributesAct_onTrigger);
  
  QPushButton *btnAreaFilter = new QPushButton{tr("Area filter"), this};
  connect(btnAreaFilter, &QPushButton::clicked, [this](){
    if (mtreeVis_->hasAttributes()) {
      layout_->removeWidget(colorBar_);
      colorBar_->deleteLater();
      colorBar_ = nullptr;
    }

    mtreeVis_->ifilter(std::make_shared<AreaTreeFiltering>(500));        
  });

  QPushButton *btnChangeNodeStyle = new QPushButton{tr("Change Node Style"), this};
  connect(btnChangeNodeStyle, &QPushButton::clicked, [this]{
    if (gradientNodeStyle_ == imt::GNodeStyle::BilinearGradientColor){
      mtreeVis_->setGNodeFactory(std::make_unique<imt::FixedColorGNodeFactory>());
      gradientNodeStyle_ = imt::GNodeStyle::FixedColor;

      if (mtreeVis_->grayscaleBar() != nullptr)
        mtreeVis_->grayscaleBar()->setShowBorders(true);              
    }
    else if (gradientNodeStyle_ == imt::GNodeStyle::FixedColor) {
      
      if (mtreeVis_->treeLayout()->orientation() == imt::TreeLayoutOrientation::Horizontal)
        mtreeVis_->setGNodeFactory(std::make_unique<imt::VGradientGNodeFactory>());
      else 
        mtreeVis_->setGNodeFactory(std::make_unique<imt::HGradientGNodeFactory>());
      
      gradientNodeStyle_ = imt::GNodeStyle::GradientColor;

      if (mtreeVis_->grayscaleBar() != nullptr)
        mtreeVis_->grayscaleBar()->setShowBorders(true);              
    }
    else if (gradientNodeStyle_ == imt::GNodeStyle::GradientColor) {
      mtreeVis_->setGNodeFactory(std::make_unique<imt::OpenGLGNodeFactory>());
      gradientNodeStyle_ = imt::GNodeStyle::BilinearGradientColor;
      
      if (mtreeVis_->grayscaleBar() != nullptr)
        mtreeVis_->grayscaleBar()->setShowBorders(false);              
    }
  });

  QPushButton *btnRotateWidget = new QPushButton{tr("Rotate"), this};
  connect(btnRotateWidget, &QPushButton::clicked, [this]{
    using TreeLayoutOrientation = IcicleMorphotreeWidget::TreeLayoutOrientation;

    if (mtreeVis_->orientation() == TreeLayoutOrientation::Horizontal) {
      mtreeVis_->setOrientation(TreeLayoutOrientation::Vertical);
    }
    else {
      mtreeVis_->setOrientation(TreeLayoutOrientation::Horizontal);
    }
  });

  QPushButton *btnToggleMTreeType = new QPushButton{tr("Toggle tree type"), this};
  connect(btnToggleMTreeType, &QPushButton::clicked, [this]{
    if (mtreeVis_->treeType() == imt::MorphoTreeType::MAX_TREE_8C)
      mtreeVis_->setTreeType(imt::MorphoTreeType::MIN_TREE_8C);
    else 
      mtreeVis_->setTreeType(imt::MorphoTreeType::MAX_TREE_8C);
  });

  QPushButton *btnGreyscaleRender = new QPushButton{tr("Toggle greyscale node render"), this};
  connect(btnGreyscaleRender, &QPushButton::clicked, [this]{
    if (mtreeVis_->isGrayscaleNodeRenderActivated()) 
      mtreeVis_->deactivactedGrayscaleNodeRender();
    else 
      mtreeVis_->activateGrayscaleNodeRender();
    mtreeVis_->updateTreeRendering();
  });


  hlayout->addWidget(btnShowAttribute);
  hlayout->addWidget(btnPan);
  hlayout->addWidget(btnAreaFilter);
  hlayout->addWidget(btnAddGrayScaleBar);
  hlayout->addWidget(btnRemoveGrayScaleBar);
  hlayout->addWidget(btnChangeNodeStyle);
  hlayout->addWidget(btnRotateWidget);
  hlayout->addWidget(btnToggleMTreeType);
  hlayout->addWidget(btnGreyscaleRender);
  treeVisLayout->addItem(hlayout);
  treeVisLayout->addItem(createUniHeightControls(unitHeight));

  // Rendering Panel
  RenderingPanel *renderingPanel = new RenderingPanel{mtreeVis_, 
    this};
  nodeRenderingLayout->addWidget(renderingPanel);

  // mtreeVis_->setDragMode(QGraphicsView::DragMode::ScrollHandDrag);
  treeVisLayout->addWidget(mtreeVis_);
  // nodeRenderingLayout

  layout_->addItem(treeVisLayout);
  layout_->addItem(nodeRenderingLayout);

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

    // node->setOpacity(0.2f);

    node->setSelected(!node->isSelected());
    node->setOpacity(0.75f);
    node->update();

    
    qDebug() << mnode->id();
  }
}

QLayout* MainWindow::createUniHeightControls(float initialUniHeight)
{
  QHBoxLayout *layout = new QHBoxLayout;
  uniHeightLabel_ = new QLabel{tr("unit node height: "), this};
  layout->addWidget(uniHeightLabel_);

  uniHeightSlider_ = new QSlider{this};
  uniHeightSlider_->setOrientation(Qt::Horizontal);
  uniHeightSlider_->setRange(1, 50);
  uniHeightSlider_->setValue(static_cast<int>(initialUniHeight));
  connect(uniHeightSlider_, &QSlider::sliderMoved, this, 
    &MainWindow::uniHeightSlider_onSliderMoved);
  layout->addWidget(uniHeightSlider_);

  uniHeightLineEdit_ = new QLineEdit{this};
  uniHeightLineEdit_->setText(QString::number(initialUniHeight));
  connect(uniHeightLineEdit_, &QLineEdit::editingFinished, this, 
    &MainWindow::uniHeightLineEdit_onEditingFinishing);
  layout->addWidget(uniHeightLineEdit_);

  return layout;
}

void MainWindow::visualiseAttributesAct_onTrigger()
{
  namespace mt = morphotree;
  using AreaComp = mt::AreaComputer<mt::uint8>;
  using VolumeComp = mt::VolumeComputer<mt::uint8>;
  using MTree = mt::MorphologicalTree<mt::uint8>;
  using NodePtr = typename MTree::NodePtr;
  using VColorBar = imt::VColorBar;
  using HColorBar = imt::HColorBar;

  using MinMaxVol = std::pair<std::vector<float>::iterator, std::vector<float>::iterator>;


  if (mtreeVis_->hasAttributes()) {
    mtreeVis_->clearAttributes();
    layout_->removeWidget(colorBar_);
    colorBar_->deleteLater();
    colorBar_ = nullptr;
  }
  else {
    const MTree &tree = mtreeVis_->mtree();
    std::vector<float> vol = 
      std::make_unique<VolumeComp>()->computeAttribute(tree);

    std::unique_ptr<std::vector<float>> nvol = 
      std::make_unique<std::vector<float>>(vol.size());

    MinMaxVol minMaxVol = std::minmax_element(vol.begin(), vol.end());

    float volMax = *minMaxVol.second;
    float volMin = *minMaxVol.first;
    for (mt::uint32 i = 0; i < vol.size(); ++i) {
      (*nvol)[i] = (vol[i] - volMin) / (volMax - volMin);      
    }

    mtreeVis_->loadAttributes(std::move(nvol));

    HColorBar *colorBar = qobject_cast<HColorBar*>(mtreeVis_->createHColorBar(this));

    colorBar->setMaxValue(volMax);
    colorBar->setMinValue(volMin);
    colorBar->setShowNumbers(true);
    layout_->addWidget(colorBar);
    colorBar_ = colorBar;
  }
}

void MainWindow::uniHeightSlider_onSliderMoved(int value)
{
  uniHeightLineEdit_->setText(QString::number(value));
  applyTreeLayoutChange();
}

void MainWindow::uniHeightLineEdit_onEditingFinishing()
{
  float uniHeightVal = uniHeightLineEdit_->text().toFloat();
  if (uniHeightSlider_->minimum() <= uniHeightVal && uniHeightVal <= uniHeightSlider_->maximum()) {
    uniHeightSlider_->setValue(uniHeightVal);
    applyTreeLayoutChange();
  }
  else {
    uniHeightLineEdit_->setText(QString::number(uniHeightSlider_->value()));
  }
}

void MainWindow::applyTreeLayoutChange()
{
  using TreeLayout = imt::TreeLayout;
  using TreeLayoutPtr = std::shared_ptr<TreeLayout>;
  using GrayScaleBasedHeightTreeLayout = imt::GrayscaleBasedHeightTreeLayout;
  using GrayScaleBasedHeightTreeLayoutPtr = std::shared_ptr<GrayScaleBasedHeightTreeLayout>;

  
  GrayScaleBasedHeightTreeLayoutPtr treeLayout  = 
    std::dynamic_pointer_cast<GrayScaleBasedHeightTreeLayout>(mtreeVis_->treeLayout());
  
  float uniHeight = uniHeightLineEdit_->text().toFloat();
  treeLayout->setUniHeight(uniHeight);
  
  if (mtreeVis_->grayscaleBar() != nullptr)
    mtreeVis_->grayscaleBar()->setUnitHeight(uniHeight);

  mtreeVis_->updateTreeRendering();
}