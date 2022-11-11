#include "mainwindow.h"
#include "painterpath.h"
//#include "./ui_mainwindow.h"
#include <QTableWidgetItem>
#include <QMessageBox>
//#include "time.h"
#include <QPainter>




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
//    , ui(new Ui::MainWindow)
{
//    setAttribute(Qt::WA_NoSystemBackground);
//    setAttribute(Qt::WA_TransparentForMouseEvents);
//    ui->setupUi(this);
}

//MainWindow::~MainWindow()
//{
//    delete ui;
//}

void MainWindow::setPushButton( QPushButton * new_pushButton) {
    pushButton = new_pushButton;
}

void MainWindow::setTableWidget( QTableWidget * new_tableWidget) {
    tableWidget = new_tableWidget;
}

void MainWindow::setWidth( QLineEdit * new_width){
    width = new_width;
}
void MainWindow::setHeight( QLineEdit * new_height){
    height = new_height;
}

void MainWindow::resizeTable(int rowCount, int columnCount) {
    isSetA = false; isSetB = false;
    rowCount = std::min(rowCount, 40);
    columnCount = std::min(columnCount, 60);
    item_size = std::min(field_height / rowCount, field_width / columnCount);
    this->tableWidget->setRowCount(rowCount);
    this->tableWidget->setColumnCount(columnCount);
    for(int i = 0 ; i < rowCount; i++) {
        this->tableWidget->setRowHeight(i, item_size);
    }
    for(int i = 0 ; i < columnCount; i++) {
        this->tableWidget->setColumnWidth(i, item_size);
    }

    srand(time(NULL));
//    table.resize(row);
    table = std::vector<std::vector<int>>(rowCount);
    for(int i = 0 ; i < rowCount; i++) {
        for(int j = 0 ; j < columnCount; j++) {
            QTableWidgetItem *item = new QTableWidgetItem("");
            this->tableWidget->setItem(i, j, item);
            if(((rand() % 100)) < 16) {
                item->setBackground(Qt::black);
                table[i].push_back(-1);
            }
            else {
                item->setBackground(Qt::white);
                table[i].push_back(-2);
            }
        }
    }
    this->update();
}

void MainWindow::on_pushButton_clicked() {
    bool wOk;
    bool hOk;
    int row = this->height->text().toInt(&hOk);
    int column = this->width->text().toInt(&wOk);
    if(wOk && hOk){
        resizeTable(row, column);
    } else {
        QMessageBox::information(this, "Error", "Ширина и высота должны быть целыми числами");
    }
}

void MainWindow::setPoint(int row, int column, QString p){
    int font_size = item_size / 4;
    QFont font;
    font.setPointSize(font_size);
    this->tableWidget->setFont(font);

    QTableWidgetItem *item = new QTableWidgetItem(p);
    this->tableWidget->setItem(row, column, item);
    item->setBackground(Qt::red);
    item->setTextAlignment(Qt::AlignCenter);
}

void MainWindow::removePoint(int row, int column){
    QTableWidgetItem *item = this->tableWidget->item(row, column);
    item->setText("");
    item->setBackground(Qt::white);
}


void MainWindow::on_tableWidget_cellClicked(int row, int column) {
//    int pos = this->tableWidget->rowViewportPosition(row);
//    QMessageBox::information(this, "Value", QString::number(pos));

    if(this->tableWidget->item(row, column)->background() == Qt::black){return;}
    if(!isSetA) {
        if(isSetB && row_B == row && column_B == column) {removePoint(row, column); isSetB = false;}
        else {
            setPoint(row, column, "A");
            isSetA = true;
            row_A =  row;
            column_A = column;
            if(isSetB) {
                PainterPath::isStartPaintingPath = true;
                this->centralWidget()->repaint();
            }
        }
    }
    else {
        if(row_A == row && column_A == column) {removePoint(row, column); isSetA = false;}
        else if(isSetB && row_B == row && column_B == column) {removePoint(row, column); isSetB = false;}
        else {
            if(isSetB) removePoint(row_B, column_B);
            setPoint(row, column, "B");
            isSetB = true;
            row_B = row;
            column_B = column;

            PainterPath::isStartPaintingPath = true;
            this->centralWidget()->update();
        }
    }

}


//void MainWindow::on_checkBox_stateChanged(int checkState)
//{
//    if(checkState == 0){
//        QMessageBox::information(this, "Check", "Не нажата");
//    } else if(checkState == 2) {
//        QMessageBox::information(this, "Check", "Нажата");
//    }
//}

