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
  
  
private:
  Ui::MainWindow *ui;
  QString destPath;
  
private:
  void addActions();
  void addShortcuts();
  
  void createDir(QString path, QString dir);
  QStringList getDirList();
  
  QString formatPath(QString path);
  QString formatDir(QString path);
    
  void status(QString msg, bool permanent=false);
  
private slots:
    void bCreateClick();
    void bBrowseClick();  
  
  
};

#endif // MAINWINDOW_H
