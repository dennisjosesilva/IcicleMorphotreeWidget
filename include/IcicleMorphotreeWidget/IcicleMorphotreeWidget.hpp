#pragma once 

#include <QGraphicsView>

#include <morphotree/core/alias.hpp>
#include <morphotree/core/box.hpp>
#include <morphotree/tree/mtree.hpp>

#include "IcicleMorphotreeWidget/TreeLayout/TreeLayout.hpp"
#include "IcicleMorphotreeWidget/Graphics/GrayScaleBar.hpp"

namespace IcicleMorphotreeWidget
{
  class IcicleMorphotreeWidget : public QGraphicsView
  {
  public:
    using Box = morphotree::Box;
    using uint8 = morphotree::uint8;
    using MTree = morphotree::MorphologicalTree<uint8>;
    using TreeLayoutPtr = std::unique_ptr<TreeLayout>;

    IcicleMorphotreeWidget(QWidget *parent = nullptr, 
      TreeLayoutPtr treeLayout=std::make_unique<FixedHeightTreeLayout>());

    void drawBackground(QPainter *painter, const QRectF &rect) override;

    void updateTreeRendering();

    void loadImage(Box domain, const std::vector<uint8> &f);

    void scaleView(qreal scaleFactor);
    void visZoomIn();
    void visZoomOut();

    void addGrayScaleBar(unsigned int numberOfLevels=256, qreal unitWidth=20, 
      qreal unitHeight = 5.0f);
    void removeGrayScaleBar();

  protected:
    void keyPressEvent(QKeyEvent *e) override;

  private:
    TreeLayoutPtr treeLayout_;
    Box domain_;
    MTree tree_;
    GrayScaleBar *grayScaleBar_;
  };
}