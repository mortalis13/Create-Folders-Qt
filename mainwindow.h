#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  
  QString path();
  void setPath(QString path);
  QString folders();
  
  
  void createFile(QString path, QString filePath);
  void createFileInFolder(QString path, QString filename);

private:
  Ui::MainWindow *ui;
  QString destPath;
  
private:
  void addActions();
  void addShortcuts();
  
  void createDir(QString path, QString dirs);
  QStringList getDirList();
  
  QString formatPath(QString path);
  QString formatDir(QString path);
    
  void status(QString msg, bool permanent=false);
  
private slots:
  void bCreateClick();
  void bBrowseClick();  
  void rbFoldersCheck();
  void rbFilesCheck();
  
};

#endif // MAINWINDOW_H
