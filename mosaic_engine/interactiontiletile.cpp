#include <interactiontiletile.h>
#include <mosaicmodel.h>
#include <quadraturerule.h>

#include <QtGlobal>


// A few helper functions
static void transformToWorldCoordinates(float x, float y, float w, float h,
                                        float alpha, float scale,
                                        float* r);
static float computeBadnessPair(const float* x, const float* y,
                                const float* w, const float* h,
                                const float* alpha, const float* scale,
                                int i, int j,
                                MoPotential* potential);


MoInteractionTileTile::MoInteractionTileTile(
        std::unique_ptr<MoPotential> potential) : potential_(std::move(potential)) {
}

float MoInteractionTileTile::computeBadness(
        const MoMosaicModel &model, const MoTargetImage &targetImage) {
    Q_UNUSED(targetImage);
    const float* x = model.getXCoords();
    const float* y = model.getYCoords();
    std::vector<float> w(model.size());
    model.getWidths(&w[0]);
    std::vector<float> h(model.size());
    model.getHeights(&h[0]);
    const float* alpha = model.getRotations();
    const float* scale = model.getScales();

    float badness = 0.0f;
    for (int i = 0; i < model.size(); ++i) {
        for (int j = 0; j < i; ++j) {
            badness += computeBadnessPair(x, y, &w[0], &h[0], alpha, scale, i, j,
                    potential_.get());
        }
    }
    return badness;
}

static float computeBadnessPair(const float* x, const float* y,
                                const float* w, const float* h,
                                const float* alpha, const float* scale,
                                int i, int j,
                                MoPotential* potential) {
    float range = potential->range();
    if (range > 0) {
        float dist = std::sqrt(
                    (x[i] - x[j]) * (x[i] - x[j]) +
                    (y[i] - y[j]) * (y[i] - y[j]));
        if (dist > range) {
            return 0.0f;
        }
    }

    // asm("# computeBadnessPair");
    static const int order = 4;
    static const float* weights = &MoQuadratureRule[order - 1][MO_QUADRATURE_WEIGHTS][0];
    static const float* nodes = &MoQuadratureRule[order - 1][MO_QUADRATURE_NODES][0];


    // asm("# compute nodes for i tile");
    float x1[order][order][2];
    for (int ix = 0; ix < order; ++ix) {
        for (int iy = 0; iy < order; ++iy) {
            x1[ix][iy][0] = nodes[ix];
            x1[ix][iy][1] = nodes[iy];
            transformToWorldCoordinates(x[i], y[i], w[i], h[i], alpha[i], scale[i],
                                        x1[ix][iy]);
        }
    }

    // asm("# compute nodes for j tile");
    float x2[order][order][2];
    for (int ix = 0; ix < order; ++ix) {
        for (int iy = 0; iy < order; ++iy) {
            x2[ix][iy][0] = nodes[ix];
            x2[ix][iy][1] = nodes[iy];
            transformToWorldCoordinates(x[j], y[j], w[j], h[j], alpha[j], scale[j],
                                        x2[ix][iy]);
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
                            potential->operator()(x1[ix][iy], x2[ix][iy]);
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
