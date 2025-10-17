#include <iostream>
#include <deque>
#include <cstdlib>
#include <ctime>

struct Position {
    int x, y;
    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }
};

class SnakeGame {
    std::deque<Position> snake;
    Position food;
    int width, height;

public:
    SnakeGame(int w, int h) : width(w), height(h) {
        snake.push_back({w / 2, h / 2});
        spawnFood();
    }

    void spawnFood() {
        std::srand(std::time(nullptr));
        food = {std::rand() % width, std::rand() % height};
    }

    bool move(char direction) {
        Position head = snake.front();
        switch (direction) {
            case 'w': head.y--; break;
            case 's': head.y++; break;
            case 'a': head.x--; break;
            case 'd': head.x++; break;
        }

        // Collision with wall
        if (head.x < 0 || head.x >= width || head.y < 0 || head.y >= height)
            return false;

        // Collision with self
        for (const auto& part : snake)
            if (head == part)
                return false;

        snake.push_front(head);

        if (head == food) {
            spawnFood(); // grow snake
        } else {
            snake.pop_back(); // move forward
        }

        return true;
    }

    void printState() const {
        std::cout << "Snake head: (" << snake.front().x << ", " << snake.front().y << ")\n";
        std::cout << "Food: (" << food.x << ", " << food.y << ")\n";
    }
};

int main() {
    SnakeGame game(10, 10);
    char input;
    while (true) {
        game.printState();
        std::cout << "Move (w/a/s/d): ";
        std::cin >> input;
        if (!game.move(input)) {
            std::cout << "Game Over!\n";
            break;
        }
    }
    return 0;
}
