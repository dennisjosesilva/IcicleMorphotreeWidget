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
      float bottomProportion = 0.6f, float rightProportion = 0.3f);

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

  private:
    static void initShaders();

  private:
    float topProportion_;
    float bottomProportion_;
    float leftProportion_;
    float rightProportion_;

  private:
    static QOpenGLShaderProgram *shaderProgram_;
  };
}