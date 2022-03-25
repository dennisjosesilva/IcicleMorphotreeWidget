#include "IcicleMorphotreeWidget/Graphics/Node/TessFunctionNodeFactory.hpp"
#include "IcicleMorphotreeWidget/Graphics/Node/TessFunctionNode.hpp"

namespace IcicleMorphotreeWidget
{
  TessFunctionNodeFactory::TessFunctionNodeFactory(IcicleMorphotreeWidget *treeVis,
    float topLeftProportion, float topRightProportion,
    float bottomLeftProportion, float bottomRightProportion,
    float minValue, float maxValue)
  : GNodeFactory{treeVis}, 
    topLeftProportion_{topLeftProportion}, topRightProportion_{topRightProportion},
    bottomLeftProportion_{bottomLeftProportion}, bottomRightProportion_{bottomRightProportion},
    minValue_{minValue}, maxValue_{maxValue}
  { }

  GNode *TessFunctionNodeFactory::create(MTreeNodePtr mnode)
  {
    return new TessFunctionNode{treeVis_, mnode, 
      topLeftProportion_, topRightProportion_,
      bottomLeftProportion_, bottomRightProportion_,
      minValue_, maxValue_};
  }

  TessFunctionNodeFactory::~TessFunctionNodeFactory()
  {}
}