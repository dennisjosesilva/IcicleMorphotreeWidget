#pragma once 

namespace IcicleMorphotreeWidget
{
  struct Range
  {    
    Range(int pmin=0, int pmax=255);

    int min;
    int max;

    inline int numberOfElements() const { return max - min + 1; }
  };

  class GrayScaleProfile
  {
  public:
    GrayScaleProfile(const Range &irange=Range{0, 255}, 
      const Range &grange=Range{0,255});

    float computeUnitBlock(float availableSpace) const;
    int grayLevel(int l) const;

    const Range &grange() const { return grange_; }
    Range &grange() { return grange_; }
    void setGRange(const Range &val) { grange_ = val; }

    const Range &irange() const { return irange_; }
    Range &irange() { return irange_; }
    void setIRange(const Range &val) { irange_ = val; }

  private:
    float normalizeValue(int l) const;

  private:    
    Range irange_;
    Range grange_;
  };
}