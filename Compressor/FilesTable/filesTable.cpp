/******************************************************************************
 * Copyright (c) 2011-2013 Artur Molchanov <artur.molchanov@gmail.com>        *
 *                                                                            *
 * This program is free software: you can redistribute it and/or modify       *
 * it under the terms of the GNU General Public License as published by       *
 * the Free Software Foundation, either version 3 of the License, or          *
 * (at your option) any later version.                                        *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * GNU General Public License for more details.                               *
 *                                                                            *
 * You should have received a copy of the GNU General Public License          *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.      *
 ******************************************************************************/

#include "filesTable.h"
#include "../DataBlock/dataBlockHeader.h"

FilesTable::FilesTable() : fileBlocksTable(), brokenFiletable(), brokenFilesNames(), archiveContent() { }

FilesTable::~FilesTable() { }

using JAA::FileBlockResult;


JAA::FileBlockResult
FilesTable::add(DataBlockHeader * inHeader, unsigned int id) {
    FileBlockResult result = FileBlockResult::OK;

    auto pos = fileBlocksTable.find(string(inHeader->getFileName()));

    if (pos == fileBlocksTable.end()) {
        FileBlocksInfo blockInfo(inHeader->getPartsCount(), id);

        result = FileBlockResult::FIRST_RECIEVED_BLOCK;

        switch (blockInfo.setRecievedBlock(inHeader->getPart())) {
            case FileBlockResult::BLOCK_OUT_OF_RANGE:
              result = FileBlockResult::BLOCK_OUT_OF_RANGE;
                break;
            case FileBlockResult::ALL_BLOCKS_RECIEVED:
              result = FileBlockResult::ALL_BLOCKS_RECIEVED;
                break;
            case FileBlockResult::FIRST_AND_LAST_RECIEVED_BLOCK:
              result = FileBlockResult::FIRST_AND_LAST_RECIEVED_BLOCK;
                break;
            default:break;
        }

        fileBlocksTable.insert(map< string, FileBlocksInfo >::value_type(inHeader->getFileName(), blockInfo));
    } else {
        switch (pos->second.setRecievedBlock(inHeader->getPart())) {
            case FileBlockResult::BLOCK_OUT_OF_RANGE:
              result = FileBlockResult::BLOCK_OUT_OF_RANGE;
                break;
            case FileBlockResult::ALL_BLOCKS_RECIEVED:
              result = FileBlockResult::ALL_BLOCKS_RECIEVED;
                break;
            case FileBlockResult::FIRST_AND_LAST_RECIEVED_BLOCK:
              result = FileBlockResult::FIRST_AND_LAST_RECIEVED_BLOCK;
                break;
            default:break;
        }
    }

    return result;
}

void
FilesTable::clean() {
    fileBlocksTable.clear();
}

unsigned int
FilesTable::getId(DataBlockHeader * inHeader) const {
    auto i = fileBlocksTable.find(string(inHeader->getFileName()));
    if (i == fileBlocksTable.end())
        return 0;
    return i->second.getId();
}

unsigned int
FilesTable::getId(string fileName) const {
    auto i = fileBlocksTable.find(fileName);
    if (i == fileBlocksTable.end())
        return 0;
    return i->second.getId();
}

void
FilesTable::remove(DataBlockHeader * inHeader) {
    fileBlocksTable.erase(string(inHeader->getFileName()));
}

map< string, vector <uint32_t> > &
FilesTable::getNonCompleteFilesBlocksInfo() {
    brokenFiletable.clear();
    for (auto &i : fileBlocksTable) {
        const auto &nonRecievedBlocksInfo = i.second.getNonRecievedBlocksInfo();
        if (!nonRecievedBlocksInfo.empty())
            brokenFiletable.insert(make_pair(i.first, nonRecievedBlocksInfo));
    }

    return brokenFiletable;
}

const vector<string> &
FilesTable::getNonCompleteFilesNames() {
    brokenFilesNames.clear();

    for (auto &i : fileBlocksTable)
        if (!i.second.complete())
            brokenFilesNames.push_back(i.first);

    return brokenFilesNames;
}

vector<FilesTable::FileInfo>&
FilesTable::getArchiveContent() {
    archiveContent.clear();
    for (auto &i : fileBlocksTable) {
        FileInfo info;
        info.fileName = i.first;
        if (i.second.complete())
            info.corrupted = false;
        else
            info.corrupted = true;
        archiveContent.push_back(info);
    }
    return archiveContent;
}