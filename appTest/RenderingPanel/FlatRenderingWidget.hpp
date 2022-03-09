#pragma once 

#include "IcicleMorphotreeWidget/IcicleMorphotreeWidget.hpp"
#include "RenderingPanel/NodeRenderingWidget.hpp"

#include "IcicleMorphotreeWidget/Graphics/Node/GNodeFactory.hpp"

class FlatRenderingWidget : public NodeRenderingWidget
{
public:
  using FixedColorGNodeFactory = IcicleMorphotreeWidget::FixedColorGNodeFactory;
  using FixedColorGNodeFactoryPtr = std::shared_ptr<FixedColorGNodeFactory>;

  FlatRenderingWidget(TreeVisuliser *treeVis, 
    QWidget *parent=nullptr);
    
protected:
  void setupGNodeFactory();
  QLayout *createMessage();

protected:
  FixedColorGNodeFactoryPtr factory_;
};