#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QApplication>
#include <QDialog>
#include <QLabel>
#include <QString>
#include <QFileDialog>
#include <QDialogButtonBox>
#include <QDesktopServices>
#include "dota2mapmanager.h"
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_textEdit_textChanged();

    void commit();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    void initUi(QWidget *parent);
};
#endif // MAINWINDOW_H
