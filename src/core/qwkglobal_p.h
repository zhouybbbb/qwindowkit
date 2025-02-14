#ifndef QWKGLOBAL_P_H
#define QWKGLOBAL_P_H

//
//  W A R N I N G !!!
//  -----------------
//
// This file is not part of the QWindowKit API. It is used purely as an
// implementation detail. This header file may change from version to
// version without notice, or may even be removed.
//

#include <QtCore/QLoggingCategory>
#include <QtGui/QMouseEvent>

#include <QWKCore/qwkglobal.h>

QWK_CORE_EXPORT Q_DECLARE_LOGGING_CATEGORY(qWindowKitLog)

#define QWK_INFO     qCInfo(qWindowKitLog)
#define QWK_DEBUG    qCDebug(qWindowKitLog)
#define QWK_WARNING  qCWarning(qWindowKitLog)
#define QWK_CRITICAL qCCritical(qWindowKitLog)
#if QT_VERSION >= QT_VERSION_CHECK(6, 6, 0)
#  define QWK_FATAL qCFatal(qWindowKitLog)
#endif

#define MAKE_RGB_COLOR(r, g, b) ((quint32) (((r) &0xFF) << 16) | (((g) &0xFF) << 8) | ((b) &0xFF))

#define MAKE_RGBA_COLOR(r, g, b, a)                                                                \
    ((quint32) (((a) &0xFF) << 24) | (((r) &0xFF) << 16) | (((g) &0xFF) << 8) | ((b) &0xFF))

#if defined(Q_CC_MSVC)
#  define QWK_NOINLINE __declspec(noinline)
#  define QWK_INLINE   __forceinline
#  define QWK_USED
#else
#  define QWK_NOINLINE __attribute__((noinline))
#  define QWK_INLINE   __attribute__((always_inline))
#  define QWK_USED     __attribute__((used))
#endif

namespace QWK {

    inline QPoint getMouseEventScenePos(const QMouseEvent *event) {
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
        return event->scenePosition().toPoint();
#else
        return event->windowPos().toPoint();
#endif
    }
    
    inline QPoint getMouseEventGlobalPos(const QMouseEvent *event) {
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
        return event->globalPosition().toPoint();
#else
        return event->screenPos().toPoint();
#endif
    }
    
}

#endif // QWKGLOBAL_P_H
