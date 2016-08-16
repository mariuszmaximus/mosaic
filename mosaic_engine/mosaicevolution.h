#ifndef MOMOSAICEVOLUTION_H
#define MOMOSAICEVOLUTION_H

#include <memory>

class MoMosaicModel;
class MoMosaicUpdate;


class MoMosaicEvolution {
public:
  MoMosaicEvolution();
  ~MoMosaicEvolution();
  void constructInitialState();
  void takeStep();
  void addUpdate(MoMosaicUpdate&& update);
  MoMosaicModel* getCurrentModel();
private:
  class MoMosaicEvolutionImpl;
  std::unique_ptr<MoMosaicEvolutionImpl> impl_;
};

#endif // MOMOSAICEVOLUTION_H
