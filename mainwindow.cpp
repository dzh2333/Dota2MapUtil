#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setFixedSize(750, 700);
    ui->setupUi(this);
    setWindowTitle("DOTA2地图替换器");
}

void MainWindow::initUi(QWidget *parent){

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString fullPath = QFileDialog::getExistingDirectory();
    QString filename, filePath;
    QFileInfo fileInfo = QFileInfo(fullPath);
    filename = fileInfo.fileName();

    filePath = fileInfo.filePath();

    QPushButton* btn= qobject_cast<QPushButton*>(sender());
    QString str = btn->objectName();
    qDebug()<<"Dota2MapManager->file Path is >>" + filePath;

    if(filePath.isEmpty()){
        return;
    }

    QTextEdit* textEdit = findChild<QTextEdit*>("textEdit");
    textEdit->setText(filePath);
}



void MainWindow::on_textEdit_textChanged()
{
    QTextEdit* textEdit = findChild<QTextEdit*>("textEdit");
    qDebug()<<"path value is " + textEdit->toPlainText();
    if(!textEdit->toPlainText().isEmpty()){
        Dota2MapManager::getInstance().setMapPatch(textEdit->toPlainText());
    }
}

void MainWindow::commit(){
    //右侧
    for(int i = 100; i <= 111; i++){
        QString str = QString("radioButton_%1").arg(i);
        QRadioButton* b12 = findChild<QRadioButton*>(str);
        if(b12 == NULL){
            continue;
        }
        if(b12->isChecked()){
           Dota2MapManager::getInstance().setReplaceMap(i);
           break;
        }else if(i == 111){
            QMessageBox::critical(this, "错误信息", "没有选择要替换的地图");
            return;
        }
    }

    //左侧
    for(int i = 200; i <= 211; i++){
        QString str = QString("radioButton_%1").arg(i);

        QRadioButton* b12 = findChild<QRadioButton*>(str);
        if(b12 == NULL){
            continue;
        }
        if(b12->isChecked()){
            Dota2MapManager::getInstance().setCurrMap(i);
            break;
        }else if(i == 211){
            QMessageBox::critical(this, "错误信息", "没有选择当前使用的地图");
            return;
        }
    }

    //开始替换
    QString oldFileName = Dota2MapManager::getInstance().getMapNam(Dota2MapManager::getInstance().currIndex%200 - 1);
    QString newFileName = Dota2MapManager::getInstance().getMapNam(Dota2MapManager::getInstance().repaceIndex%100 - 1);
    //目标地图
    QString oldFilePath = Dota2MapManager::getInstance().mapPath + "/" + oldFileName;
    QFile oldFile = QFile(oldFilePath);
    if(oldFile.exists()){
        oldFile.remove();
    }
    //保存过的地图
    QString savePath = QCoreApplication::applicationDirPath()+ "/maps/" + newFileName;
    bool copy = QFile::copy(savePath, oldFilePath);
    qDebug()<<"copy file " + savePath + "  to " + oldFilePath;

    if(copy){
        QMessageBox::about(this, "替换成功", "替换成功！开始游玩吧！");
    }else {
        QMessageBox::critical(this, "替换失败", "请确认路径和工具权限");
    }

}

void MainWindow::on_pushButton_2_clicked()
{
    commit();
}


void MainWindow::on_pushButton_3_clicked()
{
    int code = Dota2MapManager::getInstance().saveOldFile();
    if(code == 1){
           QMessageBox::about(this, "备份成功", "备份成功，可以开始替换了");
    }else if(code == 2){
        QMessageBox::critical(this, "备份", "你已经备份过了");
    }else {
         QMessageBox::critical(this, "备份失败", "请确认路径和工具权限");
    }
}


void MainWindow::on_pushButton_4_clicked()
{
    bool reset =  Dota2MapManager::getInstance().backToBackFileStatus();
    if(reset){
        QMessageBox::about(this, "还原成功", "还原成功");
    }else {
        QMessageBox::critical(this, "还原失败", "还原失败");
    }
}

