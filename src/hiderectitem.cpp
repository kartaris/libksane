/* ============================================================
*
* This file is part of the KDE project
*
* Description: QGraphicsItem for hiding rects in the image viewer.
*
* Copyright (C) 2019 by Alexander Volkov <a.volkov@rusbitech.ru>
*
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) version 3, or any
* later version accepted by the membership of KDE e.V. (or its
* successor approved by the membership of KDE e.V.), which shall
* act as a proxy defined in Section 6 of version 3 of the license.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
* ============================================================ */

#include "hiderectitem.h"

#include <QPen>

namespace KSaneIface
{

HideRectItem::HideRectItem()
    : m_devicePixelRatio(1.0)
{
    setOpacity(0.4);
    setPen(Qt::NoPen);
    setBrush(Qt::black);
}

QRectF HideRectItem::rect() const
{
    QRectF r = QGraphicsRectItem::rect();
    return QRectF(r.topLeft() * m_devicePixelRatio, r.size() * m_devicePixelRatio);
}

void HideRectItem::setRect(const QRectF &rect)
{
    QGraphicsRectItem::setRect(QRectF(rect.topLeft() / m_devicePixelRatio, rect.size() / m_devicePixelRatio));
}

qreal HideRectItem::devicePixelRatio() const
{
    return m_devicePixelRatio;
}

void HideRectItem::setDevicePixelRatio(qreal dpr)
{
    m_devicePixelRatio = dpr;
}

}  // NameSpace KSaneIface
