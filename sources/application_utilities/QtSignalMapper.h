#ifndef QT_SIGNAL_MAPPER_H
#define QT_SIGNAL_MAPPER_H

#include <QObject>
#include "Settings.h"

class QtSignalMapper
    : public QObject
{
    Q_OBJECT

public:
    QtSignalMapper(QObject* parent = nullptr);

public slots:
    void playButtonClicked();
    void cameraModeChanged(int index);

private:
   Settings& settings_ = Settings::getInstance();
};

#endif // QT_SIGNAL_MAPPER_H