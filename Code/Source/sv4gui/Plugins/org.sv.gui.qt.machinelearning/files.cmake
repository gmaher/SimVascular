set(SRC_CPP_FILES

)

set(INTERNAL_CPP_FILES
    sv4guiMachineLearning.cxx
    sv4guiMachineLearningPluginActivator.cxx
)

set(MOC_H_FILES
    src/internal/sv4guiMachineLearning.h
    src/internal/sv4guiMachineLearningPluginActivator.h
    src/internal/json.hpp
)

set(UI_FILES
    src/internal/sv4guiMachineLearning.ui
)

set(CACHED_RESOURCE_FILES
  plugin.xml
  resources/hello.png
)

set(QRC_FILES

)

set(CPP_FILES )

foreach(file ${SRC_CPP_FILES})
  set(CPP_FILES ${CPP_FILES} src/${file})
endforeach(file ${SRC_CPP_FILES})

foreach(file ${INTERNAL_CPP_FILES})
  set(CPP_FILES ${CPP_FILES} src/internal/${file})
endforeach(file ${INTERNAL_CPP_FILES})
