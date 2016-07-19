#include "wuziPlayboard.h"

WuziPlayBoard::WuziPlayBoard(QWidget *parent)
{
    setStyleSheet("background: rgb(200, 150, 100)");

    m_chessBoard = new WuZiChessBoard;
    m_labelOutcome = new QLabel(ChineseToUTF8_TSG("���������δ��ʤ��"));
    m_randomize = new QPushButton(ChineseToUTF8_TSG("��ʼ�������"));
    m_cancelLast = new QPushButton(ChineseToUTF8_TSG("������һ��"));
    m_clearAll = new QPushButton(ChineseToUTF8_TSG("ȫ�����"));
    m_restart = new QPushButton(ChineseToUTF8_TSG("���¿�ʼ"));

    QVBoxLayout *vRightLayout = new QVBoxLayout;
    vRightLayout->addWidget(m_labelOutcome);
    vRightLayout->addWidget(m_randomize);
    // vRightLayout->addWidget(m_stopRandom);
    vRightLayout->addWidget(m_cancelLast);
    vRightLayout->addWidget(m_clearAll);
    vRightLayout->addWidget(m_restart);

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(m_chessBoard);
    hLayout->addLayout(vRightLayout);

    setLayout(hLayout);
    setWindowTitle(ChineseToUTF8_TSG("��������Ϸ"));
    setFixedSize(sizeHint());

    connect(m_randomize, SIGNAL(clicked(bool)), this, SLOT(randomize()));
    connect(m_cancelLast, SIGNAL(clicked(bool)), this, SLOT(cancelLast()));
    connect(m_clearAll, SIGNAL(clicked(bool)), this, SLOT(clearAll()));
    connect(m_restart, SIGNAL(clicked(bool)), this, SLOT(clearAll()));

    connect(m_chessBoard, SIGNAL(chessFinished(int)), this, SLOT(chessFinished(int)));
    connect(m_chessBoard, SIGNAL(chessUnfinished()), this, SLOT(chessUnfinished()));
}

WuziPlayBoard::~WuziPlayBoard()
{
}

void WuziPlayBoard::randomize()
{
    if(m_randomize->text()==ChineseToUTF8_TSG("��ʼ�������"))
    {
        m_chessBoard->randomize();
        m_randomize->setText(ChineseToUTF8_TSG("ֹͣ�������"));
    }
    else
    {
        m_chessBoard->stopRandomize();
        m_randomize->setText(ChineseToUTF8_TSG("��ʼ�������"));
    }
}

void WuziPlayBoard::clearAll()
{
    m_chessBoard->clearAll();
    m_randomize->setEnabled(true);
    m_randomize->setText(ChineseToUTF8_TSG("��ʼ�������"));
}

void WuziPlayBoard::cancelLast()
{
    m_chessBoard->cancelLast();
    m_randomize->setEnabled(true);
    m_randomize->setText(ChineseToUTF8_TSG("��ʼ�������"));

    if(m_chessBoard->isFinished()==false)
    {
        m_labelOutcome->setText(ChineseToUTF8_TSG("���������δ��ʤ��"));
    }
}


void WuziPlayBoard::chessFinished(int winner)
{
    QString outcome;

    if(winner==-1)
    {
        outcome = ChineseToUTF8_TSG("����������ڷ�ʤ");
    }
    else
    {
        outcome = ChineseToUTF8_TSG("����������׷�ʤ");
    }

    m_labelOutcome->setText(outcome);
    m_randomize->setEnabled(false);
}

void WuziPlayBoard::chessUnfinished()
{
    m_labelOutcome->setText(ChineseToUTF8_TSG("���������δ��ʤ��"));
    m_randomize->setEnabled(true);
}
