#pragma once

#include <QMainWindow>
#include <QSettings>
#include "puzzlescene.h"

namespace Ui {
    class PuzzleWnd ;
}

//---------------------------------------------------------------
class PuzzleWnd : public QMainWindow
{
    Q_OBJECT

    public :
        explicit PuzzleWnd( QWidget *parent = nullptr) ;
        ~PuzzleWnd() ;

    private slots :
        void start() ;
        void keyPressEvent( QKeyEvent* pEvent) ;

    private :
        Ui::PuzzleWnd *ui ;
        puzzleScene* m_pScene ;
        QSettings    m_set ;
} ;
