#pragma once 

#include "IcicleMorphotreeWidget/Graphics/Node/GNode.hpp"

class QOpenGLShaderProgram;

void loadQtResources();

namespace IcicleMorphotreeWidget
{
  class OpenGLGNode : public GNode
  {
  public:
    enum {
      SHADER_PROGRAM_POSITION_ATTR_LOC = 0,
      SHADER_PROGRAM_COLOR_ATTR_LOC = 1
    };

    OpenGLGNode(IcicleMorphotreeWidget *treeVis, MTreeNodePtr mnode = nullptr, 
      float topProportion = 0.6f, float leftProportion = 0.3f, 
      float bottomProportion = 0.6f, float rightProportion = 0.3f,
      float centerProportion = 1.0f,
      float topLeftProportion = 0.6f, float topRightProportion = 0.6f,
      float bottomLeftProportion = 0.6f, float bottomRightProportion = 0.6f);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *options, 
      QWidget *widget) override;

    float topProportion() const { return topProportion_; }
    float &topProportion() { return topProportion_; }
    void setTopProportion(float val) { topProportion_ = val; }

    float bottomProportion() const { return bottomProportion_; }
    float &bottomProportion() { return bottomProportion_; }
    void setBottomProportion(float val) { bottomProportion_ = val; }

    float leftProportion() const { return leftProportion_; }
    float &leftProportion() { return leftProportion_; }
    void setLeftProportion(float val) { leftProportion_ = val; }

    float rightProportion() const { return rightProportion_; }
    float &rightProportion() { return rightProportion_; }
    void setRightProportion(float val) { rightProportion_ = val; }

    float centerProportion() const { return centerProportion_; }
    float &centerProportion() { return centerProportion_; }
    void setCenterProportion(float val) { centerProportion_ = val; }

    float topLeftProportion() const { return topLeftProportion_; }
    float &topLeftProportion() { return topLeftProportion_; }
    void setTopLeftProportion(float val) { topLeftProportion_ = val; }

    float topRightProportion() const { return topRightProportion_; }
    float &topRightProportion() { return topRightProportion_; }
    void setTopRightProportion(float val) { topRightProportion_ = val; }

    float bottomLeftProportion() const { return bottomLeftProportion_; }
    float &bottomLeftProportion() { return bottomLeftProportion_; }
    void setBottomLeftProportion(float val) { bottomLeftProportion_ = val; }

    float bottomRightProportion() const { return bottomRightProportion_; }
    float &bottomRightProportion() { return bottomRightProportion_; }
    void setBottomRightProportion(float val) { bottomRightProportion_ = val; }

  private:
    static void initShaders();

  private:
    float topProportion_;
    float bottomProportion_;
    float leftProportion_;
    float rightProportion_;

    float centerProportion_;
    float topLeftProportion_;
    float topRightProportion_;
    float bottomLeftProportion_;
    float bottomRightProportion_;

  private:
    static QOpenGLShaderProgram *shaderProgram_;
  };
}