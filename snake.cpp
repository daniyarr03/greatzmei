#include <QPainter>
#include <QTime>
#include "snake.h"

Snake::Snake(QWidget *parent) : QWidget(parent) { // конструктор создающий окошко, загружает пнг и начинает игру
    setStyleSheet("background-color:black;");
    leftDirection = false;
    rightDirection = true;
    upDirection = false;
    downDirection = false;
    inGame = true;
    resize(B_WIDTH, B_HEIGHT);
    loadImages();
    initGame();
}

void Snake::loadImages() { // загружаю пнг
    dot.load("dot.png");
    head.load("head.png");
    apple.load("apple.png");
}

void Snake::initGame() { // старт игры
    dots = 3;
    for (int z = 0; z < dots; z++) {
        x[z] = 50 - z * 10; // координаты появления змеи(от икса отнимаем и змейка двигается по координате x)
        // 10 это размер каждой ячейки
        y[z] = 50; // 50 рандомная координата x, y на моем поле
    }
    locateApple(); // вызывыю рандом, размещается яблоко,
    timerId = startTimer(DELAY); // инициализация таймера, со скоростью делай
}

void Snake::paintEvent(QPaintEvent *e) { //метод для перерисовки виджета при его изменениях
    Q_UNUSED(e); // макрос для не использованных переменных
    doDrawing();
}

void Snake::doDrawing() { // перерисовка
    QPainter qp(this); // ссылается на обьект класса снейк
    if (inGame) {
        qp.drawImage(apple_x, apple_y, apple);

        for (int z = 0; z < dots; z++) { // дотс отвечает за длину змеи
            if (z == 0) { // голова ВЕЛИКОГО ЗМЕЯ
                qp.drawImage(x[z], y[z], head);
            } else { // тело ВЕЛИКОГО ЗМЕЯ
                qp.drawImage(x[z], y[z], dot);
            }
        }
    } else {
        gameOver(qp); // метод который ресует гейм овер
    }
}

void Snake::gameOver(QPainter &qp) { //рисуем гейм овер
    QString message = "Game over";
    QFont font("Courier", 15, QFont::DemiBold); //шрифт
    QFontMetrics fm(font); // тоже шрифт
    int textWidth = fm.horizontalAdvance(message); // ширина текста
    qp.setPen(QColor(Qt::white)); // выбираем цвет
    qp.setFont(font); // устанавливаем шрифт
    int h = height(); // ширина
    int w = width(); // длина
    qp.translate(QPoint(w/2, h/2));
    qp.drawText(-textWidth/2, 0, message); // рисуем
}

void Snake::checkApple() { // проверяет есть ли соприкосновение
    if ((x[0] == apple_x) && (y[0] == apple_y)) {
        dots++;
        locateApple(); // если да, то новое
    }
}

void Snake::move() { // двигает змею
    for (int z = dots; z > 0; z--) {
        x[z] = x[(z - 1)];
        y[z] = y[(z - 1)];
    }
    if (leftDirection) {
        x[0] -= DOT_SIZE;
    }
    if (rightDirection) {
        x[0] += DOT_SIZE;
    }
    if (upDirection) {
        y[0] -= DOT_SIZE;
    }
    if (downDirection) {
        y[0] += DOT_SIZE;
    }
}

void Snake::checkCollision() {
    for (int z = dots; z > 0; z--) { // проверка на аварию ВЕЛИКОГО ЗМЕЯ с ВЕЛЕКИМ ЗМЕЕМ
        if ((z > 3) && (x[0] == x[z]) && (y[0] == y[z])) {
            inGame = false;
        }
    }
    if (y[0] >= B_HEIGHT || y[0] < 0 || x[0] >= B_WIDTH ||x[0] < 0) { // проверка на столкновение с ВЕЛИКОЙ КИТАЙСКОЙ СТЕН
        inGame = false; // стопориться игра
    }
    if(!inGame) {
        killTimer(timerId); // убиваем таймер
    }
}

void Snake::locateApple() { // рандом яблока
    QTime time = QTime::currentTime();
    srand((uint) time.msec());
    int r = rand() % RAND_POS; // рандомное число которое влeзает в наше окно
    apple_x = (r * DOT_SIZE); // десятичная дробь остатка на размер клетки
    r = rand() % RAND_POS; // координаты для икса
    apple_y = (r * DOT_SIZE); // и игрика
}

void Snake::timerEvent(QTimerEvent *e) {
    Q_UNUSED(e);
    if (inGame) {
        checkApple();
        checkCollision();
        move();
    }
    repaint();
}

void Snake::keyPressEvent(QKeyEvent *e) { // нажание клавиши
    int key = e->key();
    if ((key == Qt::Key_Left) && (!rightDirection)) { // двойные проверки для одного нажатия(не двух)
        leftDirection = true;
        upDirection = false;
        downDirection = false;
    }
    if ((key == Qt::Key_Right) && (!leftDirection)) {
        rightDirection = true;
        upDirection = false;
        downDirection = false;
    }
    if ((key == Qt::Key_Up) && (!downDirection)) {
        upDirection = true;
        rightDirection = false;
        leftDirection = false;
    }
    if ((key == Qt::Key_Down) && (!upDirection)) {
        downDirection = true;
        rightDirection = false;
        leftDirection = false;
    }
    QWidget::keyPressEvent(e);
}
