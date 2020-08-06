#pragma once

#include <QMainWindow>
#include <QFileDialog>
#include <QTextEdit>

#include <memory>

#include "src/foldergenerator.h"
#include "src/downloadReader.h"
#include "src/madareader.h"
#include "src/folderreader.h"
#include "src/configreader.h"
#include "src/safetyreader.h"
#include "src/readable.h"
#include "src/DebugerSetter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow, public DebugerSetter
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_6_clicked();

    void on_buttonSafetyXML_clicked();

private:
    void initDebuger(QString path);
    bool tryOpenFolderDialog();
    void updateTextBox(QString path);
    void groupsBoxEnabled(bool enable);
    void updateListBox(QTextEdit* textEdit,Readable* reader);

    QStringList selectSubfolders();
    QString selectFolder();
    QStringList selectFiles();

private:
    Ui::MainWindow *ui;

    std::shared_ptr<FolderGenerator> folderGen;
    std::shared_ptr<DownloadReader> robotReader;
    std::shared_ptr<MadaReader> madaReader;
    std::shared_ptr<ConfigReader> configReader;
    std::shared_ptr<SafetyReader> safetyReader;

    QFileDialog folderDialog{this};    
    QFile file;
};

