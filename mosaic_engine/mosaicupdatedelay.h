#ifndef MOMOSAICUPDATEDELAY_H
#define MOMOSAICUPDATEDELAY_H

#include <mosaicupdate.h>


class MoMosaicUpdateDelay : public MoMosaicUpdate {
public:
    MoMosaicUpdateDelay(unsigned long int delay = 100);
    ~MoMosaicUpdateDelay();
    virtual void update(MoMosaicModel* model);
private:
    unsigned long int delay_;
};

#endif // MOMOSAICUPDATEDELAY_H
