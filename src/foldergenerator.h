#pragma once
#include "folderreader.h"
#include "ProgressBarUse.h"
#include "DebugerSetter.h"

class FolderGenerator : public ProgressBarUse, public DebugerSetter
{
public:
    FolderGenerator(QProgressBar* pb) : ProgressBarUse(pb) {};

    void selectPath(QString const& path);
    void createFolders(std::shared_ptr<FolderReader> robotReader);

public:
    QString getPathsPath() { return pathsPath; };
    QString getProgramsPath() { return programsPath; };
    QString getMadaPath() { return madaPath; };


private:
    void initDirectioriesPaths();
    void createInitFolders();
    void createDirectoryIfNotExists(QString newFolderName);
    bool checkIfDirectoryExists(QString& path);
    void createSubfolders(QStringList robots);
    void createDirectory(QString& path);
    void createSubfolderInMains(QString& stationName);

private:
    QString outputPath, pathsPath, programsPath, madaPath;
    bool pathSelected;
};


