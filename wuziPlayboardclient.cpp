#include "wuziPlayboardclient.h"

WuziPlayBoardClient::WuziPlayBoardClient(QWidget *parent)
{
    setStyleSheet("background: rgb(200, 150, 100)");

    m_chessBoard = new WuZiChessBoardClient;
    m_connectServerDlg = NULL;

    m_labelOutcome = new QLabel(ChineseToUTF8_TSG("���������δ��ʤ��"));
    m_connectServer = new QPushButton(ChineseToUTF8_TSG("���ӷ�����"));
    m_cancelLast = new QPushButton(ChineseToUTF8_TSG("������һ��"));
    m_cancelLast->setEnabled(false);
    m_restart = new QPushButton(ChineseToUTF8_TSG("���¿�ʼ"));
    m_restart->setEnabled(false);

    QVBoxLayout *vRightLayout = new QVBoxLayout;
    vRightLayout->addWidget(m_labelOutcome);
    vRightLayout->addWidget(m_connectServer);
    vRightLayout->addWidget(m_cancelLast);
    vRightLayout->addWidget(m_restart);

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(m_chessBoard);
    hLayout->addLayout(vRightLayout);

    setLayout(hLayout);
    setWindowTitle(ChineseToUTF8_TSG("��������Ϸ"));
    setFixedSize(sizeHint());

    connect(m_connectServer, SIGNAL(clicked(bool)), this, SLOT(connectServer()));
    connect(m_cancelLast, SIGNAL(clicked(bool)), this, SLOT(cancelLast()));
    connect(m_restart, SIGNAL(clicked(bool)), this, SLOT(restart()));

    connect(m_chessBoard, SIGNAL(chessFinished(int)), this, SLOT(chessFinished(int)));
    connect(m_chessBoard, SIGNAL(chessUnfinished()), this, SLOT(chessUnfinished()));
    connect(m_chessBoard, SIGNAL(connectServerSuccess(QString, QString, bool)),
            this, SLOT(connectServerSuccess(QString, QString, bool)));
    connect(m_chessBoard, SIGNAL(disconnectFromServer()), this, SLOT(disconnectFromServer()));
}

WuziPlayBoardClient::~WuziPlayBoardClient()
{
}

void WuziPlayBoardClient::connectServer()
{
    if(m_connectServerDlg==NULL)
    {
        m_connectServerDlg = new ConnectServerDlg;
        connect(m_connectServerDlg, SIGNAL(connectServerSignal(QString, QString, int, bool)),
                m_chessBoard, SLOT(connectServer(QString, QString, int, bool)));
    }

    m_connectServerDlg->exec();
}

void WuziPlayBoardClient::connectServerSuccess(QString user, QString opponent, bool colorIsBlack)
{
    QString title = ChineseToUTF8_TSG("��������Ϸ ") + ChineseToUTF8_TSG("�û�����")
                    + user + ChineseToUTF8_TSG(" ��������") + opponent
                    + (colorIsBlack ? ChineseToUTF8_TSG(" ִ����") : ChineseToUTF8_TSG(" ִ����"));
    emit connectServerSuccess(title);

    m_connectServer->setText(ChineseToUTF8_TSG("���ӷ������ɹ�"));
}

void WuziPlayBoardClient::disconnectFromServer()
{
    m_connectServer->setText(ChineseToUTF8_TSG("�Ѵӷ������Ͽ�"));
}

void WuziPlayBoardClient::cancelLast()
{
    m_chessBoard->cancelLast();

    if(m_chessBoard->isFinished()==false)
    {
        m_labelOutcome->setText(ChineseToUTF8_TSG("���������δ��ʤ��"));
    }
}

void WuziPlayBoardClient::restart()
{
    m_chessBoard->restart();
}

void WuziPlayBoardClient::chessFinished(int winner)
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
    m_restart->setEnabled(true);
}

void WuziPlayBoardClient::chessUnfinished()
{
    m_labelOutcome->setText(ChineseToUTF8_TSG("���������δ��ʤ��"));
    m_restart->setEnabled(false);
}
