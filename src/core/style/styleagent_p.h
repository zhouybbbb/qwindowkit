#ifndef STYLEAGENTPRIVATE_H
#define STYLEAGENTPRIVATE_H

//
//  W A R N I N G !!!
//  -----------------
//
// This file is not part of the QWindowKit API. It is used purely as an
// implementation detail. This header file may change from version to
// version without notice, or may even be removed.
//

#include <QtCore/QHash>

#include <QWKCore/styleagent.h>

namespace QWK {

    class StyleAgentPrivate : public QObject {
        Q_DECLARE_PUBLIC(StyleAgent)
    public:
        StyleAgentPrivate();
        ~StyleAgentPrivate() override;

        void init();

        StyleAgent *q_ptr;

        StyleAgent::SystemTheme systemTheme = StyleAgent::Unknown;

        void setupSystemThemeHook();
        void removeSystemThemeHook();

        void notifyThemeChanged(StyleAgent::SystemTheme theme);
    };

}

#endif // STYLEAGENTPRIVATE_H