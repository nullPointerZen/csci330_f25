#include <iostream>
#include <deque>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cassert>

// Position struct with equality and hashing
struct Position {
    int x, y;
    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }
    bool operator<(const Position& other) const {
        return std::tie(x, y) < std::tie(other.x, other.y);
    }
};

// Template grid printer (for debugging or future rendering)
template<typename T>
void printGrid(const std::vector<std::vector<T>>& grid) {
    for (const auto& row : grid) {
        for (const auto& cell : row)
            std::cout << cell << ' ';
        std::cout << '\n';
    }
}

class SnakeGame {
    std::deque<Position> snake;
    std::set<Position> snakeSet;
    std::vector<char> moveHistory;
    Position food;
    int width, height;
    int score = 0;
    char lastDirection = 'd';

    std::map<char, Position> directions = {
        {'w', {0, -1}}, {'s', {0, 1}},
        {'a', {-1, 0}}, {'d', {1, 0}}
    };

public:
    SnakeGame(int w, int h) : width(w), height(h) {
        std::srand(std::time(nullptr));
        Position start = {w / 2, h / 2};
        snake.push_back(start);
        snakeSet.insert(start);
        spawnFood();
    }

    void spawnFood() {
        do {
            food = {std::rand() % width, std::rand() % height};
        } while (snakeSet.count(food));
    }

    bool move(char direction) {
        // Prevent reversing
        std::map<char, char> opposite = {{'w','s'}, {'s','w'}, {'a','d'}, {'d','a'}};
        if (direction == opposite[lastDirection]) {
            std::cout << "Can't reverse direction!\n";
            return true;
        }

        if (!directions.count(direction)) {
            std::cout << "Invalid direction. Use w/a/s/d.\n";
            return true;
        }

        Position delta = directions[direction];
        Position head = {snake.front().x + delta.x, snake.front().y + delta.y};

        // Wall collision
        if (head.x < 0 || head.x >= width || head.y < 0 || head.y >= height) {
            std::cout << "You hit a wall!\n";
            return false;
        }

        // Self collision
        if (snakeSet.count(head)) {
            std::cout << "You ran into yourself!\n";
            return false;
        }

        snake.push_front(head);
        snakeSet.insert(head);
        moveHistory.push_back(direction);
        lastDirection = direction;

        if (head == food) {
            score++;
            spawnFood();
        } else {
            Position tail = snake.back();
            snake.pop_back();
            snakeSet.erase(tail);
        }

        return true;
    }

    void printState() const {
        std::cout << "Score: " << score << "\n";
        std::cout << "Snake head: (" << snake.front().x << ", " << snake.front().y << ")\n";
        std::cout << "Food: (" << food.x << ", " << food.y << ")\n";
    }

    void printHistory() const {
        std::cout << "Moves: ";
        for (char c : moveHistory) std::cout << c << ' ';
        std::cout << "\n";
    }
};

// Basic tests
void testMovement() {
    SnakeGame game(10, 10);
    assert(game.move('w'));
    assert(game.move('a'));
}

void testCollision() {
    SnakeGame game(3, 3);
    game.move('w');
    game.move('w');
    assert(!game.move('w'));
}

int main() {
    testMovement();
    testCollision();
    std::cout << "All tests passed.\n\n";

    std::unique_ptr<SnakeGame> game = std::make_unique<SnakeGame>(10, 10);
    char input;

    while (true) {
        game->printState();
        std::cout << "Move (w/a/s/d, q to quit): ";
        std::cin >> input;

        if (input == 'q') {
            std::cout << "Quitting game.\n";
            break;
        }

        if (!game->move(input)) {
            std::cout << "Game Over!\n";
            game->printHistory();
            break;
        }
    }

    return 0;
}