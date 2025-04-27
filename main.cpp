#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <limits>

const int GRID_SIZE = 15;
const int CELL_SIZE = 40;
const int MAX_DEPTH = 4;

enum class Player { None, Black, White };

struct Move {
    int row, col;
};

class Gomoku {
private:
    sf::RenderWindow window;
    std::vector<std::vector<Player>> board;
    Player currentPlayer;
    int score[GRID_SIZE][GRID_SIZE];

public:
    Gomoku() : window(sf::VideoMode(GRID_SIZE * CELL_SIZE, GRID_SIZE * CELL_SIZE), "SFML Gomoku with Minimax AI"),
               board(GRID_SIZE, std::vector<Player>(GRID_SIZE, Player::None)),
               currentPlayer(Player::Black) {}

    void run() {
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                if (currentPlayer == Player::Black && event.type == sf::Event::MouseButtonPressed)
                    handleMouseClick(event.mouseButton.x, event.mouseButton.y);
            }

            window.clear(sf::Color::White);
            drawBoard();
            drawStones();
            window.display();

            if (currentPlayer == Player::White) {
                sf::sleep(sf::milliseconds(300));
                makeAIMove();
            }
        }
    }

private:
    void handleMouseClick(int x, int y) {
        int row = y / CELL_SIZE;
        int col = x / CELL_SIZE;

        if (isValidMove(row, col)) {
            placeStone(row, col);
        }
    }

    void drawBoard() {
        sf::RectangleShape line;
        line.setFillColor(sf::Color::Black);

        for (int i = 0; i < GRID_SIZE; ++i) {
            line.setSize(sf::Vector2f(GRID_SIZE * CELL_SIZE, 1));
            line.setPosition(0, i * CELL_SIZE);
            window.draw(line);

            line.setSize(sf::Vector2f(1, GRID_SIZE * CELL_SIZE));
            line.setPosition(i * CELL_SIZE, 0);
            window.draw(line);
        }
    }

    void drawStones() {
        sf::CircleShape stone(CELL_SIZE / 2 - 2);

        for (int r = 0; r < GRID_SIZE; ++r) {
            for (int c = 0; c < GRID_SIZE; ++c) {
                if (board[r][c] != Player::None) {
                    stone.setPosition(c * CELL_SIZE + 2, r * CELL_SIZE + 2);
                    stone.setFillColor(board[r][c] == Player::Black ? sf::Color::Black : sf::Color::Red);
                    window.draw(stone);
                }
            }
        }
    }

    void placeStone(int row, int col) {
        board[row][col] = currentPlayer;
        if (checkWin(row, col)) {
            std::string winner = (currentPlayer == Player::Black ? "Black (Player)" : "White (AI)");
            std::cout << winner << " wins!\n";
            window.close();
        }
        currentPlayer = (currentPlayer == Player::Black) ? Player::White : Player::Black;
    }

    bool isValidMove(int row, int col) {
        return row >= 0 && row < GRID_SIZE && col >= 0 && col < GRID_SIZE && board[row][col] == Player::None;
    }

    bool checkDirection(int r, int c, int dr, int dc) {
        Player p = board[r][c];
        int count = 1;
        for (int i = 1; i < 5; ++i) {
            int nr = r + i * dr, nc = c + i * dc;
            if (nr < 0 || nr >= GRID_SIZE || nc < 0 || nc >= GRID_SIZE || board[nr][nc] != p) break;
            ++count;
        }
        for (int i = 1; i < 5; ++i) {
            int nr = r - i * dr, nc = c - i * dc;
            if (nr < 0 || nr >= GRID_SIZE || nc < 0 || nc >= GRID_SIZE || board[nr][nc] != p) break;
            ++count;
        }
        return count >= 5;
    }

    bool checkWin(int r, int c) {
        return checkDirection(r, c, 1, 0) || checkDirection(r, c, 0, 1) || checkDirection(r, c, 1, 1) || checkDirection(r, c, 1, -1);
    }

    void calautescore(){
        
        int personNum = 0;
        
        int aiNum = 0;
        
        int emptyNum = 0;
        
        for (int i = 0; i < 15; i++)	
        {
            for (int j = 0; j < 15; j++)
            {
                score[i][j] = 0;
            }
        }
        
        int size = 15;
        
        for (int row = 0; row < size; row++)
        {
            for (int col = 0; col < size; col++)
            {
                
                if (board[row][col] == Player::None)
                {
                    
                    for (int y = -1; y <= 0; y++)
                    {
                        for (int x = -1; x <= 1; x++)
                        {
                            
                            personNum = 0;
                            
                            aiNum = 0;
                            
                            emptyNum = 0;
                            
                            if (y == 0 && x != 1)
                            {
                                continue;
                            }
                            
                            if (!(y == 0 && x == 0))
                            {
                                
                                for (int i = 1; i <= 4; i++)
                                {
                                    int curRow = row + i * y;
                                    int curCol = col + i * x;
                                    if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && board[curRow][curCol] == Player::Black)
                                    {
                                        personNum++;
                                    }
                                    else if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && board[curRow][curCol] == Player::None)
                                    {
                                        emptyNum++;
                                        break;
                                    }
                                    else
                                    {
                                        break;
                                    }
                                }
                                
                                for (int i = 1; i <= 4; i++)
                                {
                                    int curRow = row - i * y;
                                    int curCol = col - i * x;
                                    if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && board[curRow][curCol] == Player::Black)
                                    {
                                        personNum++;
                                    }
                                    else if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && board[curRow][curCol] == Player::None)
                                    {
                                        emptyNum++;
                                        break;
                                    }
                                    else
                                    {
                                        break;
                                    }
                                }
                                
                                if (personNum == 1)
                                {
                                    score[row][col] += 10;
                                }
                                
                                else if (personNum == 3)
                                {
                                    
                                    if (emptyNum == 1)
                                    {
                                        score[row][col] += 30;
                                    }
                                   
                                    else if (emptyNum == 2)
                                    {
                                        score[row][col] += 40;
                                    }
                                }
                                
                                else if (personNum == 3)
                                {
                                    
                                    if (emptyNum == 1)
                                    {
                                        score[row][col] += 60;
                                    }
                                    
                                    else if (emptyNum == 2)
                                    {
                                        score[row][col] += 200;
                                    }
                                }
                                
                                else if (personNum == 4)
                                {
                                    score[row][col] += 20000;
                                }
                                
                                emptyNum = 0;
                                
                                for (int i = 1; i <= 4; i++)
                                {
                                    int curRow = row + i * y;
                                    int curCol = col + i * x;
                                    if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && board[curRow][curCol] == Player::White)
                                    {
                                        aiNum++;
                                    }
                                    else if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && board[curRow][curCol] == Player::None)
                                    {
                                        emptyNum++;
                                        break;
                                    }
                                    else
                                    {
                                        break;
                                    }
                                }
                                
                                for (int i = 1; i <= 4; i++)
                                {
                                    int curRow = row - i * y;
                                    int curCol = col - i * x;
                                    if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && board[curRow][curCol] == Player::White)
                                    {
                                        aiNum++;
                                    }
                                    else if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && board[curRow][curCol] == Player::None)
                                    {
                                        emptyNum++;
                                        break;
                                    }
                                    else
                                    {
                                        break;
                                    }
                                }
                                
                                if (aiNum == 0)
                                {
                                    score[row][col] += 5;
                                }
                                
                                else if (aiNum == 1)
                                {
                                    score[row][col] += 10;
                                }
                                
                                else if (aiNum == 3)
                                {
                                    
                                    if (emptyNum == 1)
                                    {
                                        score[row][col] += 25;
                                    }
                                    
                                    else if (emptyNum == 2)
                                    {
                                        score[row][col] += 50;
                                    }
                                }
                                
                                else if (aiNum == 3)
                                {
                                    
                                    if (emptyNum == 1)
                                    {
                                        score[row][col] += 55;
                                    }
                                    
                                    else if (emptyNum == 2)
                                    {
                                        score[row][col] += 10000;
                                    }
                                }
                                
                                else if (aiNum >= 4)
                                {
                                    score[row][col] += 30000;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    void makeAIMove() {
        
        calautescore();
        std::vector<std::pair<int,int>>v;
        int mx = 0;
        for(int i=0;i<GRID_SIZE;i++){
            for(int j=0;j<GRID_SIZE;j++){
                if(score[i][j]>mx){
                    mx = score[i][j];
                    v.clear();
                    v.push_back({i,j});
                }
                else if(score[i][j]==mx){
                    v.push_back({i,j});
                }
            }
        }
        if (v.size()){
            int ind = rand()%v.size();
            placeStone(v[ind].first, v[ind].second);
        
        }
    }
};

int main() {
    Gomoku game;
    game.run();
    return 0;
}