#include "quickitemdelegate_p.h"

#include <QtQuick/QQuickItem>
#include <QtQuick/QQuickWindow>

namespace QWK {

    QuickItemDelegate::QuickItemDelegate() : WindowItemDelegate() {
    }

    QuickItemDelegate::~QuickItemDelegate() = default;

    QWindow *QuickItemDelegate::window(const QObject *obj) const {
        return static_cast<const QQuickItem *>(obj)->window();
    }

    bool QuickItemDelegate::isEnabled(const QObject *obj) const {
        return static_cast<const QQuickItem *>(obj)->isEnabled();
    }

    bool QuickItemDelegate::isVisible(const QObject *obj) const {
        return static_cast<const QQuickItem *>(obj)->isVisible();
    }

    QRect QuickItemDelegate::mapGeometryToScene(const QObject *obj) const {
        auto item = static_cast<const QQuickItem *>(obj);
        const QPointF originPoint = item->mapToScene(QPointF(0.0, 0.0));
        const QSizeF size = item->size();
        return QRectF(originPoint, size).toRect();
    }

    QWindow *QuickItemDelegate::hostWindow(const QObject *host) const {
        return static_cast<QQuickWindow *>(const_cast<QObject *>(host));
    }

    bool QuickItemDelegate::isHostSizeFixed(const QObject *host) const {
        const auto window = static_cast<const QQuickWindow *>(host);
        const auto minSize = window->minimumSize();
        const auto maxSize = window->maximumSize();
        return !minSize.isEmpty() && !maxSize.isEmpty() && minSize == maxSize;
    }

    bool QuickItemDelegate::isWindowActive(const QObject *host) const {
        return static_cast<const QQuickWindow *>(host)->isActive();
    }

    Qt::WindowStates QuickItemDelegate::getWindowState(const QObject *host) const {
        return static_cast<const QQuickWindow *>(host)->windowStates();
    }

    void QuickItemDelegate::setWindowState(QObject *host, Qt::WindowStates state) const {
        static_cast<QQuickWindow *>(host)->setWindowStates(state);
    }

    void QuickItemDelegate::setCursorShape(QObject *host, const Qt::CursorShape shape) const {
        static_cast<QQuickWindow *>(host)->setCursor(QCursor(shape));
    }

    void QuickItemDelegate::restoreCursorShape(QObject *host) const {
        static_cast<QQuickWindow *>(host)->unsetCursor();
    }

    Qt::WindowFlags QuickItemDelegate::getWindowFlags(const QObject *host) const {
        return static_cast<const QQuickWindow *>(host)->flags();
    }

    void QuickItemDelegate::setWindowFlags(QObject *host, Qt::WindowFlags flags) const {
        static_cast<QQuickWindow *>(host)->setFlags(flags);
    }

    void QuickItemDelegate::setWindowVisible(QObject *host, bool visible) const {
        static_cast<QQuickWindow *>(host)->setVisible(visible);
    }

    void QuickItemDelegate::bringWindowToTop(QObject *host) const {
        static_cast<QQuickWindow *>(host)->raise();
    }

}