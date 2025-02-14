#include "qwkquickglobal.h"

#include <QtQml/QQmlEngine>

#include "quickwindowagent.h"

namespace QWK {

    static constexpr const char kModuleUri[] = "QWindowKit";

    void registerTypes(QQmlEngine *engine) {
        Q_UNUSED(engine);

        static bool once = false;
        if (once) {
            return;
        }
        once = true;

        qmlRegisterType<QuickWindowAgent>(kModuleUri, 1, 0, "WindowAgent");
        qmlRegisterModule(kModuleUri, 1, 0);
    }

}
