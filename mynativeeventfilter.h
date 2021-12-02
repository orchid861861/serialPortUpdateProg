#ifndef MYNATIVEEVENTFILTER_H
#define MYNATIVEEVENTFILTER_H

#include <QAbstractNativeEventFilter>
#include <QWidget>

#include <Windows.h>
#include <dbt.h>

class myNativeEventFilter : public QWidget,public QAbstractNativeEventFilter //先继承QWidget,否则报错。
{
    Q_OBJECT
public:
    myNativeEventFilter();
    bool nativeEventFilter(const QByteArray &eventType, void *message, long *result) override;
signals:
    void addPort(QString& comPort);
    void removePort(QString& comPort);
};

#endif // MYNATIVEEVENTFILTER_H
