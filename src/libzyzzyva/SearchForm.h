//---------------------------------------------------------------------------
// SearchForm.h
//
// A form for searching for words, patterns, anagrams, etc.
//
// Copyright 2004, 2005, 2006, 2007, 2008 Michael W Thelen <mthelen@gmail.com>.
//
// This file is part of Zyzzyva.
//
// Zyzzyva is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// Zyzzyva is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//---------------------------------------------------------------------------

#ifndef ZYZZYVA_SEARCH_FORM_H
#define ZYZZYVA_SEARCH_FORM_H

#include "ActionForm.h"
#include <QCheckBox>
#include <QComboBox>
#include <QLabel>

class LexiconSelectWidget;
class SearchSpecForm;
class WordEngine;
class WordTableModel;
class WordTableView;
class ZPushButton;

class SearchForm : public ActionForm
{
    Q_OBJECT
    public:
    SearchForm(WordEngine* e, QWidget* parent = 0, Qt::WFlags f = 0);
    QIcon getIcon() const;
    QString getTitle() const;
    QString getStatusString() const;
    bool isSaveEnabled() const;

    public slots:
    void saveRequested();
    void search();
    void updateResultTotal(int num);
    void specChanged();

    private:
    WordEngine*     wordEngine;
    LexiconSelectWidget* lexiconWidget;
    SearchSpecForm* specForm;
    QCheckBox*      lowerCaseCbox;
    WordTableView*  resultView;
    WordTableModel* resultModel;
    ZPushButton*    searchButton;
    QString         statusString;
};

#endif // ZYZZYVA_SEARCH_FORM_H
