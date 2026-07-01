#include "pyramidwindow.h"

#include <QFont>
#include <QHBoxLayout>
#include <QLabel>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QWidget>

#include <memory>

#include "pyramid/pyramid.h"

namespace {
constexpr const char* kPyramidWindowTitle = "Pyramid of Stars";
constexpr const char* kStarsModeButtonText = "Display mode: Stars";
constexpr const char* kNumbersModeButtonText = "Display mode: Numbers";
constexpr const char* kNormalDirectionButtonText = "Direction: Normal";
constexpr const char* kUpsideDownButtonText = "Direction: Upside Down";
}

QWidget *createPyramidWindow() {
    auto *window = new QWidget;
    window->setWindowTitle(kPyramidWindowTitle);
    window->resize(420, 360);

    auto *titleLabel = new QLabel(kPyramidWindowTitle);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(18);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);

    auto *heightLabel = new QLabel("Height");

    auto *heightSpinBox = new QSpinBox;
    heightSpinBox->setRange(1, 20);
    heightSpinBox->setValue(7);

    auto *generateButton = new QPushButton("Generate");
    auto *displayModeButton = new QPushButton(kStarsModeButtonText);
    auto *upsideDownButton = new QPushButton(kNormalDirectionButtonText);
    auto displayMode = std::make_shared<PyramidDisplayMode>(PyramidDisplayMode::Stars);
    auto upsideDown = std::make_shared<bool>(false);

    auto *controlsLayout = new QHBoxLayout;
    controlsLayout->addWidget(heightLabel);
    controlsLayout->addWidget(heightSpinBox);
    controlsLayout->addStretch();
    controlsLayout->addWidget(displayModeButton);
    controlsLayout->addWidget(upsideDownButton);
    controlsLayout->addWidget(generateButton);

    auto *output = new QPlainTextEdit;
    output->setReadOnly(true);
    output->setLineWrapMode(QPlainTextEdit::NoWrap);
    output->setPlainText(buildPyramid(heightSpinBox->value(), *displayMode, *upsideDown));

    QFont outputFont("Consolas");
    outputFont.setStyleHint(QFont::Monospace);
    outputFont.setPointSize(12);
    output->setFont(outputFont);

    auto *mainLayout = new QVBoxLayout(window);
    mainLayout->addWidget(titleLabel);
    mainLayout->addLayout(controlsLayout);
    mainLayout->addWidget(output);

    auto updateOutput = [heightSpinBox, output, displayMode, upsideDown]() {
        output->setPlainText(buildPyramid(heightSpinBox->value(), *displayMode, *upsideDown));
    };

    QObject::connect(generateButton, &QPushButton::clicked, window, updateOutput);

    QObject::connect(displayModeButton, &QPushButton::clicked, window, [displayModeButton, updateOutput, displayMode]() {
        if (*displayMode == PyramidDisplayMode::Stars) {
            *displayMode = PyramidDisplayMode::Numbers;
            displayModeButton->setText(kNumbersModeButtonText);
        }
        else {
            *displayMode = PyramidDisplayMode::Stars;
            displayModeButton->setText(kStarsModeButtonText);
        }
        updateOutput();
    });

    QObject::connect(upsideDownButton, &QPushButton::clicked, window, [upsideDownButton, updateOutput, upsideDown]() {
        *upsideDown = !*upsideDown;
        upsideDownButton->setText(*upsideDown ? kUpsideDownButtonText : kNormalDirectionButtonText);
        updateOutput();
    });

    QObject::connect(heightSpinBox, &QSpinBox::valueChanged, window, [updateOutput](int) {
        updateOutput();
    });

    return window;
}
