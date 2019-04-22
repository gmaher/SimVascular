#ifndef svML_H
#define svML_H

#include <QmitkFunctionality.h>
#include <QString>
#include <string>
#include "svMLUtils.h"
#include "sv4gui_DataNodeOperationInterface.h"
#include "sv4gui_DataNodeOperation.h"
#include "sv4gui_ContourGroup.h"
#include "sv4gui_PathElement.h"

//socket includes
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#include <json.hpp>
using json = nlohmann::json;

namespace Ui {
class svML;
}

class svML : public QmitkFunctionality
{
    Q_OBJECT

public:

    svML();

    virtual ~svML();

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

  svMLUtils* ml_utils;

  Ui::svML *ui;

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

#endif // SVML_H
