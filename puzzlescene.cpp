#include "puzzlescene.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>

//---------------------------------------------------------------
puzzleScene::puzzleScene( QGraphicsView *parent /*= nullptr*/) : QGraphicsScene( parent)
{
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
    }
}

//---------------------------------------------------------------
bool
puzzleScene::doPuzzle( const QString szFile, int nDiv)
{
    int nPos ;
    int nStX, nStY ;
    QPixmap pix ;
    QVector<QPixmap> crops ;
    QVector<int> apos ;
    QVector<int> arand ;
    QGraphicsPixmapItem* pITem ;

    if ( ! pix.load( szFile)) {
        return false ;
    }

    m_pFull = addPixmap( pix) ;
    m_pFull->hide() ;
    nStX = pix.width() / nDiv ;
    nStY = pix.height() / nDiv ;
    for ( int nX = 0 ;  nX < pix.width() ;  nX ++) {
        for ( int nY = 0 ;  nY < pix.height() ;  nY ++) {
            crops.append( pix.copy( nX, nY, nStX, nStY)) ;
            nY += nStY ;
        }
        nX += nStX ;
    }

    for ( int i = 0 ;  i < crops.count() ;  i ++) {
        apos.append( i) ;
    }

    for ( int i = 0 ;  i < crops.count() ;  i ++) {
        arand.append( apos.takeAt( qrand() % (apos.count()))) ;
    }

    nPos = 0 ;
    for ( int nX = 0 ;  nX < pix.width() ;  nX ++) {
        for ( int nY = 0 ;  nY < pix.height() ;  nY ++) {
            pITem = addPixmap( crops[arand[nPos ++]]) ;
            pITem->setPos( nX, nY) ;
            nY += nStY ;
        }
        nX += nStX ;
    }

    m_pParent->fitInView( itemsBoundingRect(), Qt::KeepAspectRatio) ;

    return true ;
}
