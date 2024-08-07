#include "include/raylib.h"

Color Green = Color{166, 209, 137,255};
Color Dark_Green = Color{130, 200, 120, 255};
Color Teal = Color{129, 200, 190, 255};
Color Maroon = Color{234, 153, 156, 255};
Color Rosewater = Color{242, 213, 207, 255};

int player_score = 0;
int cpu_score = 0;

class Ball {
  public:
  float x, y;
  int speed_x, speed_y;
  int radius;

  void Draw() {
    DrawCircle(x, y, radius, Maroon);
  }

  void Update() {
    x += speed_x;
    y += speed_y;

    if (y + radius >= GetScreenHeight() || y - radius <= 0) {
      speed_y *= -1;
    }
    // Cpu wins
    if (x + radius >= GetScreenWidth()) {
      cpu_score++;
      ResetBall();
    }

    if (x - radius <= 0) {
      player_score++;
      ResetBall();
    }
  }

   void ResetBall() {
    x = (float)GetScreenWidth() / 2;
    y = (float)GetScreenHeight() / 2;

    int speed_choices[2] = {-1, 1};
    speed_x *= speed_choices[GetRandomValue(0, 1)];
    speed_y *= speed_choices[GetRandomValue(0, 1)];
  }
};

class Paddle {
  protected:
  void LimitMovement() {
    if (y <= 0) {
      y = 0;
    }
    if (y + height >= GetScreenHeight()) {
      y = GetScreenHeight() - height;
    }
  }

  public:
  float x, y;
  float width, height;
  int speed;

  void Draw() {
    DrawRectangleRounded(Rectangle{x, y, width, height}, 0.6, 0, Rosewater);
  }

  void Update() {
    Control();
    LimitMovement();
  }

  private:
  void Control(){
    if (IsKeyDown(KEY_UP)) {
      y = y - speed;
    }
    if (IsKeyDown(KEY_DOWN)) {
      y = y + speed;
    }
  }

};

class CpuPaddle : public Paddle {
  public:
  void Update(int ball_y){
    if (y + height / 2 > ball_y) {
      y = y - speed;
    }
    if (y + height / 2 <= ball_y) {
      y = y + speed;
    }
    LimitMovement();
  }
};

Ball ball;
Paddle player;
CpuPaddle cpu;

int main() {
  const int screen_width = 1280;
  const int screen_height = 800;
  InitWindow(screen_width, screen_height, "PONG++ by LordPaijo");
  SetTargetFPS(60);
  ball.radius = 20;
  ball.x = (float)screen_width / 2;
  ball.y = (float)screen_height / 2;
  ball.speed_x = 7;
  ball.speed_y = 7;

  player.width = 25;
  player.height = 120;
  player.x = screen_width - player.width - 10;
  player.y = (float)screen_height / 2 - player.height / 2;
  player.speed = 7;

  cpu.height = 120;
  cpu.width = 25;
  cpu.x = 10;
  cpu.y = (float)screen_height / 2 - cpu.height / 2;
  cpu.speed = 6;

  while (WindowShouldClose() == false) {
    BeginDrawing();

    ball.Update();
    player.Update();
    cpu.Update(ball.y);

    if (CheckCollisionCircleRec({ball.x, ball.y}, ball.radius, {player.x, player.y, player.width, player.height})) {
      ball.speed_x *= -1;
    }

    if (CheckCollisionCircleRec({ball.x, ball.y}, ball.radius, {cpu.x, cpu.y, cpu.width, cpu.height})) {
      ball.speed_x *= -1;
    }

    ClearBackground(Dark_Green);
    DrawRectangle(screen_width / 2, 0, screen_width / 2, screen_height, Green);
    DrawCircle(screen_width / 2, screen_height / 2, 150, Teal);
    DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
    ball.Draw();
    cpu.Draw();
    player.Draw();
    DrawText(TextFormat("%i", cpu_score), screen_width / 4 - 20, 20, 150, GREEN);
    DrawText(TextFormat("%i", player_score), 3 * screen_width / 4 - 20, 20, 150, GREEN);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}