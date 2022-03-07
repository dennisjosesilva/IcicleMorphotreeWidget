#pragma once 

#include "IcicleMorphotreeWidget/Graphics/Node/GNodeFactory.hpp"

namespace IcicleMorphotreeWidget
{
  class TessBLGradientNodeFactory : public GNodeFactory
  {
  public:
    TessBLGradientNodeFactory(IcicleMorphotreeWidget *treeVis = nullptr,
      float topLeftProportion=0.9f, float topRightProportion=0.7f,
      float bottomLeftProportion=0.9f, float bottomRightProportion=0.7f);

    float topLeftProportion() const { return topLeftProportion_; }
    float &topLeftProportion() { return topLeftProportion_; }
    void setTopLeftProportion(float val) { topLeftProportion_ = val; }

    float topRightProportion() const { return topRightProportion_; }
    float &topRightProportion() { return topRightProportion_; }
    void setTopRightProportion(float val) { topRightProportion_ = val; }

    float bottomLeftProportion() const { return bottomLeftProportion_; }
    float &bottomLeftProportion() { return bottomLeftProportion_; }
    void setBottomLeftProportion(float val) { bottomLeftProportion_ = val; }

    float bottomRightProportion() const { return bottomRightProportion_;}
    float &bottomRightProportion() { return bottomRightProportion_; }
    void setBottomRightProportion(float val) { bottomRightProportion_ = val; }

    GNodeStyle style() const override { return GNodeStyle::BilinearGradientColor; }

    GNode *create(MTreeNodePtr mnode = nullptr) override;

    virtual ~TessBLGradientNodeFactory();

  private:
    float topLeftProportion_;
    float topRightProportion_;
    float bottomLeftProportion_;
    float bottomRightProportion_;
  };
}