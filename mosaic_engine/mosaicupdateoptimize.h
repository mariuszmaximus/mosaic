#ifndef MOSAICUPDATEOPTIMIZE_H
#define MOSAICUPDATEOPTIMIZE_H

#include <mosaicupdate.h>
#include <memory>


class MoBadness;


class MoMosaicUpdateOptimize : public MoMosaicUpdate {
public:
    virtual ~MoMosaicUpdateOptimize() {}
    virtual void update(MoMosaicModel *model);
    virtual void setBadness(std::unique_ptr<MoBadness> badness);
private:
    std::unique_ptr<MoBadness> badness_;
};

#endif // MOSAICUPDATEOPTIMIZE_H
