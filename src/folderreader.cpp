#include "folderreader.h"
#include "Debuger.h"

#include <algorithm>


void FolderReader::readList(QStringList* paths){
    statusInit(paths->length());
    for( auto& path : *paths) {
        statusUpdate();
        debuger->insert("Reading folder: " + path);
        findNameAndSavePaths(path);
    }
}

void FolderReader::findNameAndSavePaths(QString& path){
    auto name = findNameInDirectory(path);
    if (isDuplicated(name))
        return;
    appendLists(name, path);
}

bool FolderReader::isDuplicated(QString& name){
    return std::find_if(folders.begin(), folders.end(),
                        [&](auto file){
                            return file.name == name;
                        }
            ) != folders.end();

}

void FolderReader::appendLists(QString& name, QString& path){
    folders.push_back({name, path});
}

QStringList FolderReader::getList(){
    QStringList list;
    for(auto& el: folders){
        list.append(el.name);
    }
    list.sort();
    return list;
}
