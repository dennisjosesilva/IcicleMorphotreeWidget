#include "IcicleMorphotreeWidget/Graphics/Node/TessFunctionNodeFactory.hpp"
#include "IcicleMorphotreeWidget/Graphics/Node/TessFunctionNode.hpp"

namespace IcicleMorphotreeWidget
{
  TessFunctionNodeFactory::TessFunctionNodeFactory(IcicleMorphotreeWidget *treeVis,
    float minValue, float maxValue)
  : GNodeFactory{treeVis}, minValue_{minValue}, maxValue_{maxValue}
  { }

  GNode *TessFunctionNodeFactory::create(MTreeNodePtr mnode)
  {
    return new TessFunctionNode{treeVis_, mnode, minValue_, maxValue_};
  }

  TessFunctionNodeFactory::~TessFunctionNodeFactory()
  {}
}