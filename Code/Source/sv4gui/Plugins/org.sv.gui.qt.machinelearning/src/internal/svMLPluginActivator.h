#ifndef SVMLPLUGINACTIVATOR_H
#define SVMLPLUGINACTIVATOR_H

#include <ctkPluginActivator.h>

class svMLPluginActivator :
        public QObject, public ctkPluginActivator
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org_sv_gui_qt_ml")
    Q_INTERFACES(ctkPluginActivator)

public:

//    static ctkPluginContext* GetContext();
//    static svPathPlanningPluginActivator* GetInstance();

    void start(ctkPluginContext* context) override;
    void stop(ctkPluginContext* context) override;

private:

};

#endif // SVMLPLUGINACTIVATOR_H
