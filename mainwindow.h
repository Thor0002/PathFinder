#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTableWidget>
#include <QLabel>
#include <QLineEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
//    ~MainWindow();
    void setPushButton( QPushButton * new_pushButton);
    void setTableWidget( QTableWidget * new_tableWidget);
    void setWidth( QLineEdit * new_Width);
    void setHeight( QLineEdit * new_Height);

    static int item_size;
    static std::vector<std::vector<int>> table;

    bool isSetA = false;
    bool isSetB = false;
    static int row_A;
    static int column_A;
    static int row_B;
    static int column_B;

private slots:
    void on_tableWidget_cellClicked(int row, int column);

    void on_pushButton_clicked();

//    void on_checkBox_stateChanged(int checkState);

private:
    void resizeTable(int row, int column);

    void setPoint(int row, int column, QString p);

    void removePoint(int row, int column);

    QTableWidget * tableWidget;
    QPushButton * pushButton;
    QLineEdit * width;
    QLineEdit * height;

    int const field_width = 1200;
    int const field_height = 800;


//    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
