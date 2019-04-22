#include "sv4gui_MachineLearningUtils.h"
#include "sv4gui_MachineLearning.h"
#include "ui_sv4gui_MachineLearning.h"

#include "sv4gui_Path.h"
#include "sv4gui_ContourGroup.h"

#include <vtkImageData.h>
#include <mitkDataStorage.h>
#include <mitkDataNode.h>
#include <mitkNodePredicateDataType.h>
#include <mitkUndoController.h>

#include <usModuleRegistry.h>
#include <usGetModuleContext.h>
#include <usModule.h>
#include <usModuleContext.h>
#include <QInputDialog>

#include <QDir>
#include <QString>
#include <QDomDocument>
#include <QDomElement>
#include <QFile>
#include <QAbstractItemView>
#include <QListWidgetItem>


const QString sv4guiMachineLearning::EXTENSION_ID = "org.sv.views.machinelearning";

sv4guiMachineLearning::sv4guiMachineLearning() :
  ui(new Ui::sv4guiMachineLearning)
{

}

sv4guiMachineLearning::~sv4guiMachineLearning(){
  delete ui;
}

void sv4guiMachineLearning::initialize(){
  std::cout << "initializing\n";
  mitk::NodePredicateDataType::Pointer isProjFolder = mitk::NodePredicateDataType::New("sv4guiProjectFolder");
  mitk::DataNode::Pointer projFolderNode = GetDataStorage()->GetNode (isProjFolder);


  if (projFolderNode){
    std::string projPath;
    projFolderNode->GetStringProperty("project path", projPath);
    std::cout << "path " << projPath << "\n";

    QString QprojPath = QString(projPath.c_str());

    QDir dir(QprojPath);

    QString projectConfigFileName=".svproj";

    QString projectConfigFilePath=dir.absoluteFilePath(projectConfigFileName);

    std::string projConfigFile = projectConfigFilePath.toStdString();

    std::cout << "config filename " << projConfigFile << "\n";

    //get image path
    QDomDocument doc("svproj");
    QString imageFolderName="Images";

    QFile xmlFile(projectConfigFilePath);
    xmlFile.open(QIODevice::ReadOnly);

    QString *em=NULL;
    doc.setContent(&xmlFile,em);
    xmlFile.close();

    QDomElement projDesc      = doc.firstChildElement("projectDescription");
    QDomElement imagesElement = projDesc.firstChildElement("images");
    imageFolderName           = imagesElement.attribute("folder_name");
    QDomNodeList imageList    = imagesElement.elementsByTagName("image");

    QDomNode imageNode = imageList.item(0);
    QDomElement imageElement=imageNode.toElement();

    QString inProj    = imageElement.attribute("in_project");
    QString imageName = imageElement.attribute("name");
    QString imagePath = imageElement.attribute("path");

    if(inProj=="yes")
    {
        if(imagePath!="")
        {
            m_imageFilePath = (projPath
            +"/"+imageFolderName.toStdString()+"/"+imagePath.toStdString());
        }
        else if(imageName!="")
        {
            m_imageFilePath = (projPath
            +"/"+imageFolderName.toStdString()+"/"+imageName.toStdString());
        }
    }
    else
    {
        m_imageFilePath = imageElement.attribute("path").toStdString();
    }

    std::cout << "Image filePath: " << m_imageFilePath << "\n";

    ml_utils = sv4guiMachineLearningUtils::getInstance("googlenet_c30_train300k_aug10_clean");
    ml_utils->setImage(m_imageFilePath);
  }//end if projectfoldernode
}

void sv4guiMachineLearning::CreateQtPartControl(QWidget *parent){
  initialize();
  m_Parent=parent;
  ui->setupUi(parent);

  m_DisplayWidget=GetActiveStdMultiWidget();

  if(m_DisplayWidget==NULL)
  {
      parent->setEnabled(false);
      MITK_ERROR << "Plugin ML Init Error: No QmitkStdMultiWidget!";
      return;
  }

  //display buttons
  m_Interface= new sv4guiDataNodeOperationInterface();

  //connect(ui->msgButton, SIGNAL(clicked()), this, SLOT(setImage()));
  connect(ui->msgButton_2, SIGNAL(clicked()), this, SLOT(segmentPaths()));

  connect(ui->selectAllPathsCheckBox, SIGNAL(clicked()), this, SLOT(selectAllPaths()));

  connect(ui->sampleNetButton, SIGNAL(clicked()), this, SLOT(sampleNetwork()));

  //ui->pathList->setSelectionMode(QAbstractItemView::ExtendedSelection);

  updatePaths();
}

void sv4guiMachineLearning::selectAllPaths(){
  bool checked = (ui->selectAllPathsCheckBox->checkState() == Qt::Checked);

  for (int i = 0; i < ui->pathList->count(); i++){
    if (checked){
      ui->pathList->item(i)->setCheckState(Qt::Checked);
    }else{
      ui->pathList->item(i)->setCheckState(Qt::Unchecked);
    }
  }
}

