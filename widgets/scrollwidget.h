/*
 *   Copyright 2009 Marco Martin <notmart@gmail.com>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU Library General Public License as
 *   published by the Free Software Foundation; either version 2, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details
 *
 *   You should have received a copy of the GNU Library General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef PLASMA_SCROLLWIDGET_H
#define PLASMA_SCROLLWIDGET_H

#include <QtGui/QGraphicsWidget>

#include <plasma/plasma_export.h>


namespace Plasma
{

class ScrollWidgetPrivate;

/**
 * @class ScrollWidget plasma/widgets/ScrollWidget.h <Plasma/Widgets/ScrollWidget>
 *
 * @short A container of widgets that can have scrollbars
 *
 * A container of widgets that can have horizontal and vertical scrollbars if the content is bigger than the widget itself
 *
 * @since 4.3
 */
class PLASMA_EXPORT ScrollWidget : public QGraphicsWidget
{
    Q_OBJECT
    Q_PROPERTY(QGraphicsWidget *widget READ widget WRITE setWidget)
    Q_PROPERTY(Qt::ScrollBarPolicy horizontalScrollBarPolicy READ horizontalScrollBarPolicy WRITE setHorizontalScrollBarPolicy)
    Q_PROPERTY(Qt::ScrollBarPolicy verticalScrollBarPolicy READ verticalScrollBarPolicy WRITE setVerticalScrollBarPolicy)
    Q_PROPERTY(qreal horizontalScrollValue READ horizontalScrollValue WRITE setHorizontalScrollValue)
    Q_PROPERTY(qreal verticalScrollValue READ verticalScrollValue WRITE setVerticalScrollValue)
    Q_PROPERTY(QRectF viewport READ viewport)
    Q_PROPERTY(QString styleSheet READ styleSheet WRITE setStyleSheet)

public:

    /**
     * Constructs a new ScrollWidget
     *
     * @arg parent the parent of this widget
     */
    explicit ScrollWidget(QGraphicsWidget *parent = 0);
    ~ScrollWidget();

    /**
     * Sets the widget this ScrollWidget will contain
     * ownership is transferred to this scrollwidget,
     * if an old one was already in, it will be deleted
     *
     * @arg widget the new main sub widget
     */
    void setWidget(QGraphicsWidget *widget);

    /**
     * @return the main widget
     */
    QGraphicsWidget *widget() const;

    /**
     * Sets the horizontal scrollbar policy
     *
     * @arg policy desired policy
     */
    void setHorizontalScrollBarPolicy(const Qt::ScrollBarPolicy policy);

    /**
     * @return the horizontal scrollbar policy
     */
    Qt::ScrollBarPolicy horizontalScrollBarPolicy() const;

    /**
     * Sets the vertical scrollbar policy
     *
     * @arg policy desired policy
     */
    void setVerticalScrollBarPolicy(const Qt::ScrollBarPolicy policy);

    /**
     * @return the vertical scrollbar policy
     */
    Qt::ScrollBarPolicy verticalScrollBarPolicy() const;

    /**
     * Scroll the view until the given rectangle is visible
     *
     * @param rect rect we want visible, in coordinates mapped to the inner widget
     * @since 4.4
     */
    void ensureRectVisible(const QRectF &rect);

    /**
     * Scroll the view until the given item is visible
     *
     * @param item item we want visible
     * @since 4.4
     */
    void ensureItemVisible(QGraphicsItem *item);

     /**
     * The horizontal scroll value, between 0 and 100
     * @since 4.4
     */
    qreal horizontalScrollValue() const;

    /**
     * Set the horizontal scroll value, between 0 and 100
     * @since 4.4
     */
    void setHorizontalScrollValue(qreal value);

    /**
     * The horizontal scroll value, between 0 and 100
     * @since 4.4
     */
    qreal verticalScrollValue() const;

    /**
     * Set the horizontal scroll value, between 0 and 100
     * @since 4.4
     */
    void setVerticalScrollValue(qreal value);

    /**
     * The scrollable widget size.
     * @since 4.4
     */
    QRectF viewport() const;

    /**
     * Sets the stylesheet used to control the visual display of this ScrollWidget
     *
     * @arg stylesheet a CSS string
     */
    void setStyleSheet(const QString &stylesheet);

    /**
     * @return the stylesheet currently used with this widget
     */
    QString styleSheet() const;

    /**
     * @return the native widget wrapped by this ScrollWidget
     */
    QWidget *nativeWidget() const;

protected:

    void resizeEvent(QGraphicsSceneResizeEvent *event);

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void wheelEvent(QGraphicsSceneWheelEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);
    void focusInEvent(QFocusEvent *event);

private:
    ScrollWidgetPrivate * const d;

    Q_PRIVATE_SLOT(d, void verticalScroll(int value))
    Q_PRIVATE_SLOT(d, void horizontalScroll(int value))
    Q_PRIVATE_SLOT(d, void makeRectVisible())
};

} // namespace Plasma

#endif // multiple inclusion guard
