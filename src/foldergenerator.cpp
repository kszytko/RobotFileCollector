#include "foldergenerator.h"
#include "Debuger.h"

#include <QDir>

void FolderGenerator::selectPath(QString const&  path) {
    pathSelected = true;
    outputPath = path;
    initDirectioriesPaths();
}

void FolderGenerator::createFolders(std::shared_ptr<FolderReader> robotReader) {
    if (!pathSelected)
        return;
    createInitFolders();
    createSubfolders(robotReader->getList());
}

void FolderGenerator::initDirectioriesPaths() {
    pathsPath = outputPath + BACK_SLASH + "01_paths";
    programsPath = outputPath + BACK_SLASH + "02_programs";
    madaPath = outputPath + BACK_SLASH + "03_mada";
}

void FolderGenerator::createInitFolders() {
    createDirectoryIfNotExists(pathsPath);
    createDirectoryIfNotExists(programsPath);
    createDirectoryIfNotExists(madaPath);
}

void FolderGenerator::createDirectoryIfNotExists(QString newFolderPath) {
    QDir dir(newFolderPath);

    debuger->insert("Create dir: " + newFolderPath);

    if (!dir.exists())
        dir.mkpath(".");
}

void FolderGenerator::createSubfolders(QStringList robots) {
    statusInit(robots.length());
    for (auto& robot : robots) {
        statusUpdate();
        createSubfolderInMains(robot);
    }
}

void FolderGenerator::createSubfolderInMains(QString& stationName) {
    createDirectoryIfNotExists(pathsPath + BACK_SLASH + stationName);
    createDirectoryIfNotExists(programsPath + BACK_SLASH + stationName);
    createDirectoryIfNotExists(madaPath + BACK_SLASH + stationName);
}
