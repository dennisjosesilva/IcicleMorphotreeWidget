#pragma once 

#include "IcicleMorphotreeWidget/Graphics/Node/GNodeFactory.hpp"

namespace IcicleMorphotreeWidget
{
  class TessFunctionNodeFactory : public GNodeFactory
  {
  public:
    TessFunctionNodeFactory(IcicleMorphotreeWidget *treeVis = nullptr,
      float minValue=0.75f, float maxValue=1.0f);

    float minValue() const { return minValue_; }
    float &minValue() { return minValue_; }
    void setMinValue(float val) { minValue_ = val; }

    float maxValue() const { return maxValue_; }
    float &maxValue() { return maxValue_; }
    void setMaxValue(float val) { maxValue_ = val; }

    GNodeStyle style() const override { return GNodeStyle::BilinearGradientColor; }

    GNode *create(MTreeNodePtr mnode = nullptr) override;

    virtual ~TessFunctionNodeFactory();

  private:
    float minValue_;
    float maxValue_;
  };
}