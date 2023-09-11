#ifndef SPEEDOMETERUI_HPP
#define SPEEDOMETERUI_HPP

#include <QMainWindow>
#include <memory>

class QDial;

class SpeedometerUI : public QMainWindow {
    Q_OBJECT

public:
    SpeedometerUI(std::shared_ptr<QWidget> parent = nullptr);

public slots:
    void setSpeed(double speed);

private:
    QDial* m_dialPtr;
};

#endif // SPEEDOMETERUI_HPP
