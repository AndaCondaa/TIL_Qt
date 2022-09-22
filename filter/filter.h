#ifndef FILTER_H
#define FILTER_H

#include <QObject>

class Filter : public QObject{
    Q_OBJECT
public:
    explicit Filter(QObject* parent = nullptr);

    bool eventFilter(QObject*, QEvent*);
};

#endif // FILTER_H
