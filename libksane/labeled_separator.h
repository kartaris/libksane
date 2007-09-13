/*
   Copyright (C) 2007 Kåre Särs <kare.sars@kolumbus.fi>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef LABELD_SEPARATOR_H
#define LABELD_SEPARATOR_H

// Qt includes.

#include <QFrame>

// Local includes.

#include "libksane_export.h"

/**
  *@author Kåre Särs
  */

namespace KSaneIface
{

/**
 * A separator with a text label
 */
class LIBKSANE_EXPORT LabeledSeparator : public QFrame
{
    Q_OBJECT

public:

   /**
    * Create the separator.
    *
    * \param parent parent widget
    * \param text is the text for the separator.
    */
    LabeledSeparator(QWidget *parent, const QString& text);
    ~LabeledSeparator();
};

}  // NameSpace KSaneIface

#endif // LABELD_SEPARATOR_H