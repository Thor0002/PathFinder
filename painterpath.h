#ifndef PAINTERPATH_H
#define PAINTERPATH_H

#include <QPainter>
#include <QWidget>
#include <vector>

class PainterPath : public QWidget {
public:
    PainterPath(QWidget * parent = 0);
    void findPath();

    static bool isStartPaintingPath;
    std::vector<std::vector<int>> table;

protected:
    void paintEvent(QPaintEvent * e) override;

};

struct Point {
    int row;
    int column;
};

#endif // PAINTERPATH_H
