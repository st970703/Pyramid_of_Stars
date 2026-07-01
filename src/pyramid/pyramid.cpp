//
// Created by st970 on 1/07/2026.
//

#include "pyramid.h"

QString buildPyramid(int height) {
    QString pyramid;

    for (int i = 1; i <= height; i++) {
        for (int j = 1; j <= 2*height - 1; j++) {
            if (j >= height-(i-1) && j <= height+(i-1)) {
                pyramid += QString('*');
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
