#include "mainwindow.h"
#include "painterpath.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QHeaderView>
#include <QLineEdit>
#include <QCheckBox>
#include <QGraphicsScene>

bool PainterPath::isStartPaintingPath = false;
int MainWindow::row_A = 0;
int MainWindow::column_A = 0 ;
int MainWindow::row_B = 0;
int MainWindow::column_B = 0;

int MainWindow::item_size = 80;
std::vector<std::vector<int>> MainWindow::table(10);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "PathFinder_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    MainWindow w;
    w.setObjectName("MainWindow");
    w.setGeometry(QRect(0, 0, 1400, 950));
    QGraphicsScene scene(&w);

//    w.setAutoFillBackground(true);

    QWidget mainWidget(&w);
    mainWidget.setGeometry(QRect(0, 0, 1400, 950));
    mainWidget.setObjectName("mainWidget");

    QTableWidget tableWidget(&mainWidget);

    tableWidget.setObjectName("tableWidget");
    tableWidget.setGeometry(QRect(0, 0, 1250, 850));

    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(tableWidget.sizePolicy().hasHeightForWidth());
    tableWidget.setSizePolicy(sizePolicy);
    tableWidget.setMaximumSize(QSize(1250, 1200));

    tableWidget.horizontalHeader()->setVisible(false);
    tableWidget.horizontalHeader()->setMinimumSectionSize(20);
    tableWidget.horizontalHeader()->setDefaultSectionSize(20);
    tableWidget.verticalHeader()->setVisible(false);
    tableWidget.verticalHeader()->setMinimumSectionSize(20);
    tableWidget.verticalHeader()->setDefaultSectionSize(20);
    tableWidget.setEditTriggers(QAbstractItemView::NoEditTriggers);

    tableWidget.setRowCount(10);
    tableWidget.setColumnCount(10);
    for(int i = 0 ; i < 10; i++) {
        tableWidget.setColumnWidth(i, 80);
        tableWidget.setRowHeight(i, 80);
    }
    QFont font;
    font.setPointSize(12);
    tableWidget.setFont(font);

    srand(time(NULL));
    for(int i = 0 ; i < 10; i++) {
        for(int j = 0 ; j < 10; j++) {
            QTableWidgetItem *item = new QTableWidgetItem("");
            tableWidget.setItem(i, j, item);
            if(((rand() % 100)) < 16) {
                item->setBackground(Qt::black);
                w.table[i].push_back(-1);
            }
            else {
                item->setBackground(Qt::white);
                w.table[i].push_back(-2);
            }
        }
    }
    w.setTableWidget(&tableWidget);

    QPushButton pushButton(&mainWidget);
    pushButton.setObjectName("pushButton");
    pushButton.setGeometry(QRect(1250, 0, 100, 40));
    w.setPushButton(&pushButton);

    QLabel label1(&mainWidget);
    label1.setObjectName("label");
    label1.setGeometry(QRect(270, 850, 61, 61));
    QFont font1;
    font1.setPointSize(36);
    font1.setBold(true);
    label1.setFont(font1);

    QLabel label2(&mainWidget);
    label2.setObjectName("label2");
    label2.setGeometry(QRect(760, 850, 61, 61));
    label2.setFont(font1);

    QFont font2;
    font2.setPointSize(28);
    font2.setBold(true);
    QLineEdit width(&mainWidget);
    width.setObjectName("width");
    width.setGeometry(QRect(330, 860, 51, 41));
    width.setFont(font2);
    w.setWidth(&width);
    QLineEdit height(&mainWidget);
    height.setObjectName("height");
    height.setGeometry(QRect(810, 860, 51, 41));
    height.setFont(font2);
    w.setHeight(&height);

//    QCheckBox checkBox(&mainWidget);
//    checkBox.setObjectName("checkBox");
//    checkBox.setGeometry(QRect(920, 850, 341, 81));
//    QFont font3;
//    font3.setPointSize(18);
//    checkBox.setFont(font3);
//    checkBox.setStyleSheet(QString::fromUtf8("QCheckBox::indicator {width: 30 px; height: 30 px; \n"
//                                             "background-color: blue;border-color: black; border-style: solid;border-width: 1px}\n"
//                                             "QCheckBox:checked, QCheckBox::indicator:checked {border-color: black;}\n"
//                                             "QCheckBox::indicator:checked {background-color: red}"));

    w.setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
    pushButton.setText(QCoreApplication::translate("MainWindow", "Генерировать", nullptr));
    label1.setText(QCoreApplication::translate("MainWindow", "W", nullptr));
    label2.setText(QCoreApplication::translate("MainWindow", "H", nullptr));
//    checkBox.setText(QCoreApplication::translate("MainWindow", "Интерактивный режим", nullptr));

    PainterPath painterPath(&mainWidget);

    w.setCentralWidget(&painterPath);
    painterPath.setGeometry(QRect(0, 0, 1400, 950));
    QMetaObject::connectSlotsByName(&w);

    w.show();
    return a.exec();
}
