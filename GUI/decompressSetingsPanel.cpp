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

#include "decompressSetingsPanel.h"

#include <QCheckBox>
#include <QGridLayout>
#include <QPushButton>

DecompressSettingsPanel::DecompressSettingsPanel() {
  keepBrokenFilesCheckbox = new QCheckBox("Keep broken files", this);
  QGridLayout *grid = new QGridLayout;

  QPushButton *resetToDefaultsButton = new QPushButton(tr("Reset To Defaults"));
  connect(resetToDefaultsButton, SIGNAL(clicked()), this, SIGNAL(resetToDefaults()));

  grid->addWidget(keepBrokenFilesCheckbox, 0, 0, Qt::AlignTop);
  grid->addWidget(resetToDefaultsButton, 1, 0, Qt::AlignBottom);

  setLayout(grid);
  setupWidgetsConnections();
}

DecompressSettingsPanel::~DecompressSettingsPanel() { }

void
DecompressSettingsPanel::get() {
  bool keepBroken = keepBrokenFilesCheckbox->isChecked();
  emit settingsChanged(keepBroken);
}

void
DecompressSettingsPanel::set(bool keepBroken) {
  keepBrokenFilesCheckbox->setChecked(keepBroken);
}

void
DecompressSettingsPanel::setupWidgetsConnections() {
  connect(keepBrokenFilesCheckbox, SIGNAL(stateChanged(int)), this, SLOT(get()));
}

