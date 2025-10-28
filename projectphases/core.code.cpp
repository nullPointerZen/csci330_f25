#include <iostream>
#include <deque>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cassert>

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
        std::srand(std::time(nullptr)); // Seed RNG once
        snake.push_back({w / 2, h / 2});
        spawnFood();
    }

    // Randomly place food, avoiding snake body
    void spawnFood() {
        do {
            food = {std::rand() % width, std::rand() % height};
        } while (std::find(snake.begin(), snake.end(), food) != snake.end());
    }

    // Move the snake in the given direction
    // Returns false if collision occurs (game over)
    bool move(char direction) {
        Position head = snake.front();
        switch (direction) {
            case 'w': head.y--; break;
            case 's': head.y++; break;
            case 'a': head.x--; break;
            case 'd': head.x++; break;
            default: return true; // Ignore invalid input
        }

        // Wall collision
        if (head.x < 0 || head.x >= width || head.y < 0 || head.y >= height)
            return false;

        // Self collision
        for (const auto& part : snake)
            if (head == part)
                return false;

        snake.push_front(head);

        if (head == food) {
            spawnFood(); // Grow snake
        } else {
            snake.pop_back(); // Move forward
        }

        return true;
    }

    void printState() const {
        std::cout << "Snake head: (" << snake.front().x << ", " << snake.front().y << ")\n";
        std::cout << "Food: (" << food.x << ", " << food.y << ")\n";
    }
};

// Basic test functions
void testMovement() {
    SnakeGame game(10, 10);
    assert(game.move('w'));
    assert(game.move('a'));
}

void testCollision() {
    SnakeGame game(3, 3);
    game.move('w');
    game.move('w');
    assert(!game.move('w')); // Should hit wall
}

int main() {
    // Run tests
    testMovement();
    testCollision();
    std::cout << "All tests passed.\n\n";

    SnakeGame game(10, 10);
    char input;
    while (true) {
        game.printState();
        std::cout << "Move (w/a/s/d, q to quit): ";
        std::cin >> input;

        if (input == 'q') {
            std::cout << "Quitting game.\n";
            break;
        }

        if (input != 'w' && input != 'a' && input != 's' && input != 'd') {
            std::cout << "Invalid input. Use w/a/s/d or q.\n";
            continue;
        }

        if (!game.move(input)) {
            std::cout << "Game Over!\n";
            break;
        }
    }

    return 0;
}