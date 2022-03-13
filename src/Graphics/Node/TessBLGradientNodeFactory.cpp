#include "IcicleMorphotreeWidget/Graphics/Node/TessBLGradientNodeFactory.hpp"
#include "IcicleMorphotreeWidget/Graphics/Node/TessBLGradientNode.hpp"

namespace IcicleMorphotreeWidget
{
  TessBLGradientNodeFactory::TessBLGradientNodeFactory(IcicleMorphotreeWidget *treeVis,
    float topLeftProportion, float topRightProportion,
    float bottomLeftProportion, float bottomRightProportion)
    : GNodeFactory{treeVis},
      topLeftProportion_{topLeftProportion},
      topRightProportion_{topRightProportion},
      bottomLeftProportion_{bottomLeftProportion},
      bottomRightProportion_{bottomRightProportion}
  {}

  GNode * TessBLGradientNodeFactory::create(MTreeNodePtr mnode)
  {
    return new TessBLGradientNode{treeVis_, mnode, 
      topLeftProportion_, topRightProportion_,
      bottomLeftProportion_, bottomRightProportion_};
  }

  TessBLGradientNodeFactory::~TessBLGradientNodeFactory() 
  {}  

  // ===================== [ PRESETS ] ==========================================
  TessBLBottomRightLShapedPreset::TessBLBottomRightLShapedPreset(
    float darkerLProportion)
    : darkerLProportion_{darkerLProportion}
  {}

  void TessBLBottomRightLShapedPreset::setUpFactory(TessBLGradientNodeFactoryPtr
    factory)
  {
    factory->setTopLeftProportion(1.0f);
    factory->setTopRightProportion(darkerLProportion_);
    factory->setBottomRightProportion(darkerLProportion_);
    factory->setBottomLeftProportion(darkerLProportion_);
  }

  // ======================= [ PRESET TOP-LEFT ] =================================
  TessBLTopLeftLShapedPreset::TessBLTopLeftLShapedPreset(float darkerLProportion)
    : darkerLProportion_{darkerLProportion}
  {}

  void TessBLTopLeftLShapedPreset::setUpFactory(TessBLGradientNodeFactoryPtr 
    factory)
  {
    factory->setTopLeftProportion(darkerLProportion_);
    factory->setTopRightProportion(darkerLProportion_);
    factory->setBottomLeftProportion(1.0);
    factory->setBottomRightProportion(darkerLProportion_);
  }
}