#include "puzzlescene.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>

//---------------------------------------------------------------
puzzleScene::puzzleScene( QGraphicsView *parent /*= nullptr*/) : QGraphicsScene( parent)
{
    m_pFull   = nullptr ;
    m_pPrev   = nullptr ;
    m_pParent = parent ;
    setBackgroundBrush( Qt::black) ;
}

//---------------------------------------------------------------
void
puzzleScene::mousePressEvent( QGraphicsSceneMouseEvent* pEvent)
{
    if ( pEvent == nullptr) {
        return ;
    }

    QList<QGraphicsItem*> lpitems = items( pEvent->scenePos()) ;
    if ( lpitems.isEmpty()) {
        return ;
    }

    QGraphicsItem* pItem = lpitems.first() ;

    if ( m_pPrev == nullptr) {
        m_pPrev = pItem ;
        pItem->setOpacity( 0.5) ;
    }
    else if ( pItem != m_pPrev){
        m_pPrev->setOpacity( 1.) ;
        QPointF pos = pItem->pos() ;
        pItem->setPos( m_pPrev->pos()) ;
        m_pPrev->setPos( pos) ;
        m_pPrev = nullptr ;
        if ( isSolved()) {
            showSol( true) ;
        }
    }
}

//---------------------------------------------------------------
void
puzzleScene::reset()
{
    clear() ;
    m_vSol.clear() ;
}

//---------------------------------------------------------------
bool
puzzleScene::showSol( bool bShow)
{
    if ( m_pFull == nullptr) {
        return false ;
    }

    for ( int n = 0 ;  n < m_vSol.count() ;  n ++) {
        bShow ? m_vSol[n].pItem->hide() : m_vSol[n].pItem->show() ;
    }

    bShow ? m_pFull->show() : m_pFull->hide() ;

    return true ;
}

//---------------------------------------------------------------
bool
puzzleScene::isSolved()
{
    for ( int n = 0 ;  n < m_vSol.count() ;  n ++) {
        if ( m_vSol[n].pItem->pos() != m_vSol[n].ptPos) {
            return false ;
        }
    }

    return true ;
}

//---------------------------------------------------------------
bool
puzzleScene::doPuzzle( const QString szFile, int nDiv)
{
    int nPos ;
    int nStX, nStY ;
    QPixmap pix ;
    QVector<int> apos ;
    QVector<int> arand ;
    puzzleItem pItem ;

    if ( ! pix.load( szFile)) {
        return false ;
    }

    reset() ;

    m_pFull = addPixmap( pix) ;
    m_pFull->hide() ;
    nStX = pix.width() / nDiv ;
    nStY = pix.height() / nDiv ;
    for ( int nX = 0 ;  nX < pix.width() ;  nX ++) {
        for ( int nY = 0 ;  nY < pix.height() ;  nY ++) {
            pItem.pItem = addPixmap( pix.copy( nX, nY, nStX, nStY)) ;
            pItem.ptPos = QPoint( nX, nY) ;
            m_vSol.append( pItem) ;
            nY += nStY ;
        }
        nX += nStX ;
    }

    for ( int i = 0 ;  i < m_vSol.count() ;  i ++) {
        apos.append( i) ;
    }

    for ( int i = 0 ;  i < m_vSol.count() ;  i ++) {
        arand.append( apos.takeAt( qrand() % (apos.count()))) ;
    }

    nPos = 0 ;
    for ( int nX = 0 ;  nX < pix.width() ;  nX ++) {
        for ( int nY = 0 ;  nY < pix.height() ;  nY ++) {
            m_vSol[arand[nPos ++]].pItem->setPos( nX, nY) ;
            nY += nStY ;
        }
        nX += nStX ;
    }

    m_pParent->fitInView( itemsBoundingRect(), Qt::KeepAspectRatio) ;

    return true ;
}