void sv4guiMachineLearning::updatePaths(){
  auto path_folder_node = GetDataStorage()->GetNamedNode("Paths");
  auto rs       = GetDataStorage()->GetDerivations(path_folder_node);

  if (rs->size() == 0){
    std::cout << "No paths found\n";
    return ;
  }

  ui->pathList->clear();

  for (int i = 0; i < rs->size(); i++){
    mitk::DataNode::Pointer Node=rs->GetElement(i);
    std::cout << i << ": " << Node->GetName() << "\n";

    //auto q_name = QString(Node->GetName().c_str());

    auto item = new QListWidgetItem(Node->GetName().c_str(), ui->pathList);
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
    item->setCheckState(Qt::Unchecked);

    ui->pathList->addItem(item);
  }
}

void sv4guiMachineLearning::setImage(){
  std::string status = ml_utils->setImage(m_imageFilePath);
  std::cout << "set image status " << status << "\n";
}

void sv4guiMachineLearning::segmentPaths(){
  //paths
  auto path_folder_node = GetDataStorage()->GetNamedNode("Paths");
  auto paths_list       = GetDataStorage()->GetDerivations(path_folder_node);

  m_selected_paths.clear();

  for (int i = 0; i < ui->pathList->count(); i++){
    if (ui->pathList->item(i)->checkState() == Qt::Checked){
      auto name = ui->pathList->item(i)->text().toStdString();
      m_selected_paths.push_back(name);
      std::cout << "selected " << name << "\n";
    }
  }

  for (int i = 0; i < m_selected_paths.size(); i++){
    auto path_name = m_selected_paths[i];

    for (int j = 0; j < paths_list->size(); j++){
      auto path_node = paths_list->GetElement(j);

      if (path_node->GetName() == path_name){
        m_current_path_node = path_node;
        std::cout << "segmenting " << path_name << "\n";

        createContourGroup(path_name);

        segmentPath();

        break;
      }

    }
  }
}

void sv4guiMachineLearning::createContourGroup(std::string path_name){
  auto seg_folder_node = GetDataStorage()->GetNamedNode("Segmentations");

  m_current_group = sv4guiContourGroup::New();
  m_current_group->SetPathName(path_name);
  m_current_group->SetDataModified();

  sv4guiPath* selectedPath=dynamic_cast<sv4guiPath*>(m_current_path_node->GetData());

  m_current_group->SetPathID(selectedPath->GetPathID());

  auto seg_node = mitk::DataNode::New();
  seg_node->SetName(path_name);
  seg_node->SetData(m_current_group);

  GetDataStorage()->Add(seg_node, seg_folder_node);
}

void sv4guiMachineLearning::segmentPath(){
  auto path = dynamic_cast<sv4guiPath*>(m_current_path_node->GetData());

  auto path_element = path->GetPathElement(0);

  auto path_points = path_element->GetPathPoints();

  int n = 0;

  m_interval = std::stoi(ui->intervalEdit->text().toStdString());
  m_numFourierModes = std::stoi(ui->intervalEdit->text().toStdString());

  for(int k = 0; k < path_points.size(); k += m_interval){

    doSegmentation(path_points[k], k, n);
    n+=1;

  }
}

/*
1. call svMlUtils segmentation (double[3] pos, tan, rot)
2. convert to json
3. convert to string
4. call svwrapper segment
5. segment
6. denormalize contour
7. convert to dict
8. convert to string
9. convert to json
10. convert to contour
11. insert into contour group
*/

void sv4guiMachineLearning::doSegmentation(sv4guiPathElement::sv4guiPathPoint path_point,
int index, int n_){


  std::vector<std::vector<double>> points = ml_utils->segmentPathPoint(path_point);

  if (points.size() <= 0){
    std::cout << "contour " << index << " empty points\n";
    return;
  }

  sv4guiContour* contour = new sv4guiContour();

  //create contour and add points
  contour->SetPathPoint(path_point);
  contour->SetPlaced(true);
  contour->SetMethod("ML");

  std::vector<mitk::Point3D> contourPoints;
  mitk::Point3D pt;

  for (int i = 0; i < points.size(); i++){
    pt[0] = points[i][0];
    pt[1] = points[i][1];
    pt[2] = points[i][2];

    contourPoints.push_back(pt);
  }

  contour->SetClosed(true);

  contour->SetContourPoints(contourPoints);
  contour = contour->CreateSmoothedContour(m_numFourierModes);

  m_current_group->IsEmptyTimeStep(0);

  m_current_group->InsertContour(n_, contour, 0);
  mitk::RenderingManager::GetInstance()->RequestUpdateAll();
}

void sv4guiMachineLearning::sampleNetwork(){
  ml_utils->sampleNetwork();
}
