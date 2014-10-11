/******************************************************************************
 * Copyright (c) 2011-2014 Artur Molchanov <artur.molchanov@gmail.com>        *
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

#include "dataUnitsToQString.h"

DataUnitsToQString::DataUnitsToQString() {
}

DataUnitsToQString::DataUnitsToQString(const DataUnitsToQString&) {
}

DataUnitsToQString::~DataUnitsToQString() {
}

QString DataUnitsToQString::convertDataSize(off_t dataSize, int prec) {
    if (dataSize > 1E9)
        return QString::number(dataSize / 1E9, 'f', prec) + " GB";
    else if (dataSize > 1E6)
        return QString::number(dataSize / 1E6, 'f', prec) + " MB";
    else if (dataSize > 1E3)
        return QString::number(dataSize / 1E3, 'f', prec) + " KB";
    else
        return QString::number(dataSize) + " B";
}

QString DataUnitsToQString::convertDataSpeed(int dataSpeed, int prec) {
    if (dataSpeed > 1E9)
        return QString::number(dataSpeed / 1E9, 'f', prec) + " GB/s";
    else if (dataSpeed > 1E6)
        return QString::number(dataSpeed / 1E6, 'f', prec) + " MB/s";
    else if (dataSpeed > 1E3)
        return QString::number(dataSpeed / 1E3, 'f', prec) + " KB/s";
    else
        return QString::number(dataSpeed) + " B/s";
}
