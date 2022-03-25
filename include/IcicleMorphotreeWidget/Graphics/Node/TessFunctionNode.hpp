#pragma once 

#include "IcicleMorphotreeWidget/Graphics/Node/GNode.hpp"

class QOpenGLShaderProgram;

namespace IcicleMorphotreeWidget
{
  // Tessellation Based on a function Node
  class TessFunctionNode : public GNode 
  {
  public:
    enum {
      SHADER_PROGRAM_POSITION_ATTR_LOC = 0,
      SHADER_PROGRAM_COLOR_ATTR_LOC = 1
    };

    TessFunctionNode(IcicleMorphotreeWidget *treeVis, MTreeNodePtr mnode=nullptr,
      float topLeftProportion=1.0f, float topRightProportion=1.0f,
      float botomLeftProportion=1.0f, float bottomRightProportion=1.0f,
      float minValue=0.7f, float maxValue=1.0f);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *options,
      QWidget *widget) override;

    float maxValue() const { return maxValue_; }
    float &maxValue() { return maxValue_; }
    void setMaxValue(float val) { maxValue_ = val; }

    float minValue() const { return minValue_; }
    float &minValue() { return minValue_; }
    void setMinValue(float val) { minValue_ = val; }

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
    float maxValue_;
    float minValue_;

    float topLeftProportion_;
    float topRightProportion_;
    float bottomLeftProportion_;
    float bottomRightProportion_;

    static QOpenGLShaderProgram *shaderProgram_;
  };
}