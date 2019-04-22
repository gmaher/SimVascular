set(SRC_CPP_FILES

)

set(INTERNAL_CPP_FILES
    sv4gui_MachineLearning.cxx
    sv4gui_MachineLearningPluginActivator.cxx
)

set(MOC_H_FILES
    src/internal/sv4gui_MachineLearning.h
    src/internal/sv4gui_MachineLearningPluginActivator.h
)

set(UI_FILES
    src/internal/sv4gui_MachineLearning.ui
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
