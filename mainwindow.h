#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void action();
    void loadText();
    
private:
    Ui::MainWindow *ui;
    QProcess  * mProcess;
};

#endif // MAINWINDOW_H
