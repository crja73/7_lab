#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <math.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_spinBox_count_valueChanged(int arg1);

    void on_pushButton_calculate_clicked();

    void on_tableWidget_cellChanged(int row, int column);

private:
    Ui::MainWindow *ui;
    int lol(double a);
    void samoper(int poinscount);
    bool peresech;
};

#endif // MAINWINDOW_H
