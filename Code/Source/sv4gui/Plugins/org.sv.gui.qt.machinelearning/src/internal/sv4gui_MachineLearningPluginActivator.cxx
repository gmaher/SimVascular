#include "sv4gui_MachineLearningPluginActivator.h"
#include "sv4gui_MachineLearning.h"

void svMLPluginActivator::start(ctkPluginContext* context)
{

    BERRY_REGISTER_EXTENSION_CLASS(svML, context)

}

void svMLPluginActivator::stop(ctkPluginContext* context)
{

}
