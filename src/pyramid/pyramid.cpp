#include "pyramid.h"

#include <stdexcept>

/**
 * Compute the display number with padding for the number display mode.
 *
 * @param row
 * @param position
 * @return
 */
int getDisplayNumber(int row, int position) {
    return position <= row ? position : 2*row - position;
}

QString buildPyramid(int height, PyramidDisplayMode displayMode, bool upsideDown) {
    QString pyramid;
    int numberCellWidth = QString::number(height).length() + 1;

    if (upsideDown) {
        for (int row = height; row >= 1; row--) {
            int spaces = height - row;
            int cells = row * 2 - 1;

            switch (displayMode) {
                case PyramidDisplayMode::Stars:
                    pyramid += QString(spaces, ' ');
                    pyramid += QString(cells, '*');
                    break;
                case PyramidDisplayMode::Numbers:
                    pyramid += QString(spaces * numberCellWidth, ' ');
                    for (int position = 1; position <= cells; position++) {
                        pyramid += QString("%1").arg(
                            getDisplayNumber(row, position), numberCellWidth
                        );
                    }
                    break;
                default:
                    throw std::invalid_argument("Invalid display mode selected!");
            }

            if (row != 1) {
                pyramid += '\n';
            }
        }
    }
    else {
        for (int row = 1; row <= height; row++) {
            int spaces = height - row;
            int cells = row * 2 - 1;

            switch (displayMode) {
                case PyramidDisplayMode::Stars:
                    pyramid += QString(spaces, ' ');
                    pyramid += QString(cells, '*');
                    break;
                case PyramidDisplayMode::Numbers:
                    pyramid += QString(spaces * numberCellWidth, ' ');
                    for (int position = 1; position <= cells; position++) {
                        pyramid += QString("%1").arg(
                            getDisplayNumber(row, position), numberCellWidth
                        );
                    }
                    break;
                default:
                    throw std::invalid_argument("Invalid display mode selected!");
            }

            if (row != height) {
                pyramid += '\n';
            }
        }
    }

    return pyramid;
}
