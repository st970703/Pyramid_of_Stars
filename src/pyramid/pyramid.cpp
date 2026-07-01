#include "pyramid.h"

QString buildPyramid(int height, PyramidDisplayMode displayMode) {
    QString pyramid;

    for (int i = 1; i <= height; i++) {
        for (int j = 1; j <= 2*height - 1; j++) {
            bool inside_pyramid_shape = j >= height-(i-1) && j <= height+(i-1);
            if (inside_pyramid_shape) {
                if (displayMode == PyramidDisplayMode::Stars) {
                    pyramid += QString('*');
                }
                else {
                    pyramid += QString::number(i);
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
