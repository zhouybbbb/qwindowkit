#include "quickwindowagent.h"
#include "quickwindowagent_p.h"

#include <QtQuick/QQuickWindow>
#include <QtQuick/private/qquickanchors_p.h>

#include "quickitemdelegate_p.h"

namespace QWK {

    /*!
        \class QuickWindowAgent
        \brief QuickWindowAgent is the window agent for QtQuick.

        It provides interfaces for QtQuick and processes some Qt events related to the QQuickItem
        instance. The usage of all APIs is consistent with the \a Widgets module.
    */

    QuickWindowAgentPrivate::QuickWindowAgentPrivate() = default;

    QuickWindowAgentPrivate::~QuickWindowAgentPrivate() = default;

    void QuickWindowAgentPrivate::init() {
    }

    QuickWindowAgent::QuickWindowAgent(QObject *parent)
        : QuickWindowAgent(*new QuickWindowAgentPrivate(), parent) {
    }

    QuickWindowAgent::~QuickWindowAgent() = default;

    bool QuickWindowAgent::setup(QQuickWindow *window) {
        Q_ASSERT(window);
        if (!window) {
            return false;
        }

        Q_D(QuickWindowAgent);
        if (d->hostWindow) {
            return false;
        }

        d->setup(window, new QuickItemDelegate());
        d->hostWindow = window;

#if defined(Q_OS_WINDOWS) && QWINDOWKIT_CONFIG(ENABLE_WINDOWS_SYSTEM_BORDERS)
        d->setupWindows10BorderWorkaround();
#endif
        return true;
    }

    QQuickItem *QuickWindowAgent::titleBar() const {
        Q_D(const QuickWindowAgent);
        return static_cast<QQuickItem *>(d->context->titleBar());
    }

    void QuickWindowAgent::setTitleBar(QQuickItem *item) {
        Q_D(QuickWindowAgent);
        if (!d->context->setTitleBar(item)) {
            return;
        }
        Q_EMIT titleBarWidgetChanged(item);
    }

    QQuickItem *QuickWindowAgent::systemButton(SystemButton button) const {
        Q_D(const QuickWindowAgent);
        return static_cast<QQuickItem *>(d->context->systemButton(button));
    }

    void QuickWindowAgent::setSystemButton(SystemButton button, QQuickItem *item) {
        Q_D(QuickWindowAgent);
        if (!d->context->setSystemButton(button, item)) {
            return;
        }
        Q_EMIT systemButtonChanged(button, item);
    }

    bool QuickWindowAgent::isHitTestVisible(const QQuickItem *item) const {
        Q_D(const QuickWindowAgent);
        return d->context->isHitTestVisible(item);
    }

    void QuickWindowAgent::setHitTestVisible(const QQuickItem *item, bool visible) {
        Q_D(QuickWindowAgent);
        d->context->setHitTestVisible(item, visible);
    }

    /*!
        \internal
    */
    QuickWindowAgent::QuickWindowAgent(QuickWindowAgentPrivate &d, QObject *parent)
        : WindowAgentBase(d, parent) {
        d.init();
    }

}