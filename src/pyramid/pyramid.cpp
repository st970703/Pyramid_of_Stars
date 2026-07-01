#include "pyramid.h"

/**
 * Compute the display number with padding for the number display mode.
 *
 * @param row
 * @param col
 * @param height
 * @return
 */
int getDisplayNumber(int row, int col, int height) {
    int position = col - (height - (row - 1)) + 1;
    return position <= row ? position : 2*row - position;
}

QString buildPyramid(int height, PyramidDisplayMode displayMode) {
    QString pyramid;
    int numberCellWidth = QString::number(height).length() + 1;

    for (int i = 1; i <= height; i++) {
        for (int j = 1; j <= 2*height - 1; j++) {
            bool is_inside_pyramid_shape = j >= height-(i-1) && j <= height+(i-1);
            if (is_inside_pyramid_shape) {
                switch (displayMode) {
                    case PyramidDisplayMode::Stars:
                        pyramid += QString('*');
                        break;
                    case PyramidDisplayMode::Numbers:
                        {
                            pyramid += QString("%1").arg(
                                getDisplayNumber(i, j, height), numberCellWidth
                            );
                        }
                        break;
                    default:
                        throw std::invalid_argument("Invalid display mode selected!");
                }
            }
            else {
                switch (displayMode) {
                    case PyramidDisplayMode::Stars:
                        pyramid += QString(' ');
                        break;
                    case PyramidDisplayMode::Numbers:
                        pyramid += QString(numberCellWidth, ' ');
                        break;
                    default:
                        throw std::invalid_argument("Invalid display mode selected!");
                }
            }
        }
        if (i != height) {
            pyramid += '\n';
        }
    }
    return pyramid;
}
