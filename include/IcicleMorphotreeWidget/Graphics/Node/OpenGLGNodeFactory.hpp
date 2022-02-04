#pragma once

#include "IcicleMorphotreeWidget/Graphics/Node/GNodeFactory.hpp"

class QOpenGLShaderProgram;

namespace IcicleMorphotreeWidget
{
  class OpenGLGNodeFactory : public GNodeFactory 
  {
  public:
    OpenGLGNodeFactory(IcicleMorphotreeWidget *treeVis = nullptr, 
      float topProportion=0.5f, float leftProportion = 0.4f, 
      float bottomProportion=0.5f, float rightPorportion=0.4f);

    float topProportion() const { return topProportion_; }
    float &topProportion() { return topProportion_; }
    void setTopProportion(float val) { topProportion_ = val; }

    float leftProportion() const { return leftProportion_; }
    float &leftProportion() { return leftProportion_; }
    void setLeftProportion(float val) { leftProportion_ = val; }

    float bottomProportion() const { return bottomProportion_; }
    float &bottomProportion() { return bottomProportion_; }
    void setBottomProportion(float val) { bottomProportion_ = val; }

    float rightProportion() const { return rightProportion_; }
    float &rightProportion() { return rightProportion_; }
    void setRightProportion(float val) { rightProportion_ = val; }

    GNodeStyle style() const override { return GNodeStyle::BilinearGradientColor; }

    GNode *create(MTreeNodePtr mnode = nullptr) override;

    virtual ~OpenGLGNodeFactory();

  private:
    float topProportion_;
    float leftProportion_;
    float bottomProportion_;
    float rightProportion_;
  };
}