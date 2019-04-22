#set(lib ${SV_LIB_MODULE_MACHINELEARNING_NAME})

#set(lib ${SV_LIB_MODULE_IMAGEPROCESSING_NAME})
set(lib "_simvascular_module_machinelearning")

#-----------------------------------------------------------------------------
# Create module
simvascular_create_module(
  TARGET ${lib}
  EXPORT_DIRECTIVE sv4guiModuleMachineLearning
  SHARED_LIB ${SV_USE_MODULES_SHARED_LIBRARIES}
  LIBRARY_DEPENDS
  ${MITK_LIBRARIES}
  ${ITK_LIBRARIES}
  ${QT_LIBRARIES})
#-----------------------------------------------------------------------------

if(SV_INSTALL_LIBS)
  install(TARGETS ${lib}
    RUNTIME DESTINATION ${SV_INSTALL_RUNTIME_DIR} COMPONENT CoreExecutables
    LIBRARY DESTINATION ${SV_INSTALL_LIBRARY_DIR} COMPONENT CoreLibraries
    ARCHIVE DESTINATION ${SV_INSTALL_ARCHIVE_DIR} COMPONENT CoreLibraries
  )
endif()

if(SV_INSTALL_HEADERS)
  set(MODULE_FILES_CMAKE files.cmake)
  if(NOT IS_ABSOLUTE ${MODULE_FILES_CMAKE})
    set(MODULE_FILES_CMAKE ${CMAKE_CURRENT_SOURCE_DIR}/${MODULE_FILES_CMAKE})
  endif()
  if (EXISTS ${MODULE_FILES_CMAKE})
    include(${MODULE_FILES_CMAKE})
  endif()
  install(FILES ${H_FILES}
    DESTINATION ${SV_INSTALL_INCLUDE_DIR}/core COMPONENT CoreHeaders
  )
endif()

#############################################################
# Github and python stuff
#############################################################
# set(SV_PYTHON_DIR      ${SimVascular_BINARY_DIR}/../Externals-build/svExternals/bin/python-3.5.5)
# set(SV_PYTHON_BIN      ${SV_PYTHON_DIR}/bin/python)
# set(SV_PYTHON_INCLUDES ${SV_PYTHON_DIR}/include/python3.5m)
# set(SV_PYTHON_LIB      ${SV_PYTHON_DIR}/lib/libpython3.5m.so)
#
# include_directories(${SV_PYTHON_INCLUDES})
# target_link_libraries(${lib} PRIVATE ${SV_PYTHON_LIB})
#
# include(ExternalProject)
#
# ExternalProject_Add("seg_regression"
#   SOURCE_DIR        ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/seg_regression
#   GIT_REPOSITORY    "https://github.com/gmaher/seg_regression.git"
#   GIT_TAG           "master"
#   UPDATE_COMMAND    ""
#   CONFIGURE_COMMAND ""
#   BUILD_COMMAND     ""
#   TEST_COMMAND      ""
#   INSTALL_COMMAND   ""
# )
#
# ExternalProject_Add("networks"
#   URL               http://simvascular.stanford.edu/downloads/public/machine_learning/networks.tar
#   DOWNLOAD_DIR      ${CMAKE_SOURCE_DIR}
#   SOURCE_DIR        ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/seg_regression/results
#   UPDATE_COMMAND    ""
#   CONFIGURE_COMMAND ""
#   BUILD_COMMAND     ""
#   INSTALL_COMMAND   ""
#   DEPENDS "seg_regression"
# )
#
# file(MAKE_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/python_packages)
#
# ExternalProject_Add("python_packages"
#   DOWNLOAD_COMMAND  ""
#   BUILD_COMMAND     ${SV_PYTHON_BIN} -m pip install --target=${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/python_packages -r ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/seg_regression/requirements.txt
#   UPDATE_COMMAND    ""
#   CONFIGURE_COMMAND ""
#   INSTALL_COMMAND   ""
#   DEPENDS "seg_regression"
# )
