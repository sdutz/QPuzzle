#include "puzzlescene.h"
#include "math.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>

//---------------------------------------------------------------
#define MAXMOVES 10
#define MAXOPCH  10

//---------------------------------------------------------------
puzzleScene::puzzleScene( QGraphicsView *parent /*= nullptr*/) : QGraphicsScene( parent)
{
    m_nStep   = 0 ;
    m_pFull   = nullptr ;
    m_pCurr   = nullptr ;
    m_pPrev   = nullptr ;
    m_pParent = parent ;
    m_pAnim   = new QTimer( this) ;
    setBackgroundBrush( Qt::black) ;
}

//---------------------------------------------------------------
void
puzzleScene::mousePressEvent( QGraphicsSceneMouseEvent* pEvent)
{
    if ( pEvent == nullptr  ||  ( m_pFull != nullptr  &&  m_pFull->isVisible())  ||  m_nStep != 0) {
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
        m_pCurr  = pItem ;
        m_pMove  = pItem->pos() - m_pPrev->pos() ;
        m_pMove /= MAXMOVES ;
        connect( m_pAnim, SIGNAL(timeout()), this, SLOT(swapPos())) ;
        m_pAnim->start( 100) ;
    }
    else if ( m_pPrev == pItem) {
        pItem->setOpacity( 1.) ;
        m_pPrev = nullptr ;
    }
}

//---------------------------------------------------------------
void
puzzleScene::swapPos()
{
    m_nStep ++ ;
    m_pCurr->moveBy( - m_pMove.rx(), - m_pMove.ry()) ;
    m_pPrev->moveBy( m_pMove.rx(), m_pMove.ry()) ;
    if ( m_nStep == MAXMOVES) {
        m_pAnim->stop() ;
        m_nStep = 0 ;
        m_pPrev = nullptr ;
        disconnect( m_pAnim, SIGNAL(timeout()), nullptr, nullptr) ;
        if ( isSolved()) {
            m_pFull->setOpacity( 0) ;
            m_pFull->show() ;
            connect( m_pAnim, SIGNAL(timeout()), this, SLOT(showSol())) ;
            m_pAnim->start( 100) ;
        }
    }
}

//---------------------------------------------------------------
void
puzzleScene::showSol()
{
    m_nStep ++ ;
    for ( int n = 0 ;  n < m_vSol.count() ;  n ++) {
        m_vSol[n].pItem->setOpacity( m_vSol[n].pItem->opacity() - 0.1) ;
    }
    m_pFull->setOpacity( m_pFull->opacity() + 0.1) ;

    if ( m_nStep == MAXOPCH) {
        disconnect( m_pAnim, SIGNAL(timeout()), nullptr, nullptr) ;
        m_nStep = 0 ;
    }
}

//---------------------------------------------------------------
void
puzzleScene::addImage( const QString& szImg)
{
    puzzleLevel level ;

    level.szImg = szImg ;

    m_lLevels.append( level) ;
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
puzzleScene::next()
{
    if ( m_lLevels.isEmpty()) {
        return false ;
    }

    m_lev = m_lLevels.takeFirst() ;

    return doPuzzle() ;
}

//---------------------------------------------------------------
bool
puzzleScene::start( int nDiv)
{
    if ( m_lLevels.isEmpty()) {
        return false ;
    }

    double maxLev = m_lLevels.count() > 4 ? 6 : 4 ;
    double dRatio = ( maxLev - nDiv) / m_lLevels.count() ;

    for ( int i = 0 ;  i < m_lLevels.count() ;  i ++) {
        m_lLevels[ i].nDiv = int ( nDiv + dRatio * i) ;
    }

    return next() ;
}

//---------------------------------------------------------------
bool
puzzleScene::doPuzzle()
{
    int nPos ;
    int nStX, nStY ;
    QPixmap pix ;
    QVector<int> apos ;
    QVector<int> arand ;
    puzzleItem pItem ;

    if ( ! pix.load( m_lev.szImg)) {
        return false ;
    }

    reset() ;

    m_pFull = addPixmap( pix) ;
    m_pFull->hide() ;
    nStX = pix.width() / m_lev.nDiv ;
    nStY = pix.height() / m_lev.nDiv ;
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
