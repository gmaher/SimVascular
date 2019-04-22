#ifndef sv4guiMachineLearning_H
#define sv4guiMachineLearning_H

#include <sv4gui_QmitkFunctionality.h>
#include <QString>
#include <string>
#include "sv4gui_MachineLearningUtils.h"
#include "sv4gui_DataNodeOperationInterface.h"
#include "sv4gui_DataNodeOperation.h"
#include "sv4gui_ContourGroup.h"
#include "sv4gui_PathElement.h"

namespace Ui {
class sv4guiMachineLearning;
}

class sv4guiMachineLearning : public sv4guiQmitkFunctionality
{
    Q_OBJECT

public:

    sv4guiMachineLearning();

    virtual ~sv4guiMachineLearning();

    virtual void CreateQtPartControl(QWidget *parent) override;

    static const QString EXTENSION_ID;

    void initialize();

    void segmentPath();

    void updatePaths();

    void createContourGroup(std::string path_name);

public slots:

    void setImage();

    void segmentPaths();

    void selectAllPaths();

    void doSegmentation(sv4guiPathElement::sv4guiPathPoint, int index, int n);

    void sampleNetwork();

public:

protected:

  sv4guiMachineLearningUtils* ml_utils;

  Ui::sv4guiMachineLearning *ui;

  QWidget *m_parent;

  QmitkStdMultiWidget* m_DisplayWidget;

  sv4guiDataNodeOperationInterface* m_Interface;

  std::string m_imageFilePath;

  int m_interval = 50;

  int m_numFourierModes = 7;

  mitk::DataNode::Pointer m_current_path_node;

  std::vector<std::string> m_selected_paths;

  sv4guiContourGroup::Pointer m_current_group;

};

#endif // SV4GUIMACHINELEARNING_H
