#include "IcicleMorphotreeWidget/Graphics/GrayScaleBar/GrayScaleProfile.hpp"

namespace IcicleMorphotreeWidget
{
  Range::Range(int pmin, int pmax)
    : min{pmin}, max{pmax}
  {}

  GrayScaleProfile::GrayScaleProfile(const Range &irange, const Range &grange)
    : irange_{irange}, grange_{grange}
  {}

  float GrayScaleProfile::computeUnitBlock(float availableSpace) const
  {
    return availableSpace / static_cast<float>(irange_.max - irange_.min + 1);
  }

  float GrayScaleProfile::normalizeValue(int l) const
  {
    float ng = static_cast<float>(grange_.max - grange_.min);
    return static_cast<float>(l - grange_.min) / ng;
  }

  int GrayScaleProfile::grayLevel(int l) const
  {
    return normalizeValue(l) * 255;
  }
}