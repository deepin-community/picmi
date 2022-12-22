/* *************************************************************************
 *  Copyright 2015 Jakob Gruber <jakob.gruber@gmail.com>                   *
 *                                                                         *
 *  This program is free software: you can redistribute it and/or modify   *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation, either version 2 of the License, or      *
 *  (at your option) any later version.                                    *
 *                                                                         *
 *  This program is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *  You should have received a copy of the GNU General Public License      *
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.  *
 ************************************************************************* */


#include "view.h"

View::View(QWidget *parent) :
    QGraphicsView(parent)
{
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFrameStyle(QFrame::NoFrame);
    setAlignment( Qt::AlignLeft | Qt::AlignTop );
}

void View::resizeEvent(QResizeEvent *event) {
    if (event) {
        QGraphicsView::resizeEvent(event);
    }
    m_scene->resize(event->size());
}

void View::keyPressEvent(QKeyEvent *event) {
    /* make sure all key presses go to the currently selected cell item.
       without this, clicking on other areas of the scene causes cell items
       to lose focus.
       this seems like a hackish solution, please replace if there is
       a better way. */
    m_scene->forwardKeyPressEvent(event);
}

QSharedPointer<Scene> View::createScene(QSharedPointer<Picmi> game) {
    m_scene = QSharedPointer<Scene>(new Scene(game));
    setScene(m_scene.data());
    m_scene->resize(size());
    return m_scene;
}

void View::setPaused(bool paused) {
    setEnabled(!paused);
    setFocus();
    m_scene->setPaused(paused);
}
