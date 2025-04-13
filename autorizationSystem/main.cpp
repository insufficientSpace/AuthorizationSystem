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

void buttonClicked(QLineEdit* userName, QLineEdit* password);

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
    userNameLine->setPlaceholderText("Введите имя пользователя: ");
    userNameLine->setFixedSize(250, 50);
    userNameLine->move(125, 125);
    userNameLine->show();

    QLineEdit* userPasswordLine = new QLineEdit(&w);
    userPasswordLine->setPlaceholderText("Введите пароль: ");
    userPasswordLine->setFixedSize(250, 50);
    userPasswordLine->move(125, 200);
    userPasswordLine->setEchoMode(QLineEdit::Password); // Скрыть ввод пароля
    userPasswordLine->show();

    QPushButton *button = new QPushButton("Зарегистрироваться", &w);
    button->setFixedSize(125, 50);
    button->move(190, 280);
    button->show();

    // Подключаем сигнал к слоту
    QObject::connect(button, &QPushButton::clicked, [&]() {
        buttonClicked(userNameLine, userPasswordLine);
    });

    return a.exec();
}

void buttonClicked(QLineEdit* userName, QLineEdit* password)
{
    QFile file("D:/QtProjects/autorizationSystem/regList.txt"); // Используйте / вместо \

    if (file.open(QIODevice::Append | QIODevice::Text)) { // Открываем файл для добавления текста
        QTextStream out(&file);
        out << "Имя пользователя: " << userName->text() << "\n"; // Получаем текст из QLineEdit
        out << "Пароль: " << password->text() << "\n"; // Получаем текст из QLineEdit
        file.close();
        QMessageBox::information(nullptr, "Успех", "Регистрация прошла успешно!");
    } else {
        QMessageBox::warning(nullptr, "Ошибка", "Не удалось открыть файл для записи.");
    }
}
