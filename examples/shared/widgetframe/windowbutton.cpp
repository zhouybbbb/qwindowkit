#include "windowbutton.h"
#include "windowbutton_p.h"

#include <QtCore/QDebug>
#include <QtGui/QtEvents>

namespace QWK {

    WindowButtonPrivate::WindowButtonPrivate() = default;

    WindowButtonPrivate::~WindowButtonPrivate() = default;

    void WindowButtonPrivate::init() {
    }

    void WindowButtonPrivate::reloadIcon() {
        Q_Q(WindowButton);

        if (!q->isEnabled() && !iconDisabled.isNull()) {
            q->setIcon(iconDisabled);
            return;
        }

        if (q->isChecked() && !iconChecked.isNull()) {
            q->setIcon(iconChecked);
            return;
        }

        if (!iconNormal.isNull()) {
            q->setIcon(iconNormal);
        }
    }

    WindowButton::WindowButton(QWidget *parent) : WindowButton(*new WindowButtonPrivate(), parent) {
    }

    WindowButton::~WindowButton() = default;

    QIcon WindowButton::iconNormal() const {
        Q_D(const WindowButton);
        return d->iconNormal;
    }

    void WindowButton::setIconNormal(const QIcon &icon) {
        Q_D(WindowButton);
        d->iconNormal = icon;
        d->reloadIcon();
    }

    QIcon WindowButton::iconChecked() const {
        Q_D(const WindowButton);
        return d->iconChecked;
    }

    void WindowButton::setIconChecked(const QIcon &icon) {
        Q_D(WindowButton);
        d->iconChecked = icon;
        d->reloadIcon();
    }

    QIcon WindowButton::iconDisabled() const {
        Q_D(const WindowButton);
        return d->iconDisabled;
    }

    void WindowButton::setIconDisabled(const QIcon &icon) {
        Q_D(WindowButton);
        d->iconDisabled = icon;
        d->reloadIcon();
    }

    void WindowButton::checkStateSet() {
        Q_D(WindowButton);
        d->reloadIcon();
    }

    void WindowButton::mouseDoubleClickEvent(QMouseEvent *event) {
        if (event->button() == Qt::LeftButton) {
            Q_EMIT doubleClicked();
        }
    }

    WindowButton::WindowButton(WindowButtonPrivate &d, QWidget *parent)
        : QPushButton(parent), d_ptr(&d) {
        d.q_ptr = this;

        d.init();
    }

}
