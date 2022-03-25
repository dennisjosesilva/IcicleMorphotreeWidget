#pragma once 

#include "IcicleMorphotreeWidget/Graphics/Node/GNodeFactory.hpp"

namespace IcicleMorphotreeWidget
{
  class TessFunctionNodeFactory : public GNodeFactory
  {
  public:
    TessFunctionNodeFactory(IcicleMorphotreeWidget *treeVis = nullptr,
      float topLeftProportion=1.0f, float topRightProportion=1.0f,
      float bottomLeftProportion=1.0f, float bottomRightProportion=1.0f,
      float minValue=0.75f, float maxValue=1.0f);

    float minValue() const { return minValue_; }
    float &minValue() { return minValue_; }
    void setMinValue(float val) { minValue_ = val; }

    float maxValue() const { return maxValue_; }
    float &maxValue() { return maxValue_; }
    void setMaxValue(float val) { maxValue_ = val; }

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

    GNodeStyle style() const override { return GNodeStyle::BilinearGradientColor; }

    GNode *create(MTreeNodePtr mnode = nullptr) override;

    virtual ~TessFunctionNodeFactory();

  private:
    float minValue_;
    float maxValue_;

    float topLeftProportion_;
    float topRightProportion_;
    float bottomLeftProportion_;
    float bottomRightProportion_;
  };
}