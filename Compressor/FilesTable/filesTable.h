/* 
 * File:   DataBlocksTable.h
 * Author: art
 *
 * Created on 12 Март 2011 г., 9:10
 */

#ifndef DATABLOCKSTABLE_H
#define	DATABLOCKSTABLE_H

#include <stdint.h>
#include <map>
#include <string>
#include <vector>
#include "fileBlocksInfo.h"

using namespace std;

class DataBlockHeader;

class FilesTable {
public:

    struct FileInfo {
        string fileName;
        bool corrupted;
    };

    FilesTable();

    FilesTable(const FilesTable&);
    virtual ~FilesTable();

    int add(DataBlockHeader * inHeader, unsigned int id = 0);
    void remove(DataBlockHeader * inHeader);
    map< string, vector <uint32_t> > & getNonCompleteFilesBlocksInfo();
    const vector<string>& getNonCompleteFilesNames();
    vector<FileInfo>& getArchiveContent();
    void clean();
    unsigned int getId(DataBlockHeader * inHeader) const;
    unsigned int getId(string fileName) const;

private:
    map< string, FileBlocksInfo > fileBlocksTable; //сведения о полученных блоках файла
    map< string, vector <uint32_t> > brokenFiletable;
    vector <string> brokenFilesNames;
    vector<FileInfo> archiveContent;

};

#endif	/* DATABLOCKSTABLE_H */

