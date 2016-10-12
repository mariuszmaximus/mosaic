#include <interactiontileborder.h>
#include <potential.h>
#include <mosaicmodel.h>
#include <quadraturerule.h>

#include <QtGlobal>
#include <vector>
#include <cmath>


static void transformToWorldCoordinates(float x, float y, float w, float h,
                                        float alpha, float scale,
                                        float* r);
static float computeBadnessPair(float x0, float y0, float w0, float h0,
                         float alpha0, float scale0,
                         float x1, float y1, float w1, float h1,
                         float alpha1, float scale1,
                         MoPotential* potential);

MoInteractionTileBorder::MoInteractionTileBorder(
        std::unique_ptr<MoPotential> potential) :
    potential_(std::move(potential)) {
}

float MoInteractionTileBorder::computeBadness(
        const MoMosaicModel &model, const MoTargetImage &targetImage) {
    int numTilesLinear = static_cast<int>(
                std::round(std::sqrt(static_cast<float>(model.size()))));

    const float* x = model.getXCoords();
    const float* y = model.getYCoords();
    std::vector<float> w(model.size());
    model.getWidths(&w[0]);
    std::vector<float> h(model.size());
    model.getHeights(&h[0]);
    const float* alpha = model.getRotations();
    const float* scale = model.getScales();

    float badness = 0.0;
    // bottom row of fake tiles
    QSize targetSize = targetImage.getImage().size();
    // TODO: Check the units on this
    float width0 = static_cast<float>(targetSize.width()) / numTilesLinear;
    float height0 = static_cast<float>(targetSize.height()) / numTilesLinear;
    // TODO check the origin
    for (int i = 0; i != numTilesLinear; ++i) {
        int j = 0;
        float x0 = i * width0 +0.5 * width0;
        float y0 = j * height0 -0.5 * height0;
        for (int ii = 0; ii < model.size(); ++ii) {
            badness +=
                    computeBadnessPair(x0, y0, width0, height0, 0.0f, 1.0f,
                                       x[ii], y[ii], w[ii], h[ii], alpha[ii], scale[ii],
                                       potential_.get());
        }
    }
    return badness;
}

void MoInteractionTileBorder::resetPotential(
        std::unique_ptr<MoPotential> potential) {
    potential_ = std::move(potential);
}

float computeBadnessPair(float x0, float y0, float w0, float h0,
                         float alpha0, float scale0,
                         float x1, float y1, float w1, float h1,
                         float alpha1, float scale1,
                         MoPotential* potential) {

    float range = potential->range();
    if (range > 0) {
        // Check if distance between tiles is larger than range.
        // To compute the distance between tiles we construct a
        // bounding circle around each tile and we compute the
        // distance between these circles.
        float distanceBetweenTileCenters = std::sqrt(
                    (x0 - x1) * (x0 - x1) +
                    (y0 - y1) * (y0 - y1));
        float radius1 = std::sqrt(w0 * w0 + h0 * h0);
        float radius2 = std::sqrt(w1 * w1 + h1 * h1);
        float distanceBetweenTiles =
                distanceBetweenTileCenters - radius1 - radius2;
        if (distanceBetweenTiles > range) {
            return 0.0f;
        }
    }

    // asm("# computeBadnessPair");
    static const int order = 4;
    static const float* weights = &MoQuadratureRule[order - 1][MO_QUADRATURE_WEIGHTS][0];
    static const float* nodes = &MoQuadratureRule[order - 1][MO_QUADRATURE_NODES][0];


    // asm("# compute nodes for i tile");
    float r1[order][order][2];
    for (int ix = 0; ix < order; ++ix) {
        for (int iy = 0; iy < order; ++iy) {
            r1[ix][iy][0] = nodes[ix];
            r1[ix][iy][1] = nodes[iy];
            transformToWorldCoordinates(x0, y0, w0, h0, alpha0, scale0,
                                        r1[ix][iy]);
        }
    }

    // asm("# compute nodes for j tile");
    float r2[order][order][2];
    for (int ix = 0; ix < order; ++ix) {
        for (int iy = 0; iy < order; ++iy) {
            r2[ix][iy][0] = nodes[ix];
            r2[ix][iy][1] = nodes[iy];
            transformToWorldCoordinates(x1, y1, w1, h1, alpha1, scale1,
                                        r2[ix][iy]);
        }
    }

    // Now compute badness by integrating over both tiles
    // asm("# quadrature loop");
    float badness = 0.0f;
    for (int ix = 0; ix < order; ++ix) {
        float b = 0.0f;
        for (int iy = 0; iy < order; ++iy) {
            float bp = 0.0f;
            for (int jx = 0; jx < order; ++jx) {
                float bpp = 0.0f;
                for (int jy = 0; jy < order; ++jy) {
                    bpp += weights[jy] *
                            potential->operator()(r1[ix][iy], r2[ix][iy]);
                }
                bp += weights[jx] * bpp;
            }
            b += weights[iy] * bp;
        }
        badness += weights[ix] * b;
    }
    // Gauss quadrature weights are normalized for integration over [-1, 1].
    // We divide by 2^4 to make the integrals normalized over the tiles.
    return badness / 16.0f;
}

void transformToWorldCoordinates(float x, float y, float w, float h,
                                        float alpha, float scale,
                                        float* r) {
    float rtemp[2];
    float c = cos(alpha);
    float s = sin(alpha);

    r[0] *= w;
    r[1] *= h;

    rtemp[0] = scale * (c * r[0] - s * r[1]) + x;
    rtemp[1] = scale * (s * r[0] + c * r[1]) + y;

    for (int i = 0; i < 2; ++i) {
        r[i] = rtemp[i];
    }
}
