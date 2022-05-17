#ifndef SNAKE_H
#define SNAKE_H
#include <QWidget>
#include <QKeyEvent>

class Snake : public QWidget {// Наследуем класс Qwidget классом Snake

public:
    Snake(QWidget *parent = 0); // Никакие из параметров не наследуются (Конструктор)

protected:
    void paintEvent(QPaintEvent *); // метод отвечает за рисовку виджетов
    void timerEvent(QTimerEvent *); // метод отвечает за выполнение действий по типу поражения, сьесть яблоко и направление движения
    void keyPressEvent(QKeyEvent *); // метод отвечает за нажатую клавишу

private:
    QImage dot;
    QImage head;
    QImage apple;

    static const int B_WIDTH = 300; // ширина игрового поля
    static const int B_HEIGHT = 300; // высота игрового поля
    static const int DOT_SIZE = 10; // размер яблока и тела змеи
    static const int ALL_DOTS = 900; // максимальное количество возможных точек на карте
    static const int RAND_POS = 29; //рандом яблока
    static const int DELAY = 140; // скорость игры в миллисекундах

    int timerId; // отвечает за таймер - скорость игры
    int dots;  // тело змеи с головой
    int apple_x; // координата яблока по иксу
    int apple_y; // координата яблока по игрику

    int x[ALL_DOTS]; // массив хранящий всего ВЕЛИКОГО ЗМЕЯ
    int y[ALL_DOTS]; // массив хранящий всего ВЕЛИКОГО ЗМЕЯ
    // да здраствует ВЕЛИКИЙ ЗМЕЙ !!!
    bool leftDirection; // клава
    bool rightDirection; // клава
    bool upDirection; // клава
    bool downDirection; // клава
    bool inGame; // убийца игры при поражении
    void loadImages(); // беру png из каталога
    void initGame(); // старт игры
    void locateApple(); // рандом яблока
    void checkApple(); // проверяем сьел ли ВЕЛИКИЙ ЗМЕЙ нашеь яблочко
    void checkCollision(); // проверяем голово и стену
    void move(); // изменение движения ВЕЛИКОГО ЗМЕЯ в массиве
    void doDrawing(); // рисует змею
    void gameOver(QPainter &); // рисует гейм овер
};
#endif // SNAKE_H
