/* 
 * File:   DataSizeToQString.cpp
 * Author: art
 * 
 * Created on 22 Март 2011 г., 15:46
 */

#include "dataUnitsToQString.h"

DataUnitsToQString::DataUnitsToQString() { }

DataUnitsToQString::DataUnitsToQString(const DataUnitsToQString&) { }

DataUnitsToQString::~DataUnitsToQString() { }

QString
DataUnitsToQString::convertDataSize(off_t dataSize, int prec) {
  if (dataSize > 1E9)
    return QString::number((float) dataSize / 1E9, 'f', prec) + " GB";
  else if (dataSize > 1E6)
    return QString::number((float) dataSize / 1E6, 'f', prec) + " MB";
  else if (dataSize > 1E3)
    return QString::number((float) dataSize / 1E3, 'f', prec) + " KB";
  else
    return QString::number(dataSize) + " B";
}

QString
DataUnitsToQString::convertDataSpeed(int dataSpeed, int prec) {
  if (dataSpeed > 1E9)
    return QString::number((float) dataSpeed / 1E9, 'f', prec) + " GB/s";
  else if (dataSpeed > 1E6)
    return QString::number((float) dataSpeed / 1E6, 'f', prec) + " MB/s";
  else if (dataSpeed > 1E3)
    return QString::number((float) dataSpeed / 1E3, 'f', prec) + " KB/s";
  else
    return QString::number(dataSpeed) + " B/s";
}