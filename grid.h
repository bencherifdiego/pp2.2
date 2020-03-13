#pragma once

namespace Tmpl8
{

class grid
{
  public:
    void Grid();
    void add(Tank* tank);
    void processTanks();
    void handleCell(/*Tank* tank*/int x, int y);
    static const int NUM_CELLS = 640;
    static const int CELL_SIZE = 20;
    void move(Tank* tank, double x, double y);
    void handleTank(Tank* tank, Tank* other);
    void handleNudge(Tank* tank, Tank* other);
    Tank* cells_[NUM_CELLS][NUM_CELLS];
};

} // namespace Tmpl8