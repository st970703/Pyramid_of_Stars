#include "pyramidwindow.h"

#include <QFont>
#include <QHBoxLayout>
#include <QLabel>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QWidget>

#include "pyramid.h"

QWidget *createPyramidWindow() {
    auto *window = new QWidget;
    window->setWindowTitle("Pyramid of Stars");
    window->resize(420, 360);

    auto *titleLabel = new QLabel("Pyramid of Stars");
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(18);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);

    auto *heightLabel = new QLabel("Height");

    auto *heightSpinBox = new QSpinBox;
    heightSpinBox->setRange(1, 20);
    heightSpinBox->setValue(7);

    auto *generateButton = new QPushButton("Generate");

    auto *controlsLayout = new QHBoxLayout;
    controlsLayout->addWidget(heightLabel);
    controlsLayout->addWidget(heightSpinBox);
    controlsLayout->addStretch();
    controlsLayout->addWidget(generateButton);

    auto *output = new QPlainTextEdit;
    output->setReadOnly(true);
    output->setLineWrapMode(QPlainTextEdit::NoWrap);
    output->setPlainText(buildPyramid(heightSpinBox->value()));

    QFont outputFont("Consolas");
    outputFont.setStyleHint(QFont::Monospace);
    outputFont.setPointSize(12);
    output->setFont(outputFont);

    auto *mainLayout = new QVBoxLayout(window);
    mainLayout->addWidget(titleLabel);
    mainLayout->addLayout(controlsLayout);
    mainLayout->addWidget(output);

    QObject::connect(generateButton, &QPushButton::clicked, window, [heightSpinBox, output]() {
        output->setPlainText(buildPyramid(heightSpinBox->value()));
    });

    QObject::connect(heightSpinBox, &QSpinBox::valueChanged, window, [heightSpinBox, output](int) {
        output->setPlainText(buildPyramid(heightSpinBox->value()));
    });

    return window;
}
