#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
{
    m_playBoardClient = NULL;
    m_playBoardDesktop = NULL;

    m_state = non_selected;

    createActions();
    createMenus();

    m_playBoardDesktop = new WuziPlayBoardDesktop;
    setCentralWidget(m_playBoardDesktop);
    setFixedSize(sizeHint());

    QLabel *label = new QLabel;
    setCentralWidget(label);

    setWindowTitle(ChineseToUTF8_TSG("��������Ϸ"));
}

MainWindow::~MainWindow()
{
}


void MainWindow::createMenus()
{
    selectMenu = menuBar()->addMenu(ChineseToUTF8_TSG("ѡ��"));
    selectMenu->addAction(desktopLoadAction);
    selectMenu->addAction(networkLoadAction);

    helpMenu = menuBar()->addMenu(ChineseToUTF8_TSG("����"));
    helpMenu->addAction(aboutAction);
}

void MainWindow::createActions()
{
    desktopLoadAction = new QAction(ChineseToUTF8_TSG("������"), this);
    connect(desktopLoadAction, SIGNAL(triggered()), this, SLOT(desktopLoad()));

    networkLoadAction = new QAction(ChineseToUTF8_TSG("�����"), this);
    connect(networkLoadAction, SIGNAL(triggered()), this, SLOT(networkLoad()));

    aboutAction = new QAction(ChineseToUTF8_TSG("����"), this);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));
}

void MainWindow::about()
{
    QString qstring1, qstring2;

    qstring1 = ChineseToUTF8_TSG("������������Ϸ");
    qstring2 = ChineseToUTF8_TSG(
               "<h2>������С��Ϸ 1.1</h2>"
               "<p>Copyright &copy; 2016 Software Inc."
               "<p>������С��Ϸ ��һ������QT��С��������Ϸ"
               "<p>���ߣ�Ϳ�ɸ�"
               "<p>���ڣ�2016-06-23");

    QMessageBox::about(this, qstring1, qstring2);
}

void MainWindow::desktopLoad()
{
    if(m_state != desktop)
    {
        m_playBoardDesktop = new WuziPlayBoardDesktop;
        setCentralWidget(m_playBoardDesktop);
        setWindowTitle(ChineseToUTF8_TSG("��������Ϸ ������"));
        m_state = desktop;
    }
}

void MainWindow::networkLoad()
{
    if(m_state != network)
    {
        m_playBoardClient = new WuziPlayBoardClient;
        setCentralWidget(m_playBoardClient);
        setWindowTitle(ChineseToUTF8_TSG("��������Ϸ �����"));
        m_state = network;

        connect(m_playBoardClient, SIGNAL(connectServerSuccess(QString &)),
                this, SLOT(connectServerSuccess(QString &)));
    }
}

void MainWindow::connectServerSuccess(QString &title)
{
    setWindowTitle(title);
}
