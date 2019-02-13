#include "puzzleview.h"
#include <QMimeData>
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>

puzzleview::puzzleview( QWidget* parent) : QGraphicsView( parent)
{
    setAcceptDrops( true) ;

}

//---------------------------------------------------------------
bool
puzzleview::setParent( PuzzleWnd* pParent)
{
    if ( pParent == nullptr) {
        return false ;
    }

    m_pParent = pParent ;

    return true ;
}

//---------------------------------------------------------------
void
puzzleview::dragEnterEvent( QDragEnterEvent* pEvent)
{
    if ( pEvent == nullptr) {
        return ;
    }

    pEvent->acceptProposedAction() ;
}

//---------------------------------------------------------------
void
puzzleview::dragMoveEvent( QDragMoveEvent* pEvent)
{
    if ( pEvent == nullptr) {
        return ;
    }

    pEvent->acceptProposedAction() ;
}

//---------------------------------------------------------------
void
puzzleview::dragLeaveEvent( QDragLeaveEvent* pEvent)
{
    if ( pEvent == nullptr) {
        return ;
    }

    pEvent->accept() ;
}

//---------------------------------------------------------------
void
puzzleview::dropEvent( QDropEvent* pEvent)
{
    if ( pEvent == nullptr  ||  pEvent->mimeData() == nullptr  ||
         ! pEvent->mimeData()->hasUrls()) {
        return ;
    }

    m_pParent->addUrls( pEvent->mimeData()->urls()) ;
}
