#pragma once
#include <QString>
#include <QStringList>
#include <QList>
#include "readable.h"
#include "ProgressBarUse.h"
#include "DebugerSetter.h"

class FolderGenerator;
constexpr char BACK_SLASH{'/'};

struct FileInfo{
    QString name;
    QString path;
};

using FileList = QList<FileInfo>;

class FolderReader : public Readable, public ProgressBarUse, public DebugerSetter{
public:
    FolderReader(std::shared_ptr<FolderGenerator> folderGen, QProgressBar* pb): ProgressBarUse(pb), folderGenerator(folderGen){};

    virtual void copyFiles(bool override) = 0;
    virtual void readList(QStringList* paths);

protected:
    virtual void findNameAndSavePaths(QString& path);
    virtual QString findNameInDirectory(QString& directory) = 0;

    bool isDuplicated(QString& name);
    void appendLists(QString& name, QString& path);

    FileList folders;
    std::shared_ptr<FolderGenerator> folderGenerator;

    // Readable interface
public:
    QStringList getList() override;
};


