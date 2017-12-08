#include "doubleclickedbutton.h"
#include <QEvent>
#include <QTimer>

DoubleClickedButton::DoubleClickedButton(QWidget *parent)
    : QPushButton(parent),
      m_single_clicked_timer(new QTimer(this)),
      m_bDoubleClicked(false)
{
    m_single_clicked_timer->setSingleShot(true);
    connect(m_single_clicked_timer, SIGNAL(timeout()), this, SIGNAL(singleClicked()));
}

DoubleClickedButton::DoubleClickedButton(const QString &text, QWidget *parent)
    : DoubleClickedButton(parent)
{
    setText(text);
}

DoubleClickedButton::DoubleClickedButton(const QIcon &icon, const QString &text, QWidget *parent)
    : DoubleClickedButton(text, parent)
{
    setIcon(icon);
}

DoubleClickedButton::~DoubleClickedButton()
{
}

bool DoubleClickedButton::event(QEvent* event)
{
    switch (event->type())
    {
    case QEvent::MouseButtonRelease:
//        m_bDoubleClicked ? m_bDoubleClicked = false : m_single_clicked_timer->start(10);//测试发现间隔时间最好不要低于10ms，否则不够两个事件的反馈间隔，如果需要延迟，可以自行修改间隔时间
        if(m_bDoubleClicked == true)
        {
            m_bDoubleClicked = false;


        }
        else if(m_bDoubleClicked == false)
        {
           m_single_clicked_timer->start(10);

        }
        break;
    case QEvent::MouseButtonDblClick:
        m_single_clicked_timer->stop();//进入双击事件停止掉定时器
        m_bDoubleClicked = true;
        emit doubleClicked();
        break;
    default:
        break;
    }

    return QPushButton::event(event);
}
