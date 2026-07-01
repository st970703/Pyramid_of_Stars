//
// Created by st970 on 1/07/2026.
//

#ifndef PRINT_PYRAMID_PYRAMID_H
#define PRINT_PYRAMID_PYRAMID_H

#include <QString>

enum class PyramidDisplayMode {
    Stars,
    Numbers
};

QString buildPyramid(
    int height,
    PyramidDisplayMode displayMode = PyramidDisplayMode::Stars,
    bool upsideDown = false
);

#endif //PRINT_PYRAMID_PYRAMID_H
