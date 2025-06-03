#ifndef BASEMAINWINDOW_H
#define BASEMAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QMessageBox>

class BaseMainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit BaseMainWindow(QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    void showUserGuide();
};

#endif // BASEMAINWINDOW_H
