#include "SpeedometerUI.hpp"
#include <QDial>

SpeedometerUI::SpeedometerUI(std::shared_ptr<QWidget> parent) : QMainWindow(parent.get()) {
    m_dialPtr = new QDial(this);
    m_dialPtr->setGeometry(50, 50, 300, 300);
    m_dialPtr->setMinimum(-7);
    m_dialPtr->setMaximum(7);
    m_dialPtr->setSingleStep(1);

    setCentralWidget(m_dialPtr);
}

void SpeedometerUI::setSpeed(double speed) {
    m_dialPtr->setValue(static_cast<int>(speed));
}
