#ifndef WINDOWBARPRIVATE_H
#define WINDOWBARPRIVATE_H

#include <QBoxLayout>

#include "windowbar.h"

namespace QWK {

    class WindowBarPrivate {
        Q_DECLARE_PUBLIC(WindowBar)
    public:
        WindowBarPrivate();
        virtual ~WindowBarPrivate();

        void init();

        WindowBar *q_ptr;

        QWidget *w;
        bool autoTitle;
        bool autoIcon;

        enum WindowBarItem {
            IconButton,
            MenuWidget,
            TitleLabel,
            MinimumButton,
            MaximumButton,
            CloseButton,
        };

        QHBoxLayout *layout;

        inline QWidget *widgetAt(int index) const {
            return layout->itemAt(index)->widget();
        }

        void setWidgetAt(int index, QWidget *widget);

        QWidget *takeWidgetAt(int index);

        inline void insertDefaultSpace(int index) {
            layout->insertSpacerItem(index, new QSpacerItem(0, 0));
        }

    private:
        Q_DISABLE_COPY_MOVE(WindowBarPrivate)
    };

}

#endif // WINDOWBARPRIVATE_H