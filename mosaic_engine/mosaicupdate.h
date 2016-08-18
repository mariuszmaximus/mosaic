#ifndef MOMOSAICUPDATE_H
#define MOMOSAICUPDATE_H

class MoMosaicModel;

class MoMosaicUpdate {
public:
    virtual ~MoMosaicUpdate();
    virtual void update(MoMosaicModel* model) = 0;
};

#endif // MOMOSAICUPDATE_H
