#include "mynativeeventfilter.h"

myNativeEventFilter::myNativeEventFilter()
{

}
bool myNativeEventFilter::nativeEventFilter(const QByteArray & eventType, void * message, long * result)
{
    MSG* msg = reinterpret_cast<MSG*>(message);
    int msgType = msg->message;
    if (msgType == WM_DEVICECHANGE) {
        PDEV_BROADCAST_HDR lpdb = (PDEV_BROADCAST_HDR)msg->lParam;
        switch (msg->wParam) {
        case DBT_DEVICEARRIVAL:
            if (lpdb->dbch_devicetype == DBT_DEVTYP_PORT) {
                PDEV_BROADCAST_PORT lpdbv = (PDEV_BROADCAST_PORT)lpdb;
                QString port = QString::fromWCharArray(lpdbv->dbcp_name);//插入的串口名
                emit addPort(port);
            }
            break;
        case DBT_DEVICEREMOVECOMPLETE:
            if (lpdb->dbch_devicetype == DBT_DEVTYP_PORT) {
                PDEV_BROADCAST_PORT lpdbv = (PDEV_BROADCAST_PORT)lpdb;
                QString port = QString::fromWCharArray(lpdbv->dbcp_name);//拔出的串口名
                emit removePort(port);
            }
            break;
        case DBT_DEVNODES_CHANGED:
            break;
        default:
            break;
        }
    }
    return QWidget::nativeEvent(eventType, message, result);
}
