set(H_FILES
    svModelUtils.h
    svModelElement.h
    svModelElementPolyData.h
    svModelElementAnalytic.h
    svModelElementFactory.h
    svModelOperation.h
    svModel.h
    svModelVtkMapper2D.h
    svModelVtkMapper3D.h
    svModelDataInteractor.h
    svModelIO.h
    svModelLegacyIO.h
    svModelObjectFactory.h
)

if(SV_USE_OpenCASCADE_QT_GUI)
  set(H_FILES
      ${H_FILES}
      svModelElementOCCT.h
  )
endif()

if(SV_USE_PARASOLID)
  set(H_FILES
      ${H_FILES}
      svModelElementParasolid.h
  )
endif()

set(CPP_FILES
    svModelUtils.cxx
    svModelElement.cxx
    svModelElementPolyData.cxx
    svModelElementAnalytic.cxx
    svModelElementFactory.cxx
    svModelOperation.cxx
    svModel.cxx
    svModelVtkMapper2D.cxx
    svModelVtkMapper3D.cxx
    svModelDataInteractor.cxx
    svModelIO.cxx
    svModelLegacyIO.cxx
    svModelObjectFactory.cxx
    svRegisterPolyDataFunction.cxx
)

if(SV_USE_OpenCASCADE_QT_GUI)
  set(CPP_FILES
      ${CPP_FILES}
      svModelElementOCCT.cxx
      svRegisterOCCTFunction.cxx
  )
endif()

if(SV_USE_PARASOLID)
  set(CPP_FILES
      ${CPP_FILES}
      svModelElementParasolid.cxx
      svRegisterParasolidFunction.cxx
  )
endif()

set(RESOURCE_FILES
    Interactions/svModelInteraction.xml
    Interactions/svModelConfig.xml
)
