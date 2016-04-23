#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QShortcut>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  
  addActions();
  addShortcuts();
}

MainWindow::~MainWindow() {
  delete ui;
}


void MainWindow::addActions() {
  connect( ui->bCreate, SIGNAL(clicked()), this, SLOT(bCreateClick()) );
  connect( ui->bBrowse, SIGNAL(clicked()), this, SLOT(bBrowseClick()) );
}

void MainWindow::addShortcuts() {
  QShortcut *bCreate=new QShortcut(QKeySequence("Ctrl+Q"), this);
  connect( bCreate, SIGNAL(activated()), ui->bCreate, SLOT(click()) );

  QShortcut *bBrowse=new QShortcut(QKeySequence("Ctrl+O"), this);
  connect( bBrowse, SIGNAL(activated()), ui->bBrowse, SLOT(click()) );

  QShortcut *quit=new QShortcut(QKeySequence("Esc"), this);
  connect( quit, SIGNAL(activated()), this, SLOT(close()) );
}


// ---------------------------------------------- button handlers ----------------------------------------------

void MainWindow::bCreateClick(){
  destPath=formatPath(path());
  if(destPath.length()==0){
    ui->bBrowse->click();
    return;
  }
  
  QStringList dirList=getDirList();
  foreach(QString dir, dirList){
    createDir(destPath, dir);
  }

  status("Folders created");
}

void MainWindow::bBrowseClick(){
  QString dir=path();
  if(dir.length()==0) dir=QDir::currentPath();

  QString dirname = QFileDialog::getExistingDirectory(this, tr("Select a Directory"), dir);
  if( !dirname.isNull() ) {
    setPath(dirname);
  }
}


// --------------------------------------------- model ---------------------------------------------

QStringList MainWindow::getDirList(){
  QStringList list, list1, list2;
  QString folder;
  
  QString foldersText=folders();
  foldersText=foldersText.trimmed();
  list=foldersText.split("\n");
  
  for(int i=0; i<list.size(); i++){
    list[i]=formatDir(list[i]);
  }
  
  return list;
}

void MainWindow::createDir(QString path, QString dir){
  QDir d(path);
//  d.mkdir(dir);
  d.mkpath(dir);
}


// --------------------------------------------- set/get ---------------------------------------------

QString MainWindow::folders(){
  return ui->teFolders->toPlainText();
}

QString MainWindow::path(){
  return ui->lePath->text();
}

void MainWindow::setPath(QString path){
  ui->lePath->setText(path);
}

// --------------------------------------------- helpers ---------------------------------------------

QString MainWindow::formatPath(QString path){
  path=path.replace("\\", "/");
  path=path.trimmed();
  return path;
}

QString MainWindow::formatDir(QString dir){
  dir=dir.trimmed();
  return dir;
}

void MainWindow::status(QString msg, bool permanent){
  int timeout=3000;
  if(permanent) timeout=0;
  ui->statusBar->showMessage(msg, timeout);
}
