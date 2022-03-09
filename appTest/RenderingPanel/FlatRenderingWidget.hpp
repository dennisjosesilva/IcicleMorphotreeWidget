#pragma once 

#include "IcicleMorphotreeWidget/IcicleMorphotreeWidget.hpp"
#include "RenderingPanel/NodeRenderingWidget.hpp"

class FlatRenderingWidget : public NodeRenderingWidget
{
public:
  FlatRenderingWidget(IcicleMorphotreeWidget *treeVis, 
    QWidget *parent=nullptr);
    
protected:
  QLayout *createMessage();  
};