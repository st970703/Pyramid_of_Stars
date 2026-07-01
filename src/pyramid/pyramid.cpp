#include "pyramid.h"

QString buildPyramid(int height, PyramidDisplayMode displayMode) {
    QString pyramid;

    for (int i = 1; i <= height; i++) {
        for (int j = 1; j <= 2*height - 1; j++) {
            bool inside_pyramid_shape = j >= height-(i-1) && j <= height+(i-1);
            if (inside_pyramid_shape) {
                switch (displayMode) {
                    case PyramidDisplayMode::Stars:
                        pyramid += QString('*');
                        break;
                    case PyramidDisplayMode::Numbers:
                        pyramid += QString::number(i);
                        break;
                    default:
                        throw std::invalid_argument("Invalid display mode selected!");
                }
            }
            else {
                pyramid += QString(' ');
            }
        }
        if (i != height) {
            pyramid += '\n';
        }
    }
    return pyramid;
}
