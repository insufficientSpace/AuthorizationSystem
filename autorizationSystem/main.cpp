#include "mainwindow.h"
#include <QApplication>
#include <QLabel>
#include <QFont>
#include <QLineEdit>
#include <QPushButton>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QString>
#include <QMainWindow>
#include <QMap>

class logWindow : public QMainWindow
{
public:
    logWindow()
    {
        setWindowTitle("LOGIN");
        setFixedSize(400, 400);
        show();

        QLabel *loginTitle = new QLabel("LOGIN", this);
        loginTitle->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
        loginTitle->setFixedSize(200, 50);
        loginTitle->move(100, 50);
        loginTitle->show();

        QFont font = loginTitle->font();
        font.setPointSize(18);
        loginTitle->setFont(font);

        QLineEdit *loginUserNameLine = new QLineEdit(this);
        loginUserNameLine->setPlaceholderText("Enter the user's name: ");
        loginUserNameLine->setFixedSize(250, 50);
        loginUserNameLine->move(75, 125);
        loginUserNameLine->show();

        QLineEdit *loginUserPasswordLine = new QLineEdit(this);
        loginUserPasswordLine->setPlaceholderText("Enter the password: ");
        loginUserPasswordLine->setFixedSize(250, 50);
        loginUserPasswordLine->move(75, 200);
        loginUserPasswordLine->setEchoMode(QLineEdit::Password);
        loginUserPasswordLine->show();

        QPushButton *LoginButton = new QPushButton("Login", this);
        LoginButton->setFixedSize(125, 50);
        LoginButton->move(140, 280);
        LoginButton->show();

        QMap<QString, QString> userCredentials;
        QFile file("D:/QtProjects/autorizationSystem/regList.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "Error", "Couldn't open the file for reading.");
            return;
        }

        QTextStream in(&file);
        while (!in.atEnd()) {
            QString userName = in.readLine();
            QString password = in.readLine();
            userCredentials.insert(userName.trimmed(), password.trimmed());
        }
        file.close();

        QObject::connect(LoginButton, &QPushButton::clicked, [this, loginUserNameLine, loginUserPasswordLine, userCredentials]() {
            QString enteredUserName = loginUserNameLine->text().trimmed();
            QString enteredPassword = loginUserPasswordLine->text().trimmed();

                if (userCredentials.contains(enteredUserName) &&
                    userCredentials.value(enteredUserName) == enteredPassword) {
                QMessageBox::information(this, "Successful authorization", "You have successfully logged in!");
            } else {
                QMessageBox::warning(this, "Authorization error!", "Incorrect username or password!");
            }
        });
    }
};

void buttonClicked(QLineEdit* userName, QLineEdit* password)
{
    QFile file("D:/QtProjects/autorizationSystem/regList.txt");

    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << userName->text().trimmed() << "\n";
        out << password->text().trimmed() << "\n";
        file.close();
    } else {
        QMessageBox::warning(nullptr, "Error", "Couldn't open the file for writing.");
    }

    logWindow *lw = new logWindow();
    lw->show();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setWindowTitle("AUTHORIZATION SYSTEM");
    w.resize(500, 500);
    w.show();

    QLabel *registrationTitle = new QLabel("REGISTRATION", &w);
    registrationTitle->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    registrationTitle->setFixedSize(200, 50);
    registrationTitle->move(150, 50);
    registrationTitle->show();

    QFont font = registrationTitle->font();
    font.setPointSize(18);
    registrationTitle->setFont(font);

    QLineEdit* userNameLine = new QLineEdit(&w);
    userNameLine->setPlaceholderText("Enter the user's name: ");
    userNameLine->setFixedSize(250, 50);
    userNameLine->move(125, 125);
    userNameLine->show();

    QLineEdit* userPasswordLine = new QLineEdit(&w);
    userPasswordLine->setPlaceholderText("Enter the password: ");
    userPasswordLine->setFixedSize(250, 50);
    userPasswordLine->move(125, 200);
    userPasswordLine->setEchoMode(QLineEdit::Password);
    userPasswordLine->show();

    QPushButton *button = new QPushButton("Register", &w);
    button->setFixedSize(125, 50);
    button->move(190, 280);
    button->show();

    QObject::connect(button, &QPushButton::clicked, [&]() {
        buttonClicked(userNameLine, userPasswordLine);
        w.close();
    });

    return a.exec();
}
