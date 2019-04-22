#include "svMLPluginActivator.h"
#include "svML.h"

void svMLPluginActivator::start(ctkPluginContext* context)
{

    BERRY_REGISTER_EXTENSION_CLASS(svML, context)

}

void svMLPluginActivator::stop(ctkPluginContext* context)
{

}
