#include "IcicleMorphotreeWidget/Graphics/Node/OpenGLGNodeFactory.hpp"
#include "IcicleMorphotreeWidget/Graphics/Node/OpenGLGNode.hpp"

#include <QOpenGLShaderProgram>

namespace IcicleMorphotreeWidget
{
  OpenGLGNodeFactory::OpenGLGNodeFactory(IcicleMorphotreeWidget *treeVis,
    float topProportion, float leftProportion, 
    float bottomProportion, float rightProportion)
    : GNodeFactory{treeVis},
      topProportion_{topProportion},
      leftProportion_{leftProportion},
      bottomProportion_{bottomProportion},
      rightProportion_{rightProportion}
  {
    centerProportion_ = 1.0f;
    topLeftProportion_ = (topProportion_ + leftProportion_) / 2.0f;
    topRightProportion_ = (topProportion_ + rightProportion_) / 2.0f;
    bottomLeftProportion_ = (bottomProportion_ + leftProportion_) / 2.0f;
    bottomRightProportion_ = (bottomProportion_ + rightProportion_) / 2.0f;
  }
  
  GNode *OpenGLGNodeFactory::create(MTreeNodePtr mnode)
  {
    return new OpenGLGNode{treeVis_, mnode, topProportion_, 
      leftProportion_, bottomProportion_, rightProportion_, centerProportion_,
      topLeftProportion_, topRightProportion_,
      bottomLeftProportion_, bottomRightProportion_};
  }

  OpenGLGNodeFactory::~OpenGLGNodeFactory()
  {}

  // ========================== [ Default Preset ] =======================================
  DefaultPreset::DefaultPreset(float topProportion, float leftProportion, 
    float rightProportion, float bottomProportion)
    : topProportion_{topProportion}, leftProportion_{leftProportion},
      rightProportion_{rightProportion}, bottomProportion_{bottomProportion}
  {}

  void DefaultPreset::setUpFactory(GNodeFactoryPtr factory)
  {
    factory->setTopProportion(topProportion_);
    factory->setLeftProportion(leftProportion_);
    factory->setRightProportion(rightProportion_);
    factory->setBottomProportion(bottomProportion_);

    factory->setTopLeftProportion((topProportion_ + leftProportion_) / 2.0f);
    factory->setTopRightProportion((topProportion_ + rightProportion_) / 2.0f);
    factory->setBottomLeftProportion((bottomProportion_ + leftProportion_) / 2.0f);
    factory->setBottomRightProportion((bottomProportion_ + rightProportion_) / 2.0f);
  }

  // =================== [ Flat Preset ] ================================================
  FlatPreset::FlatPreset()
  {}

  void FlatPreset::setUpFactory(GNodeFactoryPtr factory)
  {
    factory->setTopProportion(1.0f);
    factory->setLeftProportion(1.0f);
    factory->setRightProportion(1.0f);
    factory->setBottomProportion(1.0f);

    factory->setTopLeftProportion(1.0f);
    factory->setTopRightProportion(1.0f);
    factory->setBottomLeftProportion(1.0f);
    factory->setBottomRightProportion(1.0f);
  }

  // ================== [ Vertical Preset ] =============================================
  VerticalPreset::VerticalPreset(float topProportion, float bottomProportion)
    :topProportion_{topProportion}, bottomProportion_{bottomProportion}
  {}

  void VerticalPreset::setUpFactory(GNodeFactoryPtr factory)
  {
    factory->setTopLeftProportion(topProportion_);
    factory->setTopProportion(topProportion_);
    factory->setTopRightProportion(topProportion_);

    factory->setBottomLeftProportion(bottomProportion_);
    factory->setBottomProportion(bottomProportion_);
    factory->setBottomRightProportion(bottomProportion_);

    float mean = (topProportion_ + bottomProportion_) / 2.0f;

    factory->setLeftProportion(mean);
    factory->setCenterProportion(mean);
    factory->setRightProportion(mean);
  }

  // ================ [ Horizontal Preset ] ===============================================
  HorinzontalPreset::HorinzontalPreset(float leftProportion, float rightProportion)
    :leftProportion_{leftProportion}, rightProportion_{rightProportion}
  {}

  void HorinzontalPreset::setUpFactory(GNodeFactoryPtr factory)
  {
    factory->setTopLeftProportion(leftProportion_);
    factory->setLeftProportion(leftProportion_);
    factory->setBottomLeftProportion(leftProportion_);

    factory->setTopRightProportion(rightProportion_);
    factory->setRightProportion(rightProportion_);
    factory->setBottomRightProportion(rightProportion_);

    float mean = (leftProportion_ + rightProportion_) / 2.0f;

    factory->setTopProportion(mean);
    factory->setCenterProportion(mean);
    factory->setBottomProportion(mean);
  }

  // =================== [ Symmetric Tent-Like Cushion ] ====================================
  SymmetricTentLikeCushion::SymmetricTentLikeCushion(float cornerProportion, 
    float sideProportion) 
    : cornerProportion_{cornerProportion}, sideProportion_{sideProportion}
  {}

  void SymmetricTentLikeCushion::setUpFactory(GNodeFactoryPtr factory)
  {
    factory->setCenterProportion(1.0f);

    factory->setTopProportion(sideProportion_);
    factory->setLeftProportion(sideProportion_);
    factory->setRightProportion(sideProportion_);
    factory->setBottomProportion(sideProportion_);

    factory->setTopLeftProportion(cornerProportion_);
    factory->setTopRightProportion(cornerProportion_);
    factory->setBottomLeftProportion(cornerProportion_);
    factory->setBottomRightProportion(cornerProportion_);
  }

  // ====================== [ Assymetric Tent-Like Cushion ] ==================================
  AsymetricTentLikeCushion::AsymetricTentLikeCushion(float cornerProportion, float sideProportion,
    float increasePorportion)
    : SymmetricTentLikeCushion{cornerProportion, sideProportion}, 
      increaseProportion_{increasePorportion}
  { }

  void AsymetricTentLikeCushion::setUpFactory(GNodeFactoryPtr factory)
  {
    factory->setCenterProportion(1.0f);

    factory->setTopProportion(sideProportion_);
    factory->setLeftProportion(sideProportion_);
    factory->setRightProportion(sideProportion_);
    factory->setBottomProportion(sideProportion_);

    factory->setTopLeftProportion(cornerProportion_);
    factory->setTopRightProportion(cornerProportion_ * increaseProportion_);
    factory->setBottomLeftProportion(cornerProportion_ * increaseProportion_);
    factory->setBottomRightProportion(cornerProportion_ * increaseProportion_);
  }
}