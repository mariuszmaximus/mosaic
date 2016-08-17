#ifndef MOMOSAICEVOLUTION_H
#define MOMOSAICEVOLUTION_H

#include <memory>
#include <vector>


class MoMosaicModel;
class MoMosaicUpdate;
class MoTargetImage;
class MoTile;


class MoMosaicEvolution {
public:
  MoMosaicEvolution();
  ~MoMosaicEvolution();
  void constructInitialState(const MoTargetImage& targetImage,
                             const std::vector<MoTile>& tiles);
  void takeStep();
  void addUpdate(std::unique_ptr<MoMosaicUpdate>&& update);
  MoMosaicModel* getCurrentModel();
private:
  class MoMosaicEvolutionImpl;
  std::unique_ptr<MoMosaicEvolutionImpl> impl_;
};

#endif // MOMOSAICEVOLUTION_H
