#include "painterpath.h"
#include "mainwindow.h"
#include <queue>
#include <QMessageBox>
#include<QDebug>
#include <mutex>

PainterPath::PainterPath(QWidget * parent) :
    QWidget( parent) {
    setAttribute(Qt::WA_NoSystemBackground);
    setAttribute(Qt::WA_TransparentForMouseEvents);
}

void PainterPath::paintEvent(QPaintEvent * e) {
    qInfo() << "paintEvent";
//    std::mutex m;
    if(isStartPaintingPath) {
//        std::lock_guard<std::mutex> g(m);
        isStartPaintingPath = false;
        table = MainWindow::table;
        findPath();
        if( table[MainWindow::row_B][MainWindow::column_B] == 0) {
            QMessageBox::information(this, "Failure", "Пути нет");
             return;
        }

        QPainter painter(this);
        painter.setPen(QPen(Qt::darkGreen, 3, Qt::SolidLine,  Qt::RoundCap));
        int rowCount = table.size();
        int columnCount = table[0].size();
        qDebug() << "______________________________________________";
        for(int i = 0 ; i < rowCount; i++) {
            QString s = "";
            for(int j = 0; j < columnCount; j++){
                s =  s + QString::number(table[i][j]) + " ";
            }
            qDebug() << s + "\n";
        }
        qDebug() << "______________________________________________";
        std::vector<int> rowShift   {0, -1, 0, 1};
        std::vector<int> columnShift{-1, 0, 1, 0};
        int prevRow = MainWindow::row_B, prevColumn = MainWindow::column_B;
        while(prevRow != MainWindow::row_A || prevColumn != MainWindow::column_A) {
            for(int i = 0; i < 4; i++) {
                int row = prevRow + rowShift[i];
                int column = prevColumn + columnShift[i];
                QString s;
                s =  QString::number(row) + " " + QString::number(column) + " <- "
                                              + QString::number(prevRow) + " " + QString::number(prevColumn);
                qDebug() << s + "\n";
                if(0 <= row && row < rowCount
                   && 0 <= column && column < columnCount
                    && (table[row][column] + 1) == table[prevRow][prevColumn]
                        && table[row][column] != -2)
                {

                    int x1 = column * MainWindow::item_size + MainWindow::item_size / 2;
                    int y1 = row * MainWindow::item_size + MainWindow::item_size / 2;
                    int x2 = prevColumn * MainWindow::item_size + MainWindow::item_size / 2;
                    int y2 = prevRow * MainWindow::item_size + MainWindow::item_size / 2;
                    painter.drawLine(x1, y1, x2, y2);
                    prevRow = row; prevColumn = column;
                    break;
                 }
            }
         }
    }
}


void PainterPath::findPath() {
    int rowCount = table.size();
    int columnCount = table[0].size();
    std::vector<int> rowShift   {0, -1, 0, 1};
    std::vector<int> columnShift{-1, 0, 1, 0};
    std::queue<Point> q;
    q.push({MainWindow::row_A, MainWindow::column_A});
    table[MainWindow::row_A][MainWindow::column_A] = 0;
    while(!q.empty()) {
        Point p = q.front();
        if(p.row == MainWindow::row_B && p.column == MainWindow::column_B) return;

        for(int i = 0; i < 4; i++) {
            int row = p.row + rowShift[i];
            int column = p.column + columnShift[i];

            if(0 <= row && row < rowCount
               && 0 <= column && column < columnCount
               && table[row][column] == -2)
            {
                table[row][column] = table[p.row][p.column] + 1;
                q.push({row, column});

            }

        }
        q.pop();
    }
}
