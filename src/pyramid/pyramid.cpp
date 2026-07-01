#include "pyramid.h"

QString buildPyramid(int height, PyramidDisplayMode displayMode) {
    QString pyramid;

    for (int i = 1; i <= height; i++) {
        for (int j = 1; j <= 2*height - 1; j++) {
            if (j >= height-(i-1) && j <= height+(i-1)) {
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
