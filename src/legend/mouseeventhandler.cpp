/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#include "mouseeventhandler_p.h"
#include <QGraphicsSceneMouseEvent>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

MouseEventHandler::MouseEventHandler() :
    m_pressedPos(0,0),
    m_state(Idle),
    m_treshold(10)
{
}

MouseEventHandler::~MouseEventHandler()
{
}

void MouseEventHandler::setMoveTreshold(qreal treshold)
{
    m_treshold = treshold;
}

void MouseEventHandler::handleMousePressEvent(QGraphicsSceneMouseEvent* event)
{
    m_pressedPos = event->pos();
    m_state = Pressed;
}

void MouseEventHandler::handleMouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    QPointF delta = event->pos() - m_pressedPos;

    switch (m_state) {
    case Pressed: {
        // calculate treshold. If enough, change to move state and send out move deltas.
        if (qAbs(delta.x()) > m_treshold || qAbs(delta.y()) > m_treshold) {
            m_state = Moved;
            mouseMoved(delta);
        }
        break;
    }
    case Moved: {
        mouseMoved(delta);
        break;
    }
    case Idle:
    default: {
        break;
    }
    }
}

void MouseEventHandler::handleMouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    QPointF delta = event->pos() - m_pressedPos;

    switch (m_state) {
    case Pressed:
    {
        m_state = Idle;
        mouseClicked();
        break;
    }
    case Moved:
    {
        m_state = Idle;
        mouseReleased(delta);
        break;
    }
    default:
    {
        m_state = Idle;
        break;
    }
    }
}

QTCOMMERCIALCHART_END_NAMESPACE