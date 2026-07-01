#include <QPlainTextEdit>
#include <QPushButton>
#include <QTest>
#include <QWidget>

#include <memory>

#include "pyramid/pyramid.h"
#include "ui/pyramidwindow.h"

class PyramidWindowTest : public QObject {
    Q_OBJECT

private slots:
    void directionButtonTogglesUpsideDownPyramid();
};

void PyramidWindowTest::directionButtonTogglesUpsideDownPyramid() {
    std::unique_ptr<QWidget> window(createPyramidWindow());
    window->show();

    auto *output = window->findChild<QPlainTextEdit *>();
    QVERIFY(output != nullptr);

    QPushButton *directionButton = nullptr;
    const auto buttons = window->findChildren<QPushButton *>();
    for (auto *button : buttons) {
        if (button->text() == "Direction: Normal") {
            directionButton = button;
            break;
        }
    }

    QVERIFY(directionButton != nullptr);
    QCOMPARE(output->toPlainText(), buildPyramid(7, PyramidDisplayMode::Stars, false));

    QTest::mouseClick(directionButton, Qt::LeftButton);

    QCOMPARE(directionButton->text(), QString("Direction: Upside Down"));
    QCOMPARE(output->toPlainText(), buildPyramid(7, PyramidDisplayMode::Stars, true));
}

QTEST_MAIN(PyramidWindowTest)
#include "pyramidwindow_test.moc"
