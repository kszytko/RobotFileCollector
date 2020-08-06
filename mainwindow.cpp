#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>
#include <QDirIterator>
#include <QStringList>
#include <QDateTime>

#include "src/Debuger.h"

#include <QStatusBar>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    statusBar()->showMessage("Version 1.2.1 K.Szytko");

    folderGen = std::make_shared<FolderGenerator>(ui->progressBar);
    robotReader = std::make_shared<DownloadReader>(folderGen, ui->progressBar);
    madaReader = std::make_shared<MadaReader>(folderGen,ui->progressBar);
    configReader = std::make_shared<ConfigReader>(folderGen, ui->progressBar);
    safetyReader = std::make_shared<SafetyReader>(folderGen, ui->progressBar);

    groupsBoxEnabled(false);
}

MainWindow::~MainWindow()
{
    file.close();
    delete ui;
}

void MainWindow::groupsBoxEnabled(bool enable)
{
    ui->groupBox->setEnabled(enable);
    ui->groupBox_3->setEnabled(enable);
    ui->groupBox_4->setEnabled(enable);
    ui->groupBox_5->setEnabled(enable);
}

void MainWindow::on_pushButton_clicked()
{


    auto path = selectFolder();
    if(path == "")
        return;

    initDebuger(path);
    groupsBoxEnabled(true);
    updateTextBox(path);
    folderGen->selectPath(path);

    debuger->start("MAIN", "Output dir :" + path);
    debuger->end();
}

void MainWindow::initDebuger(QString path)
{
    QString filename = QDateTime::currentDateTime().toString("'debugFile_'ddMMyyyy_hhmmss'.txt'");
    file.setFileName(path + BACK_SLASH + filename);

    debuger = std::make_shared<Debuger>(ui->debug, &file);

    folderGen->setDebuger(debuger);
    robotReader->setDebuger(debuger);
    madaReader->setDebuger(debuger);
    configReader->setDebuger(debuger);
    safetyReader->setDebuger(debuger);
}

QString MainWindow::selectFolder() {
    folderDialog.setFileMode(QFileDialog::FileMode::Directory);

    if (!tryOpenFolderDialog())
        return {};
    return folderDialog.selectedFiles().front();
}

QStringList MainWindow::selectFiles() {
    folderDialog.setFileMode(QFileDialog::FileMode::ExistingFiles);

    if (!tryOpenFolderDialog())
        return {};
    return folderDialog.selectedFiles();
}

bool MainWindow::tryOpenFolderDialog() {
    return folderDialog.exec();
}

void MainWindow::updateTextBox(QString path) {
    ui->lineEdit->setText(path);
}



void MainWindow::on_pushButton_2_clicked()
{
    auto paths = selectSubfolders();
    if(paths.empty())
        return;

    debuger->start("DOWNLOADS", "Reading downloads.");

    robotReader->readList(&paths);
    updateListBox(ui->textRobots, robotReader.get());

    debuger->end();
}

QStringList MainWindow::selectSubfolders() {
    auto path = selectFolder();
    QStringList paths;

    QDirIterator directories(path, QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot);
    while(directories.hasNext()){
        directories.next();
        paths.push_back(directories.filePath());
    }

    return paths;
}

void MainWindow::updateListBox(QTextEdit* textEdit, Readable* reader) {
    textEdit->clear();
    for(auto& el : reader->getList()){
        textEdit->append(el);
    }
}

void MainWindow::on_pushButton_3_clicked()
{

    auto paths = selectSubfolders();
    if(paths.empty())
        return;

    debuger->start("MADA", "Reading mada files.");

    madaReader->readList(&paths);
    updateListBox(ui->textMada, madaReader.get());

    debuger->end();
}

void MainWindow::on_pushButton_4_clicked()
{
    debuger->start("FOLDERS", "Generating folders.");

    folderGen->createFolders(robotReader);

    debuger->end();
}

void MainWindow::on_pushButton_6_clicked()
{

    auto paths = selectFiles();
    if(paths.empty())
        return;

    debuger->start("CONFIG", "Reading configs.");

    configReader->readList(&paths);

    debuger->end();
}

void MainWindow::on_buttonSafetyXML_clicked()
{

    auto paths = selectFiles();
    if(paths.empty())
        return;

    debuger->start("SAFETY", "Reading safety...");

    safetyReader->readList(&paths);
    updateListBox(ui->textSafety, safetyReader.get());

    debuger->end();
}



void MainWindow::on_pushButton_8_clicked()
{
    bool override = ui->checkBox->isChecked();

    debuger->start("D", "Copy robots downloads into folders.");
    robotReader->copyFiles(override);
    debuger->end();

    debuger->start("M","Copy mada files.");
    madaReader->copyFiles(override);
    debuger->end();

    debuger->start("C", "Copy config, machine and options.dat into mada folders.");
    configReader->copyFiles(override);
    debuger->end();

    debuger->start("S", "Copy safety files into mada folders.");
    safetyReader->copyFiles(override);
    debuger->end();

    debuger->insert("Copying process FINISHED! uff");
}






