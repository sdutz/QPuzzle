#pragma once

#include "puzzlewnd.h"
#include <QGraphicsView>

//---------------------------------------------------------------
class puzzleview : public QGraphicsView
{
    Q_OBJECT
    public :
        puzzleview( QWidget* parent) ;
        bool setParent( PuzzleWnd* pParent) ;

    protected :
        void dropEvent( QDropEvent* pEvent) ;
        void dragMoveEvent( QDragMoveEvent* pEvent) ;
        void dragEnterEvent( QDragEnterEvent* pEvent) ;
        void dragLeaveEvent( QDragLeaveEvent* pEvent) ;

    private :
        PuzzleWnd* m_pParent ;
} ;
